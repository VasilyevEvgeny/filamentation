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





class BaseReadout:
    def __init__(self, **kwargs):
        self._args = kwargs['args']

        # parameters
        self._schema = {
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
                    'P_0_to_P_cr': {'type': 'float', 'required': True},
                    'P_cr_to_P_G': {'type': 'float', 'required': True},
                    'P_G': {'type': 'float', 'required': True},
                    'P_0': {'type': 'float', 'required': True},
                    'I_max_to_I_0': {'type': 'float', 'required': True},
                    'I_0': {'type': 'float', 'required': True},
                    'E_0': {'type': 'float', 'required': True}
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
                    'dz_0': {'type': 'float', 'required': True},
                    'max_intensity_to_stop': {'type': 'float', 'required': True}
                }
            }
        }
        self._parameters = self._readout_parameters()

        # propagation
        self._df_propagation = self._readout_propagation()

        # language
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

    def _find_z(self, filename):
        step = int(filename)
        return self._df_propagation['z, [cm]'][step]

    def _find_I_max(self, filename):
        step = int(filename)
        return self._df_propagation['I_max, [TW/cm^2]'][step]

    def _find_Ne_max(self, filename):
        step = int(filename)
        return self._df_propagation['N_e_max, [m^-3]'][step]

    def _readout_parameters(self):
        with open(self._args.current_results_dir + '/parameters.yml', 'r') as f:
            parameters = safe_load(f)

        validator = Validator(self._schema)
        if not validator.validate(parameters):
            raise Exception(validator.errors)
        else:
            return parameters

    def _readout_propagation(self):
        df_propagation = read_csv(self._args.current_results_dir + '/propagation.csv', sep='|')

        df_propagation.columns = [name.lstrip() for name in df_propagation.columns]

        # add z_normalized
        df_propagation['z, [cm]'] = df_propagation['z, [m]'] * 1e2

        # add z / z_diff
        df_propagation['z / z_diff'] = df_propagation['z, [m]'] / self._parameters['pulsed_beam']['z_diff']

        # add z / z_disp
        df_propagation['|z / z_disp|'] = df_propagation['z, [m]'] / abs(self._parameters['pulsed_beam']['z_disp'])

        # add i_max / i_0
        df_propagation['I_max / I_0'] = df_propagation['I_max, [W/m^2]'] / self._parameters['pulsed_beam']['I_0']

        # add i_max_normalized
        df_propagation['I_max, [TW/cm^2]'] = df_propagation['I_max, [W/m^2]'] / 1e16

        # dtypes
        df_propagation = df_propagation.astype(float64)
        df_propagation['step'] = df_propagation['step'].astype(int64)

        return df_propagation

    @staticmethod
    def _initialize_language_string(language, russian, english):
        return russian if language == 'russian' else english
