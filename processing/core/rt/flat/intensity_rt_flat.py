from datetime import datetime
from numpy import loadtxt, transpose, append, where, log10, meshgrid, zeros
from numpy import max as maximum
from matplotlib import pyplot as plt
from matplotlib import colors as mcolors
from pylab import contourf
from mpl_toolkits.mplot3d import Axes3D
from numba import jit

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-3]))

from processing.core.rt.base_intensity_rt import BaseIntensityRT
from .base_rt_flat import BaseRTFlat


class IntensityRTFlat(BaseIntensityRT, BaseRTFlat):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.__colorbar = kwargs['colorbar']

        # plot
        self._initialize_log_tickslabels(self._log_ticks_prec)

    def __initialize_colorbar(self, fig, plot, max_intensity):
        if self.__colorbar:
            if self._log:
                colorbar = fig.colorbar(plot, ticks=self._log_ticks, orientation='vertical', aspect=10, pad=0.05)
                colorbar.set_label('lg(I/I$\mathbf{_0}$)', labelpad=-105, y=1.07, rotation=0,
                                   fontsize=self._font_size['colorbar_label'], fontweight=self._font_weight['colorbar_label'])
                colorbar.ax.set_yticklabels(self._log_ticklabels)
                colorbar.ax.tick_params(labelsize=self._font_size['colorbar_ticks'])
            else:
                n_ticks_colorbar_levels = 4
                dcb = max_intensity / n_ticks_colorbar_levels
                levels_ticks_colorbar = [i * dcb for i in range(n_ticks_colorbar_levels + 1)]
                colorbar = fig.colorbar(plot, ticks=levels_ticks_colorbar, orientation='vertical', aspect=10, pad=0.05)

                if self._normalize_to == 'I_0':
                    label_pad = -120
                    y = 1.07
                else:
                    label_pad = -120
                    y = 1.1

                if self._normalize_to == 'I_0':
                    colorbar_label = 'I/I$\mathbf{_0}$'
                    colorbar.set_label(colorbar_label, labelpad=label_pad, y=y, rotation=0,
                                       fontsize=self._font_size['colorbar_label'],
                                       fontweight=self._font_weight['colorbar_label'])
                else:
                    colorbar_label = self._initialize_language_string(self._language,
                                                                      'I,\nТВт/см$\mathbf{^2}$',
                                                                      'I,\nTW/cm$\mathbf{^2}$')
                    colorbar.set_label(colorbar_label, labelpad=label_pad, y=y, rotation=0,
                                       fontsize=self._font_size['colorbar_label'],
                                       fontweight=self._font_weight['colorbar_label'])

                ticks_cbar = ['%05.2f' % e if e != 0 else '00.00' for e in levels_ticks_colorbar]

                colorbar.ax.set_yticklabels(ticks_cbar)
                colorbar.ax.tick_params(labelsize=self._font_size['colorbar_ticks'])

    def _plot(self, arr, filename):

        # figure
        fig, ax = plt.subplots(figsize=self._fig_size)

        # plot
        levels_plot, max_intensity = self._initialize_levels_plot_and_max_intensity(arr)
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
            i_max = self._find_I_max(filename)
            plt.title((self._default_title_string + '\n') % (z, i_max), fontsize=self._font_size['title'])

        # colorbar
        self.__initialize_colorbar(fig, plot, max_intensity)

        # aspect
        self._initialize_aspect(ax)

        # bbox
        bbox = self._initialize_bbox(fig)

        fig.savefig(self._res_dir + '/' + filename + '.png', bbox_inches=bbox, dpi=self._dpi)
        plt.close()

    # def __plot_3D(self, arr, filename):
    #     fig = plt.figure(figsize=(12, 10))
    #     ax = fig.add_subplot(111, projection='3d')
    #
    #     # plot
    #     levels_plot, _ = self.__calculate_levels_plot_and_max_intensity(arr)
    #     rs, ts = [e * 10**6 for e in self.__rs_cropped], [e * 10**15 for e in self.__ts_cropped]
    #     tt, rr = meshgrid(ts, rs)
    #     ax.plot_surface(rr, tt, arr, cmap=self.__cmap, rstride=1, cstride=1, antialiased=False,
    #                     vmin=levels_plot[0], vmax=levels_plot[-1])
    #     ax.view_init(elev=50, azim=345)
    #
    #     if self.__ticks:
    #         plt.xticks([int(e) for e in self.__r_labels], [e + '      ' for e in self.__r_labels[::-1]],
    #                    fontsize=self.__font_size['plot_ticks'])
    #         plt.yticks([int(e) for e in self.__t_labels], [e for e in self.__t_labels[::-1]],
    #                    fontsize=self.__font_size['plot_ticks'])
    #         ax.xaxis.set_tick_params(pad=5)
    #         ax.yaxis.set_tick_params(pad=5)
    #
    #         if self.__log:
    #             ax.set_zlim([levels_plot[0], levels_plot[-1]])
    #             ax.set_zticks(self.__log_ticks)
    #             ax.set_zticklabels(self.__log_ticklabels)
    #             ax.tick_params(labelsize=self.__font_size['plot_ticks'])
    #             ax.zaxis.set_tick_params(pad=20)
    #         else:
    #             n_z_ticks = 3
    #             di0 = levels_plot[-1] / n_z_ticks
    #             prec = 2
    #             zticks = [i * di0 for i in range(n_z_ticks + 1)]
    #             zticklabels = ['%05.2f' % (int(e * 10 ** prec) / 10 ** prec) for e in zticks]
    #             ax.set_zlim([levels_plot[0], levels_plot[-1]])
    #             ax.set_zticks(zticks)
    #             ax.set_zticklabels(zticklabels)
    #             ax.tick_params(labelsize=self.__font_size['plot_ticks'])
    #             ax.zaxis.set_tick_params(pad=30)
    #
    #     else:
    #         plt.xticks([])
    #         plt.yticks([])
    #         ax.set_zticks([])
    #
    #     if self.__labels:
    #         plt.xlabel('\n\n\n\n' + self.__r_label, fontsize=self.__font_size['plot_labels'],
    #                    fontweight=self.__font_weight['plot_labels'])
    #         plt.ylabel('\n\n' + self.__t_label, fontsize=self.__font_size['plot_labels'],
    #                    fontweight=self.__font_weight['plot_labels'])
    #         if self.__log:
    #             z_label = '$\qquad\qquad\quad \ $lg\n$\qquad\quad\quad \ \ $(I/I$\mathbf{_0}$)'
    #         else:
    #             if self.__normalize_to == 'i_0':
    #                 z_label = '$\qquad\qquad\quad$ I/I$\mathbf{_0}$'
    #             else:
    #                 z_label = self._initialize_label(self._language,
    #                                                  '$\qquad\qquad\qquad\mathbf{I}$\n$\qquad\qquad\quad$ТВт/\n$\quad\qquad\qquad$см$\mathbf{^2}$',
    #                                                  '$\qquad\qquad\qquad\mathbf{I}$\n$\qquad\qquad\quad$TW/\n$\quad\qquad\qquad$cm$\mathbf{^2}$')
    #         ax.text(0, 0, levels_plot[-1] * 0.8, s=z_label, fontsize=self.__font_size['plot_labels'],
    #                 fontweight=self.__font_weight['plot_labels'])
    #
    #     # title
    #     if self.__title:
    #         z = self._find_z(filename)
    #         i_max = self._find_i_max(filename)
    #         plt.title(self.__default_title_string % (z, i_max), fontsize=self.__font_size['title'])
    #
    #     # white background
    #     ax.w_xaxis.set_pane_color(mcolors.to_rgba('white'))
    #     ax.w_yaxis.set_pane_color(mcolors.to_rgba('white'))
    #     ax.w_zaxis.set_pane_color(mcolors.to_rgba('white'))
    #
    #     # bbox
    #     bbox = None
    #     if self.__style_mode == 'analysis':
    #         bbox = 'tight'
    #     elif self.__style_mode == 'multimedia':
    #         bbox = fig.bbox_inches.from_bounds(1.1, 0.3, 10.3, 10.0)
    #
    #     fig.savefig(self.__res_dir + '/' + filename + '.png', bbox_inches=bbox, dpi=self.__dpi)
    #     plt.close()

    def process(self):
        s_min, s_max, k_max = None, None, None
        for idx, path in enumerate(self._paths):
            filename = path.split('/')[-1]

            arr = loadtxt(path, skiprows=0)
            arr = self._a_to_i(arr)

            s_min, s_max, k_max = self._process_iteration(idx, filename, arr, s_min, s_max, k_max)
