from datetime import datetime
from numpy import loadtxt, transpose, append, where, log10
from numpy import max as maximum
from matplotlib import pyplot as plt
from pylab import contourf

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-2]))

from processing.core import BaseReadout


class IntensityRT(BaseReadout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        # res_dir
        self.__res_dir = self.__create_res_dir()

        # readout
        self._readout_field_paths()
        self._readout_parameters()
        self._readout_propagation()

        # parameters
        self.__n_t = self._parameters['grid']['n_t']
        self.__h_t = self._parameters['grid']['h_t']
        self.__n_r = self._parameters['grid']['n_r']
        self.__h_r = self._parameters['grid']['h_r']
        self.__i_0 = self._parameters['pulsed_beam']['i_0']

        # mode -> flat or volume
        self.__mode = kwargs['mode']
        if self.__mode not in ('flat', 'volume'):
            raise Exception('Wrong plot mode!')

        # logarithmization
        self.__log = kwargs.get('log', True)
        if not self.__log:
            self.__maximum_intensity = kwargs['maximum_intensity']
            if isinstance(self.__maximum_intensity, str):
                if self.__maximum_intensity != 'local':
                    raise Exception('Wrong maximum intensty!')

            self.__normalize_to = kwargs['normalize_to']
            if self.__normalize_to not in (1, 'i_0'):
                raise Exception('Wrong normalize value!')

        # processing
        self.__ts = [(self.__n_t / 2 - s) * self.__h_t for s in range(self.__n_t)]
        self.__rs = [k * self.__h_r for k in range(self.__n_r)]
        self.__ts_cropped, self.__rs_cropped = None, None
        self.__t_left = kwargs['t_left']
        self.__t_right = kwargs['t_right']
        self.__r_right = kwargs['r_right']

        # plot
        self.__fig_size = (9, 7)
        self.__font_size = {'title': 40,  'plot_ticks': 40, 'plot_labels': 50, 'colorbar_ticks': 40, 'colorbar_label': 50}
        self.__font_weight = {'title': 'bold', 'plot_ticks': 'normal', 'plot_labels': 'bold', 'colorbar_ticks': 'bold', 'colorbar_label': 'bold'}
        self.__cmap = plt.get_cmap('jet')
        self.__t_labels = kwargs['t_labels']
        self.__r_labels = kwargs['r_labels']
        self.__t_label = self._initialize_label('t, фс', 't, fs')
        self.__r_label = self._initialize_label('r, мкм', 'r, $\mathbf{\mu}$m')
        self.__bbox_width, self.__bbox_height = 10.3, 10.0
        self.__title = True
        self.__default_title_string = self._initialize_label('z = %05.2f см\nI$_{макс}$ = %05.2f ТВт/см$^2$\n',
                                                             'z = %05.2f cm\nI$_{max}$ = %05.2f TW/cm$^2$\n')
        self.__dpi = 50

    def __create_res_dir(self):
        datetime_string = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        dir_name = 'procesing_i(r,t)_' + datetime_string
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

    def process(self):
        s_min, s_max, k_max = None, None, None
        for idx, path in enumerate(self._field_paths):
            filename = path.split('/')[-1]

            arr = loadtxt(path, skiprows=0)
            arr = self._a_to_i(arr)

            if not idx:
                arr, s_min, s_max = self.__crop_t(arr)
                arr, k_max = self.__crop_r(arr)
            else:
                arr = arr[:, s_min:s_max]
                arr = arr[:k_max, :]

            arr = self._reflect(arr)

            if self.__log:
                arr = self.__filter_and_log_arr(arr)

            if self.__mode == 'flat':
                self.__plot_flat(arr, filename)

    def __calculate_max_intensity(self, arr):
        if isinstance(self.__maximum_intensity, int) or isinstance(self.__maximum_intensity, float):
            max_intensity = self.__maximum_intensity
        else:
            max_intensity = maximum(arr) * self.__i_0

        if self.__normalize_to == 'i_0':
            max_intensity /= self.__i_0
        else:
            arr *= self.__i_0 / 10**16
            max_intensity /= 10**16

        return max_intensity

    def __calculate_levels_plot_and_max_intensity(self, arr):
        n_plot_levels = 100

        max_intensity = None
        if self.__log:
            levels_plot = [-1. + i * 0.05 for i in range(50)]
        else:
            max_intensity = self.__calculate_max_intensity(arr)

            di = max_intensity / n_plot_levels
            levels_plot = [i * di for i in range(n_plot_levels + 1)]

        return levels_plot, max_intensity

    def __plot_flat(self, arr, filename):
        levels_plot, max_intensity = self.__calculate_levels_plot_and_max_intensity(arr)

        fig, ax = plt.subplots(figsize=self.__fig_size)
        plot = contourf(arr, cmap=self.__cmap, levels=levels_plot)

        t_ticks = self.__calc_ticks_t(self.__t_labels)
        r_ticks = self.__calc_ticks_r(self.__r_labels)

        plt.xticks(t_ticks, self.__t_labels, fontsize=self.__font_size['plot_ticks'])
        plt.yticks(r_ticks, self.__r_labels, fontsize=self.__font_size['plot_ticks'])

        plt.xlabel(self.__t_label, fontsize=self.__font_size['plot_labels'], fontweight=self.__font_weight['plot_labels'])
        plt.ylabel(self.__r_label, fontsize=self.__font_size['plot_labels'], fontweight=self.__font_weight['plot_labels'],
                   labelpad=-30)

        plt.grid(color='white', linestyle=':', linewidth=3, alpha=0.5)

        # title
        if self.__title:
            z = self._find_z(filename)
            i_max = self._find_i_max(filename)
            plt.title((self.__default_title_string + '\n') % (z, i_max), fontsize=self.__font_size['title'])

        # colorbar
        colorbar = True
        if self.__log:
            ticklevels_colorbar = [-1.0, 0, +1.0]
            colorbar = fig.colorbar(plot, ticks=ticklevels_colorbar, orientation='vertical', aspect=10, pad=0.05)
            colorbar.set_label('lg(I/I$\mathbf{_0}$)', labelpad=-90, y=1.2, rotation=0,
                               fontsize=self.__font_size['colorbar_label'], fontweight=self.__font_weight['colorbar_label'])
            ticks_cbar = ['+' + str(round(e)) if e > 0 else '$-$' + str(abs(round(e))) if e != 0 else '  0'
                          for e in ticklevels_colorbar]
            colorbar.ax.set_yticklabels(ticks_cbar)
            colorbar.ax.tick_params(labelsize=self.__font_size['colorbar_ticks'])
        else:
            if colorbar:
                n_ticks_colorbar_levels = 4
                dcb = max_intensity / n_ticks_colorbar_levels
                levels_ticks_colorbar = [i * dcb for i in range(n_ticks_colorbar_levels + 1)]
                colorbar = fig.colorbar(plot, ticks=levels_ticks_colorbar, orientation='vertical', aspect=10, pad=0.05)
                if self.__normalize_to == 'i_0':
                    colorbar_label = 'I/I$\mathbf{_0}$'
                    colorbar.set_label(colorbar_label, labelpad=-60, y=1.25, rotation=0,
                                       fontsize=self.__font_size['colorbar_label'],
                                       fontweight=self.__font_weight['colorbar_label'])
                else:
                    colorbar_label = self._initialize_label('I,\nТВт/см$\mathbf{^2}$',
                                                            'I,\nTW/cm$\mathbf{^2}$')
                    colorbar.set_label(colorbar_label, labelpad=-100, y=1.4, rotation=0,
                                       fontsize=self.__font_size['colorbar_label'],
                                       fontweight=self.__font_weight['colorbar_label'])

                ticks_cbar = ['%05.2f' % e if e != 0 else '00.00' for e in levels_ticks_colorbar]

                colorbar.ax.set_yticklabels(ticks_cbar)
                colorbar.ax.tick_params(labelsize=self.__font_size['colorbar_ticks'])

        # bbox
        bbox = fig.bbox_inches.from_bounds(-0.8, -1.0, self.__bbox_width, self.__bbox_height)

        plt.savefig(self.__res_dir + '/' + filename + '.png', bbox_inches=bbox, dpi=self.__dpi)
        plt.close()

    def plot_volume(self):
        pass


