from numpy import where, log10, zeros
from numpy import max as maximum
from numba import jit
from matplotlib import pyplot as plt

from .base_rt import BaseRT


class BasePlasmaRT(BaseRT):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        # parameters
        self._N_0 = self._parameters['medium']['N_0']

        # scale
        self._initialize_scale(10**20, 10**30, (1, 'N_0'), **kwargs)

        self._log_ticks = kwargs['log_ticks']

        # plot
        self._cmap = plt.get_cmap('hot')

        # readout paths
        src_dir = '/'.join([self._args.current_results_dir, 'plasma'])
        self._readout_paths(src_dir)

        self._default_title_string = self._initialize_language_string(self._language,
                                                                      'z = %05.2f см\nN$_{e(макс)}$ / N$_0$ $\\times 10^4$ = %.4f\n',
                                                                      'z = %05.2f cm\nN$_{e(max)}$ / N$_0$ $\\times 10^4$ = %.4f\n')

    def _filter_and_log_arr(self, arr, min_val=10**-8):
        arr /= self._N_0
        arr[where(arr < min_val)] = min_val
        return log10(arr)

    def _initialize_levels_plot_and_max_plasma(self, arr):
        if self._log:
            levels_plot = [-8. + i * 0.1 for i in range(50)]
            max_intensity = None
        else:
            pass
            # n_plot_levels = 100
            #
            # # calculate intensity
            # if isinstance(self._maximum, int) or isinstance(self._maximum, float):
            #     max_intensity = self._maximum
            # else:
            #     max_intensity = maximum(arr) * self._I_0
            #
            # if self._normalize_to == 'I_0':
            #     max_intensity /= self._I_0
            # else:
            #     arr *= self._I_0 / 10**16
            #     max_intensity /= 10**16
            #
            # di = max_intensity / n_plot_levels
            # levels_plot = [i * di for i in range(n_plot_levels + 1)]

        return levels_plot, max_intensity