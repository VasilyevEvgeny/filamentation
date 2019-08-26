import argparse
from glob import glob
import os
import shutil
from time import sleep
from yaml import safe_load
from numba import jit
from numpy import zeros, copy, append
from numpy import float64, int64
from pandas import read_csv
from cerberus import Validator


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
        self._plasma_dir = self._args.current_results_dir + '/plasma'

        self._field_paths = []
        self._plasma_paths = []
        self._parameters = None
        self.__schema = {
            'sellmeyer': {
                'type': 'dict',
                'schema': {
                    'C_1': {'type': 'float', 'required': True},
                    'C_2': {'type': 'float', 'required': True},
                    'C_3': {'type': 'float', 'required': True},
                    'lambda_1': {'type': 'float', 'required': True},
                    'lambda_2': {'type': 'float', 'required': True},
                    'lambda_3': {'type': 'float', 'required': True}
                }
            },
            'medium': {
                'type': 'dict',
                'schema': {
                    'name': {'type': 'string', 'required': True},
                    'formula': {'type': 'string', 'required': True},
                    'ionization': {'type': 'string', 'required': True},
                    'n_0': {'type': 'float', 'required': True},
                    'k_0': {'type': 'float', 'required': True},
                    'k_1': {'type': 'float', 'required': True},
                    'k_2': {'type': 'float', 'required': True},
                    'n_2': {'type': 'float', 'required': True},
                    'g': {'type': 'float', 'required': True},
                    'Omega_R': {'type': 'float', 'required': True},
                    'tau_k': {'type': 'float', 'required': True},
                    'Delta_t': {'type': 'float', 'required': True},
                    'N_0': {'type': 'float', 'required': True},
                    'v_ei': {'type': 'float', 'required': True},
                    'beta': {'type': 'float', 'required': True},
                    'U_i_in_eV': {'type': 'float', 'required': True},
                    'K': {'type': 'float', 'required': True},
                    'delta': {'type': 'float', 'required': True}
                }
            },
            'pulsed_beam': {
                'type': 'dict',
                'schema': {
                    'space_distribution': {'type': 'string', 'required': True},
                    'M': {'type': 'integer', 'required': True},
                    'm': {'type': 'integer', 'required': True},
                    'r_0': {'type': 'float', 'required': True},
                    't_0': {'type': 'float', 'required': True},
                    'lambda_0': {'type': 'float', 'required': True},
                    'z_diff': {'type': 'float', 'required': True},
                    'z_disp': {'type': 'float', 'required': True},
                    'p_0_to_p_cr': {'type': 'float', 'required': True},
                    'p_cr_to_p_g': {'type': 'float', 'required': True},
                    'p_g': {'type': 'float', 'required': True},
                    'p_0': {'type': 'float', 'required': True},
                    'i_max_to_i_0': {'type': 'float', 'required': True},
                    'i_0': {'type': 'float', 'required': True},
                    'e_0': {'type': 'float', 'required': True}
                }
            },
            'grid': {
                'type': 'dict',
                'schema': {
                    'r_max': {'type': 'float', 'required': True},
                    'n_r': {'type': 'integer', 'required': True},
                    'dr': {'type': 'float', 'required': True},
                    't_max': {'type': 'float', 'required': True},
                    'n_t': {'type': 'integer', 'required': True},
                    'dt': {'type': 'float', 'required': True}
                }
            },
            'track': {
                'type': 'dict',
                'schema': {
                    'n_z': {'type': 'integer', 'required': True},
                    'dz_0': {'type': 'float', 'required': True}
                }
            }
        }

        self._df_propagation = None

        self._language = kwargs['language']
        if self._language not in ('russian', 'english'):
            raise Exception('Wrong language!')

    def _find_z(self, filename):
        step = int(filename)
        return self._df_propagation['z, [cm]'][step]

    def _find_i_max(self, filename):
        step = int(filename)
        return self._df_propagation['i_max, [TW/cm^2]'][step]

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

        # add z / z_disp
        self._df_propagation['|z / z_disp|'] = self._df_propagation['z, [m]'] / abs(self._parameters['pulsed_beam']['z_disp'])

        # add i_max / i_0
        self._df_propagation['i_max / i_0'] = self._df_propagation['i_max, [W/m^2]'] / self._parameters['pulsed_beam']['i_0']

        # add i_max_normalized
        self._df_propagation['i_max, [TW/cm^2]'] = self._df_propagation['i_max, [W/m^2]'] / 1e16

        self._df_propagation = self._df_propagation.astype(float64)
        self._df_propagation['step'] = self._df_propagation['step'].astype(int64)

        print(self._df_propagation.dtypes)

    def _readout_parameters(self):
        with open(self._args.current_results_dir + '/parameters.yml', 'r') as f:
            self._parameters = safe_load(f)

        validator = Validator(self.__schema)
        if not validator.validate(self._parameters):
            raise Exception(validator.errors)

    def _readout_field_paths(self):
        for path in glob(self._field_dir + '/*'):
            self._field_paths.append(path.replace('\\', '/'))

    def _readout_plasma_paths(self):
        for path in glob(self._plasma_dir + '/*'):
            self._plasma_paths.append(path.replace('\\', '/'))

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
