import os
import sys
from datetime import datetime
from numpy import loadtxt, transpose, append, where, log10
from matplotlib import pyplot as plt
from pylab import contourf

# right relative path
sys.path.insert(0, os.getcwd().replace('\\', '/'))

from processing.core import parse_args, BaseReadout


class IntensityRT(BaseReadout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.__mode = kwargs['mode']
        if self.__mode not in ('flat', 'volume'):
            raise Exception('Wrong plot mode!')

        self.__res_dir = self.__create_res_dir()

        self._readout_field_paths()
        self._readout_parameters()

        self.__n_t = self._parameters['grid']['n_t']
        self.__h_t = self._parameters['grid']['h_t']
        self.__ts = [(self.__n_t / 2 - s) * self.__h_t for s in range(self.__n_t)]

        self.__n_r = self._parameters['grid']['n_r']
        self.__h_r = self._parameters['grid']['h_r']
        self.__rs = [k * self.__h_r for k in range(self.__n_r)]

        self.__ts_cropped, self.__rs_cropped = None, None

        self.__t_left = kwargs['t_left']
        self.__t_right = kwargs['t_right']
        self.__r_right = kwargs['r_right']

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
            arr = self.__filter_and_log_arr(arr)

            if self.__mode == 'flat':
                self.__plot_flat(arr, filename)

    def __plot_flat(self, arr, filename):
        font_sizes = {'plot_ticks': 35, 'plot_labels': 40, 'colorbar_ticks': 40, 'colorbar_label': 40}
        font_weights = {'plot_ticks': 'normal', 'plot_labels': 'bold', 'colorbar_ticks': 'normal', 'colorbar_label': 'bold'}
        cmap = plt.get_cmap('jet')
        levels_plot = [-1. + i * 0.05 for i in range(50)]
        title = True

        fig, ax = plt.subplots(figsize=(22, 15))
        plot = contourf(arr, cmap=cmap, levels=levels_plot)
        x_labels = ['+100', '+50', '0', '-50', '-100']
        x_ticks = self.__calc_ticks_t(x_labels)
        y_labels = ['-150', '-100', '-50', '0', '+50', '+100', '+150']
        y_ticks = self.__calc_ticks_r(y_labels)

        plt.xticks(x_ticks, x_labels, fontsize=font_sizes['plot_ticks'])
        plt.yticks(y_ticks, y_labels, fontsize=font_sizes['plot_ticks'])

        xlabel = self._initialize_label(self._language, 't, фс', 't, fs')
        ylabel = self._initialize_label(self._language, 'r, мкм', 'r, $\mu$m')
        plt.xlabel(xlabel, fontsize=font_sizes['plot_labels'], fontweight=font_weights['plot_labels'])
        plt.ylabel(ylabel, fontsize=font_sizes['plot_labels'], fontweight=font_weights['plot_labels'])

        #if title:
        #   title_string = 'z = ' + str(round(z * 10**2, 3)) + ' cm\nI$_{max}$ = ' + '%.2E' % I_max + ' W/m$^2$'

        plt.grid(color='white', linestyle=':', linewidth=3, alpha=0.5)

        # colorbar
        ticklevels_colorbar = [-1.0, 0, +1.0]
        colorbar = fig.colorbar(plot, ticks=ticklevels_colorbar, orientation='vertical', aspect=10, pad=0.05)
        colorbar.set_label('lg(I/I$\mathbf{_0}$)', labelpad=-110, y=1.1, rotation=0,
                           fontsize=font_sizes['colorbar_label'], fontweight=font_weights['colorbar_label'])
        ticks_cbar = ['+' + str(round(e)) if e > 0 else '$-$' + str(abs(round(e))) if e != 0 else '  0'
                      for e in ticklevels_colorbar]
        colorbar.ax.set_yticklabels(ticks_cbar)
        colorbar.ax.tick_params(labelsize=font_sizes['colorbar_ticks'])

        plt.savefig(self.__res_dir + '/' + filename + '.png', bbox_inches='tight')
        plt.close()

    def plot_volume(self):
        pass


# parse args from command line
args = parse_args()
plot_intensity_rt = IntensityRT(args=args,
                                mode='flat',
                                language='russian',
                                t_left=150 * 10**-15,
                                t_right=-150 * 10**-15,
                                r_right=200 * 10**-6)
plot_intensity_rt.process()
