from numpy import where, log10, zeros
from numpy import max as maximum
from numba import jit
from matplotlib import pyplot as plt

from .base_rt import BaseRT


class BaseIntensityRT(BaseRT):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        # parameters
        self._I_0 = self._parameters['pulsed_beam']['I_0']

        # scale
        self._initialize_scale(1e13, 1e19, (1, 'I_0'), **kwargs)

        self._log_ticks = kwargs['log_ticks']

        # plot
        self._cmap = plt.get_cmap('jet')

        # readout paths
        src_dir = '/'.join([self._args.current_results_dir, 'field'])
        self._readout_paths(src_dir)

        self._default_title_string = self._initialize_language_string(self._language,
                                                                      'z = %05.2f см\nI$_{макс}$ = %05.2f ТВт/см$^2$\n',
                                                                      'z = %05.2f cm\nI$_{max}$ = %05.2f TW/cm$^2$\n')

    @staticmethod
    def _filter_and_log_arr(arr, min_val=0.1):
        arr[where(arr < min_val)] = min_val
        return log10(arr)

    @staticmethod
    @jit(nopython=True)
    def _a_to_i(arr):
        arr_i = zeros((arr.shape[0], int(arr.shape[1]/2)))
        for k in range(arr.shape[0]):
            idx = 0
            for s in range(0, arr.shape[1], 2):
                arr_i[k, idx] = arr[k, s]**2 + arr[k, s+1]**2
                idx += 1
        return arr_i

    def _initialize_levels_plot_and_max_intensity(self, arr):
        if self._log:
            levels_plot = [-1. + i * 0.05 for i in range(50)]
            max_intensity = None
        else:
            n_plot_levels = 100

            # calculate intensity
            if isinstance(self._maximum, int) or isinstance(self._maximum, float):
                max_intensity = self._maximum
            else:
                max_intensity = maximum(arr) * self._I_0

            if self._normalize_to == 'I_0':
                max_intensity /= self._I_0
            else:
                arr *= self._I_0 / 10**16
                max_intensity /= 10**16

            di = max_intensity / n_plot_levels
            levels_plot = [i * di for i in range(n_plot_levels + 1)]

        return levels_plot, max_intensity