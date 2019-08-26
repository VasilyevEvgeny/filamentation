from datetime import datetime
from numpy import loadtxt, transpose, append, where, log10, meshgrid
from numpy import max as maximum
from matplotlib import pyplot as plt
from matplotlib import colors as mcolors
from pylab import contourf
from mpl_toolkits.mplot3d import Axes3D


import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-2]))

from processing.core import BaseReadout


class PlasmaRT(BaseReadout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        # res_dir
        self.__res_dir = self.__create_res_dir()

        # readout
        self._readout_plasma_paths()
        self._readout_parameters()
        self._readout_propagation()

        # parameters
        self.__n_r = self._parameters['grid']['n_r']
        self.__dr = self._parameters['grid']['dr']
        self.__n_t = self._parameters['grid']['n_t']
        self.__dt = self._parameters['grid']['dt']
        self.__N_0 = self._parameters['medium']['N_0']

        # mode -> flat or volume
        self.__mode = kwargs['mode']
        if self.__mode not in ('flat', 'volume'):
            raise Exception('Wrong plot mode!')

        # logarithmization
        self.__log = kwargs.get('log', True)
        if not self.__log:
            self.__maximum_plasma = kwargs['maximum_plasma']
            if isinstance(self.__maximum_plasma, str):
                if self.__maximum_plasma != 'local':
                    raise Exception('Wrong maximum plasma!')

            self.__normalize_to = kwargs['normalize_to']
            if self.__normalize_to not in (1, 'N_0'):
                raise Exception('Wrong normalize value!')

        # processing
        self.__ts = [(self.__n_t / 2 - s) * self.__dt for s in range(self.__n_t)]
        self.__rs = [k * self.__dr for k in range(self.__n_r)]
        self.__ts_cropped, self.__rs_cropped = None, None
        self.__t_left = kwargs['t_left']
        self.__t_right = kwargs['t_right']
        self.__r_right = kwargs['r_right']

        # plot
        self.__font_size = {'title': 40,  'plot_ticks': 40, 'plot_labels': 50, 'colorbar_ticks': 40, 'colorbar_label': 50}
        self.__font_weight = {'title': 'bold', 'plot_ticks': 'normal', 'plot_labels': 'bold', 'colorbar_ticks': 'bold', 'colorbar_label': 'bold'}
        self.__cmap = plt.get_cmap('jet')
        self.__t_labels = kwargs['t_labels']
        self.__r_labels = kwargs['r_labels']
        self.__t_label = self._initialize_label(self._language, 't, фс', 't, fs')
        self.__r_label = self._initialize_label(self._language, 'r, мкм', 'r, $\mathbf{\mu}$m')
        self.__bbox_width, self.__bbox_height = 10.3, 10.0
        self.__default_title_string = self._initialize_label(self._language,
                                                             'z = %05.2f см\nNe$_{макс}$ = %05.2f см$^{-3}$\n',
                                                             'z = %05.2f cm\nNe$_{max}$ = %05.2f см$^{-3}$\n')
        #self.__log_ticks = [-1.0, 0.0, +1.0]
        #self.__log_ticklabels = ['+' + str(round(e)) if e > 0 else '$-$' + str(abs(round(e))) if e != 0 else '  0'
        #                         for e in self.__log_ticks]
        self.__dpi = 100

        # flags
        self.__ticks = True
        self.__title = True
        self.__labels = True
        if self.__mode == 'flat':
            self.__colorbar = kwargs.get('colorbar', False)

    def __create_res_dir(self):
        datetime_string = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        dir_name = 'procesing_Ne(r,t)_' + datetime_string
        return self._create_dir(dir_name=dir_name)

    def __crop_r(self, arr):
        k_max = 0
        for k in range(len(self.__rs)):
            if self.__rs[k] > self.__r_right:
                k_max = k
                break

        self.__rs_cropped = self.__rs[:k_max]
        self.__rs_cropped = append([-e for e in self.__rs_cropped[::-1][:-1]], self.__rs_cropped)

        return arr[:k_max], k_max

    def __crop_t(self, arr):
        s_min = 0
        s_max = -1
        for s in range(len(self.__ts)):
            if self.__ts[s] < self.__t_left:
                s_min = s
                break
        for s in range(len(self.__ts)-1, 0, -1):
            if self.__ts[s] > self.__t_right:
                s_max = s
                break

        self.__ts_cropped = self.__ts[s_min:s_max]

        return transpose(transpose(arr)[s_min:s_max]), s_min, s_max

    @staticmethod
    def __filter_and_log_arr(arr, min_val=0.1):
        arr[where(arr < min_val)] = min_val
        return log10(arr)

    def __calc_ticks_t(self, labels):
        ticks = []
        nxt = 0
        for label in labels:
            for i in range(nxt, len(self.__ts_cropped)):
                if self.__ts_cropped[i] < float(label) * 10**-15:
                    ticks.append(i)
                    nxt = i
                    break
        return ticks

    def __calc_ticks_r(self, labels):
        ticks = []
        nxt = 0
        for label in labels:
            for i in range(nxt, len(self.__rs_cropped)):
                if self.__rs_cropped[i] > float(label) * 10**-6:
                    ticks.append(i)
                    nxt = i
                    break
        return ticks

    def __calculate_max_plasma(self, arr):
        if isinstance(self.__maximum_plasma, int) or isinstance(self.__maximum_plasma, float):
            max_plasma = self.__maximum_plasma
        else:
            max_plasma = maximum(arr) * self.__N_0

        if self.__normalize_to == 'N_0':
            max_plasma /= self.__N_0
        else:
            arr *= self.__N_0 / 10**22
            max_plasma /= 10**22

        return max_plasma

    def __calculate_levels_plot_and_max_plasma(self, arr):
        n_plot_levels = 100

        max_plasma = None
        if self.__log:
            levels_plot = [-1. + i * 0.05 for i in range(50)]
        else:
            max_plasma = self.__calculate_max_plasma(arr)

            di = max_plasma / n_plot_levels
            levels_plot = [i * di for i in range(n_plot_levels + 1)]

        return levels_plot, max_plasma

    def __plot_flat(self, arr, filename):
        fig, ax = plt.subplots(figsize=(9, 7))

        # plot
        levels_plot, max_plasma = self.__calculate_levels_plot_and_max_plasma(arr)
        plot = contourf(arr, cmap=self.__cmap, levels=levels_plot)

        # ticks
        if self.__ticks:
            t_ticks = self.__calc_ticks_t(self.__t_labels)
            r_ticks = self.__calc_ticks_r(self.__r_labels)
            plt.xticks(t_ticks, self.__t_labels, fontsize=self.__font_size['plot_ticks'])
            plt.yticks(r_ticks, self.__r_labels, fontsize=self.__font_size['plot_ticks'])
        else:
            plt.xticks([])
            plt.yticks([])

        # labels
        if self.__labels:
            plt.xlabel(self.__t_label, fontsize=self.__font_size['plot_labels'], fontweight=self.__font_weight['plot_labels'])
            plt.ylabel(self.__r_label, fontsize=self.__font_size['plot_labels'], fontweight=self.__font_weight['plot_labels'],
                       labelpad=-30)

        plt.grid(color='white', linestyle=':', linewidth=3, alpha=0.5)

        # title
        if self.__title:
            z = self._find_z(filename)
            i_max = self._find_i_max(filename)
            plt.title((self.__default_title_string + '\n') % (z, i_max), fontsize=self.__font_size['title'])

        # # colorbar
        # if self.__colorbar:
        #     if self.__log:
        #         colorbar = fig.colorbar(plot, ticks=self.__log_ticks, orientation='vertical', aspect=10, pad=0.05)
        #         colorbar.set_label('lg(I/I$\mathbf{_0}$)', labelpad=-90, y=1.2, rotation=0,
        #                            fontsize=self.__font_size['colorbar_label'], fontweight=self.__font_weight['colorbar_label'])
        #         colorbar.ax.set_yticklabels(self.__log_ticklabels)
        #         colorbar.ax.tick_params(labelsize=self.__font_size['colorbar_ticks'])
        #     else:
        #         n_ticks_colorbar_levels = 4
        #         dcb = max_intensity / n_ticks_colorbar_levels
        #         levels_ticks_colorbar = [i * dcb for i in range(n_ticks_colorbar_levels + 1)]
        #         colorbar = fig.colorbar(plot, ticks=levels_ticks_colorbar, orientation='vertical', aspect=10, pad=0.05)
        #         if self.__normalize_to == 'i_0':
        #             colorbar_label = 'I/I$\mathbf{_0}$'
        #             colorbar.set_label(colorbar_label, labelpad=-60, y=1.25, rotation=0,
        #                                fontsize=self.__font_size['colorbar_label'],
        #                                fontweight=self.__font_weight['colorbar_label'])
        #         else:
        #             colorbar_label = self._initialize_label(self._language,
        #                                                     'I,\nТВт/см$\mathbf{^2}$',
        #                                                     'I,\nTW/cm$\mathbf{^2}$')
        #             colorbar.set_label(colorbar_label, labelpad=-100, y=1.4, rotation=0,
        #                                fontsize=self.__font_size['colorbar_label'],
        #                                fontweight=self.__font_weight['colorbar_label'])
        #
        #         ticks_cbar = ['%05.2f' % e if e != 0 else '00.00' for e in levels_ticks_colorbar]
        #
        #         colorbar.ax.set_yticklabels(ticks_cbar)
        #         colorbar.ax.tick_params(labelsize=self.__font_size['colorbar_ticks'])

        # bbox
        bbox = fig.bbox_inches.from_bounds(-0.8, -1.0, self.__bbox_width, self.__bbox_height)

        plt.savefig(self.__res_dir + '/' + filename + '.png', bbox_inches=bbox, dpi=self.__dpi)
        plt.close()

    def __plot_volume(self, arr, filename):
        pass

        # fig = plt.figure(figsize=(12, 10))
        # ax = fig.add_subplot(111, projection='3d')
        #
        # # plot
        # levels_plot, _ = self.__calculate_levels_plot_and_max_intensity(arr)
        # rs, ts = [e * 10**6 for e in self.__rs_cropped], [e * 10**15 for e in self.__ts_cropped]
        # tt, rr = meshgrid(ts, rs)
        # ax.plot_surface(rr, tt, arr, cmap=self.__cmap, rstride=1, cstride=1, antialiased=False,
        #                 vmin=levels_plot[0], vmax=levels_plot[-1])
        # ax.view_init(elev=50, azim=345)
        #
        # if self.__ticks:
        #     plt.xticks([int(e) for e in self.__r_labels], [e + '      ' for e in self.__r_labels[::-1]],
        #                fontsize=self.__font_size['plot_ticks'])
        #     plt.yticks([int(e) for e in self.__t_labels], [e for e in self.__t_labels[::-1]],
        #                fontsize=self.__font_size['plot_ticks'])
        #     ax.xaxis.set_tick_params(pad=5)
        #     ax.yaxis.set_tick_params(pad=5)
        #
        #     if self.__log:
        #         ax.set_zlim([levels_plot[0], levels_plot[-1]])
        #         ax.set_zticks(self.__log_ticks)
        #         ax.set_zticklabels(self.__log_ticklabels)
        #         ax.tick_params(labelsize=self.__font_size['plot_ticks'])
        #         ax.zaxis.set_tick_params(pad=20)
        #     else:
        #         n_z_ticks = 3
        #         di0 = levels_plot[-1] / n_z_ticks
        #         prec = 2
        #         zticks = [i * di0 for i in range(n_z_ticks + 1)]
        #         zticklabels = ['%05.2f' % (int(e * 10 ** prec) / 10 ** prec) for e in zticks]
        #         ax.set_zlim([levels_plot[0], levels_plot[-1]])
        #         ax.set_zticks(zticks)
        #         ax.set_zticklabels(zticklabels)
        #         ax.tick_params(labelsize=self.__font_size['plot_ticks'])
        #         ax.zaxis.set_tick_params(pad=30)
        #
        # else:
        #     plt.xticks([])
        #     plt.yticks([])
        #     ax.set_zticks([])
        #
        # if self.__labels:
        #     plt.xlabel('\n\n\n\n' + self.__r_label, fontsize=self.__font_size['plot_labels'],
        #                fontweight=self.__font_weight['plot_labels'])
        #     plt.ylabel('\n\n' + self.__t_label, fontsize=self.__font_size['plot_labels'],
        #                fontweight=self.__font_weight['plot_labels'])
        #     if self.__log:
        #         z_label = '$\qquad\qquad\quad \ $lg\n$\qquad\quad\quad \ \ $(I/I$\mathbf{_0}$)'
        #     else:
        #         if self.__normalize_to == 'i_0':
        #             z_label = '$\qquad\qquad\quad$ I/I$\mathbf{_0}$'
        #         else:
        #             z_label = self._initialize_label(self._language,
        #                                              '$\qquad\qquad\qquad\mathbf{I}$\n$\qquad\qquad\quad$ТВт/\n$\quad\qquad\qquad$см$\mathbf{^2}$',
        #                                              '$\qquad\qquad\qquad\mathbf{I}$\n$\qquad\qquad\quad$TW/\n$\quad\qquad\qquad$cm$\mathbf{^2}$')
        #     ax.text(0, 0, levels_plot[-1] * 0.8, s=z_label, fontsize=self.__font_size['plot_labels'],
        #             fontweight=self.__font_weight['plot_labels'])
        #
        # # title
        # if self.__title:
        #     z = self._find_z(filename)
        #     i_max = self._find_i_max(filename)
        #     plt.title(self.__default_title_string % (z, i_max), fontsize=self.__font_size['title'])
        #
        # # white background
        # ax.w_xaxis.set_pane_color(mcolors.to_rgba('white'))
        # ax.w_yaxis.set_pane_color(mcolors.to_rgba('white'))
        # ax.w_zaxis.set_pane_color(mcolors.to_rgba('white'))
        #
        # # bbox
        # bbox = fig.bbox_inches.from_bounds(1.1, 0.3, self.__bbox_width, self.__bbox_height)
        #
        # plt.savefig(self.__res_dir + '/' + filename + '.png', bbox_inches=bbox, dpi=self.__dpi)
        # plt.close()

    def process(self):
        s_min, s_max, k_max = None, None, None
        for idx, path in enumerate(self._plasma_paths):
            filename = path.split('/')[-1]

            arr = loadtxt(path, skiprows=0)

            if not idx:
                arr, s_min, s_max = self.__crop_t(arr)
                arr, k_max = self.__crop_r(arr)
            else:
                arr = arr[:, s_min:s_max]
                arr = arr[:k_max, :]

            arr = self._reflect(arr)

            #if self.__log:
            #    arr = self.__filter_and_log_arr(arr)

            if self.__mode == 'flat':
                self.__plot_flat(arr, filename)
            elif self.__mode == 'volume':
                self.__plot_volume(arr, filename)
            else:
                raise Exception('Wrong plot mode!')

            del arr
