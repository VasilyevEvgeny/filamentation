import argparse
from glob import glob
import os
import shutil
from time import sleep
from yaml import safe_load
from numba import jit
from numpy import zeros, copy, append
from pandas import read_csv


def parse_args():
    """Parses arguments from command line"""

    parser = argparse.ArgumentParser()
    parser.add_argument('--current_results_dir')
    parser.add_argument('--insert_datetime', default=True)

    return parser.parse_args()


class BaseReadout:
    def __init__(self, **kwargs):
        self._args = kwargs['args']

        self._field_dir = self._args.current_results_dir + '/field'

        self._field_paths = []
        self._parameters = None
        self._df_propagation = None

        self._language = kwargs['language']
        if self._language not in ('russian', 'english'):
            raise Exception('Wrong language!')

    def _create_dir(self, **kwargs):
        """Creates dir with default name dir_name deleting the existing directory"""

        dir_name = kwargs['dir_name']
        res_path = self._args.current_results_dir + '/' + dir_name

        try:
            os.makedirs(res_path)
        except OSError:
            shutil.rmtree(res_path)
            sleep(1)
            os.makedirs(res_path)

        return res_path

    def _readout_propagation(self):
        self._df_propagation = read_csv(self._args.current_results_dir + '/propagation.csv', sep='|')
        self._df_propagation.columns = [name.lstrip() for name in self._df_propagation.columns]

        # add z_normalized
        self._df_propagation['z, [cm]'] = self._df_propagation['z, [m]'] * 1e2

        # add z / z_diff
        self._df_propagation['z / z_diff'] = self._df_propagation['z, [m]'] / self._parameters['pulsed_beam']['z_diff']

        # add i_max / i_0
        self._df_propagation['i_max / i_0'] = self._df_propagation['i_max, [W/m^2]'] / self._parameters['pulsed_beam']['i_0']

        # add i_max_normalized
        self._df_propagation['i_max, [TW/cm^2]'] = self._df_propagation['i_max, [W/m^2]'] / 1e16

    def _readout_parameters(self):
        with open(self._args.current_results_dir + '/parameters.yml', 'r') as f:
            self._parameters = safe_load(f)

    def _readout_field_paths(self):
        for path in glob(self._field_dir + '/*'):
            self._field_paths.append(path.replace('\\', '/'))

    @staticmethod
    def _reflect(arr):
        res = copy(arr)
        return append(res[::-1, :], res[1:]).reshape((2 * arr.shape[0]-1, arr.shape[1]))

    @staticmethod
    def _initialize_label(language, russian, english):
        if language == 'russian':
            return russian
        else:
            return english

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
