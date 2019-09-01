from datetime import datetime
from numpy import loadtxt, transpose, append, where, log10, meshgrid
from numpy import max as maximum
from matplotlib import pyplot as plt
from matplotlib import colors as mcolors
from pylab import contourf
from mpl_toolkits.mplot3d import Axes3D


import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-2]))

from processing.core.rt.base_plasma_rt import BasePlasmaRT
from .base_rt_flat import BaseRTFlat


class PlasmaRTFlat(BasePlasmaRT, BaseRTFlat):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.__colorbar = kwargs['colorbar']

        # plot
        self._initialize_log_tickslabels(self._log_ticks_prec)

    def __initialize_colorbar(self, fig, plot, max_intensity):
        if self.__colorbar:
            if self._log:
                colorbar = fig.colorbar(plot, ticks=self._log_ticks, orientation='vertical', aspect=10, pad=0.05)
                colorbar.set_label('lg(N$\mathbf{_e}$/N$\mathbf{_0}$)', labelpad=-60, y=1.07, rotation=0,
                                   fontsize=self._font_size['colorbar_label'], fontweight=self._font_weight['colorbar_label'])
                colorbar.ax.set_yticklabels(self._log_ticklabels)
                colorbar.ax.tick_params(labelsize=self._font_size['colorbar_ticks'])
            else:
                pass
                # n_ticks_colorbar_levels = 4
                # dcb = max_intensity / n_ticks_colorbar_levels
                # levels_ticks_colorbar = [i * dcb for i in range(n_ticks_colorbar_levels + 1)]
                # colorbar = fig.colorbar(plot, ticks=levels_ticks_colorbar, orientation='vertical', aspect=10, pad=0.05)
                #
                # if self._normalize_to == 'I_0':
                #     label_pad = -120
                #     y = 1.07
                # else:
                #     label_pad = -120
                #     y = 1.1
                #
                # if self._normalize_to == 'I_0':
                #     colorbar_label = 'I/I$\mathbf{_0}$'
                #     colorbar.set_label(colorbar_label, labelpad=label_pad, y=y, rotation=0,
                #                        fontsize=self._font_size['colorbar_label'],
                #                        fontweight=self._font_weight['colorbar_label'])
                # else:
                #     colorbar_label = self._initialize_language_string(self._language,
                #                                                       'I,\nТВт/см$\mathbf{^2}$',
                #                                                       'I,\nTW/cm$\mathbf{^2}$')
                #     colorbar.set_label(colorbar_label, labelpad=label_pad, y=y, rotation=0,
                #                        fontsize=self._font_size['colorbar_label'],
                #                        fontweight=self._font_weight['colorbar_label'])
                #
                # ticks_cbar = ['%05.2f' % e if e != 0 else '00.00' for e in levels_ticks_colorbar]
                #
                # colorbar.ax.set_yticklabels(ticks_cbar)
                # colorbar.ax.tick_params(labelsize=self._font_size['colorbar_ticks'])

    def _plot(self, arr, filename):

        # figure
        fig, ax = plt.subplots(figsize=self._fig_size)

        # plot
        levels_plot, max_intensity = self._initialize_levels_plot_and_max_plasma(arr)
        plot = contourf(arr, cmap=self._cmap, levels=levels_plot)

        # ticks
        self._initialize_ticks()

        # labels
        self._initialize_labels()

        # grid
        self._initialize_grid()

        # title
        if self._title:
            z = self._find_z(filename)
            Ne_max_rel = self._find_Ne_max(filename) / self._N_0 * 10**4
            plt.title((self._default_title_string + '\n') % (z, Ne_max_rel), fontsize=self._font_size['title'])

        # colorbar
        self.__initialize_colorbar(fig, plot, max_intensity)

        # aspect
        self._initialize_aspect(ax)

        # bbox
        bbox = self._initialize_bbox(fig)

        fig.savefig(self._res_dir + '/' + filename + '.png', bbox_inches=bbox, dpi=self._dpi)
        plt.close()

    def process(self):
        s_min, s_max, k_max = None, None, None
        for idx, path in enumerate(self._paths):
            filename = path.split('/')[-1]

            arr = loadtxt(path, skiprows=0)

            s_min, s_max, k_max = self._process_iteration(idx, filename, arr, s_min, s_max, k_max)
