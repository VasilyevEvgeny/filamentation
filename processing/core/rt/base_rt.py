from datetime import datetime
from numpy import loadtxt, transpose, append, where, log10, meshgrid
from glob import glob
from numpy import copy
from numpy import max as maximum
from matplotlib import pyplot as plt
from matplotlib import colors as mcolors
from pylab import contourf
from mpl_toolkits.mplot3d import Axes3D

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-2]))

from processing.core import BaseReadout


class BaseRT(BaseReadout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self._paths = []

        # res_dir
        self._res_dir_name = kwargs['res_dir_name']
        self._res_dir = self._create_res_dir(self._res_dir_name)

        # readout from parameters.yml
        self._n_r = self._parameters['grid']['n_r']
        self._dr = self._parameters['grid']['dr']
        self._n_t = self._parameters['grid']['n_t']
        self._dt = self._parameters['grid']['dt']

        # processing
        self._ts = [(self._n_t / 2 - s) * self._dt for s in range(self._n_t)]
        self._rs = [k * self._dr for k in range(self._n_r)]
        self._ts_cropped, self._rs_cropped = None, None

        # axes labels
        self._t_label = self._initialize_language_string(self._language, 't, фс', 't, fs')
        self._r_label = self._initialize_language_string(self._language, 'r, мкм', 'r, $\mathbf{\mu}$m')

        # readout plot parameters
        self._t_left = kwargs['t_left']
        self._t_right = kwargs['t_right']
        self._t_labels = kwargs['t_labels']
        self._r_right = kwargs['r_right']
        self._r_labels = kwargs['r_labels']
        self._fig_size = kwargs['fig_size']
        self._font_size = kwargs['font_size']
        self._font_weight = kwargs['font_weight']
        self._aspect = kwargs['aspect']
        self._ticks = kwargs['ticks']
        self._title = kwargs['title']
        self._labels = kwargs['labels']
        self._bbox = kwargs['bbox']
        self._dpi = kwargs['dpi']

        self._log_ticks_prec = kwargs['log_ticks_prec']

    def _readout_paths(self, src_dir):
        for path in glob(src_dir + '/*'):
            self._paths.append(path.replace('\\', '/'))

    def _create_res_dir(self, dir_name):
        datetime_string = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        dir_name_full = dir_name + '_' + datetime_string
        return self._create_dir(dir_name=dir_name_full)

    def _crop_r(self, arr):
        k_max = 0
        for k in range(len(self._rs)):
            if self._rs[k] > self._r_right:
                k_max = k
                break

        self._rs_cropped = self._rs[:k_max]
        self._rs_cropped = append([-e for e in self._rs_cropped[::-1][:-1]], self._rs_cropped)

        return arr[:k_max], k_max

    def _crop_t(self, arr):
        s_min = 0
        s_max = -1
        for s in range(len(self._ts)):
            if self._ts[s] < self._t_left:
                s_min = s
                break
        for s in range(len(self._ts)-1, 0, -1):
            if self._ts[s] > self._t_right:
                s_max = s
                break

        self._ts_cropped = self._ts[s_min:s_max]

        return transpose(transpose(arr)[s_min:s_max]), s_min, s_max

    def _calc_ticks_t(self, labels):
        ticks = []
        nxt = 0
        for label in labels:
            for i in range(nxt, len(self._ts_cropped)):
                if self._ts_cropped[i] < float(label) * 10**-15:
                    ticks.append(i)
                    nxt = i
                    break
        return ticks

    def _calc_ticks_r(self, labels):
        ticks = []
        nxt = 0
        for label in labels:
            for i in range(nxt, len(self._rs_cropped)):
                if self._rs_cropped[i] > float(label) * 10**-6:
                    ticks.append(i)
                    nxt = i
                    break
        return ticks

    @staticmethod
    def _reflect(arr):
        res = copy(arr)
        return append(res[::-1, :], res[1:]).reshape((2 * arr.shape[0]-1, arr.shape[1]))

    def _initialize_scale(self, min_maximum, max_maximum, appropriate_normalize_to, **kwargs):
        self._log = kwargs['log']
        if self._log not in (True, False):
            raise Exception('Wrong log!')

        if not self._log:
            self._maximum = kwargs['maximum']
            if isinstance(self._maximum, float):
                if self._maximum < min_maximum or self._maximum > max_maximum:
                    raise Exception('Wrong float maximum!')
            elif isinstance(self._maximum, str):
                if self._maximum != 'local':
                    raise Exception('Wrong string maximum!')
            else:
                raise Exception('Wrong maximum!')

            self._normalize_to = kwargs['normalize_to']
            if self._normalize_to not in appropriate_normalize_to:
                raise Exception('Wrong normalize!')
        else:
            self._log_ticks = None

    def _initialize_log_tickslabels(self, prec):
        self._log_ticklabels = ['+' + str(round(e, prec)) if e > 0 else '$-$' + str(abs(round(e, prec))) if e != 0 else '  0'
                                 for e in self._log_ticks]

    def _plot(self, arr, filename):
        pass

    def _filter_and_log_arr(self, arr):
        pass

    def _process_iteration(self, idx, filename, arr, s_min, s_max, k_max):
        if not idx:
            arr, s_min, s_max = self._crop_t(arr)
            arr, k_max = self._crop_r(arr)
        else:
            arr = arr[:, s_min:s_max]
            arr = arr[:k_max, :]

        arr = self._reflect(arr)

        if self._log:
            arr = self._filter_and_log_arr(arr)

        self._plot(arr, filename)

        del arr