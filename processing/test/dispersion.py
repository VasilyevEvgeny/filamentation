from unittest import TestCase
from numpy import exp, sqrt, arctan
from numpy.linalg import norm
from numpy import max as maximum
import pandas as pd
pd.options.mode.chained_assignment = None
from matplotlib import pyplot as plt

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-2]))

from processing.core import parse_args, IntensityRT, Track


class TestDispersion(TestCase):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self.__language = 'english'

        self.__args = parse_args()

        self.__intensity_rt = IntensityRT(args=self.__args,
                                          mode='flat',
                                          log=False,
                                          maximum_intensity='local',
                                          normalize_to='i_0',
                                          language='russian',
                                          t_left=150 * 10**-15,
                                          t_right=-150 * 10**-15,
                                          t_labels=['+100', '0', '-100'],
                                          r_right=200 * 10**-6,
                                          r_labels=['-150', '0', '+150'])

        self.__track = Track(args=self.__args,
                             language='english',
                             intensity=True)

        self.__df_propagation, self.__parameters = None, None
        self.__eps = 0.02
        self.__png_name = 'dispersion'

        self.__horizontal_line = 1 / sqrt(2)

    @staticmethod
    def __calculate_max_intensity(z, radius, z_to_normalize, spatial_coord=0.0, p=0.5):
        z_rel = z / z_to_normalize
        a_0 = exp(-spatial_coord**2 / (radius**2 * (1 + z_rel**2))) / sqrt(1.0 + z_rel**2) ** p
        k_psi = (spatial_coord / radius)**2 * z_rel / (1 + z_rel**2) ** p - arctan(z_rel)

        return norm(a_0 * exp(1j * k_psi))**2

    def __add_analytics_to_df(self):
        t_0 = self.__parameters['pulsed_beam']['t_0']

        self.__df_propagation['analytics'] = 0.0
        n = len(self.__df_propagation)
        for i in range(n):
            z = self.__df_propagation['z, [m]'][i]
            self.__df_propagation['analytics'][i] = \
                self.__calculate_max_intensity(z, t_0, abs(self.__parameters['pulsed_beam']['z_disp']))

    def __check(self):
        numerical = self.__df_propagation['i_max / i_0']
        analytics = self.__df_propagation['analytics']

        self.assertLess(maximum(abs(numerical - analytics) / analytics), self.__eps)

    def __plot(self, path_to_save_plot):
        font_size = 40
        font_weight = 'bold'

        plt.figure(figsize=(15, 10))
        label_numerical = self.__track._initialize_label(self.__language,
                                                         'Численное\nмоделирование',
                                                         'Numerical\nmodeling')
        label_analytics = self.__track._initialize_label(self.__language,
                                                         'Аналитическая\nформула',
                                                         'Analytics')
        plt.plot(self.__df_propagation['|z / z_disp|'], self.__df_propagation['analytics'], color='blue', linewidth=30, label=label_analytics)
        plt.plot(self.__df_propagation['|z / z_disp|'], self.__df_propagation['i_max / i_0'], color='red', linewidth=10, label=label_numerical)
        plt.xticks(fontsize=font_size-5)
        plt.yticks(fontsize=font_size-5)

        x_label = self.__track._initialize_label(self.__language,
                                                 '$\mathbf{|z \ / \ z_{дисп}|}$',
                                                 '$\mathbf{|z \ / \ z_{disp}|}$')
        y_label = self.__track._initialize_label(self.__language,
                                                 '$\mathbf{I \ / \ I_{макс} (z=0)}$',
                                                 '$\mathbf{I \ / \ I_{max} (z=0)}$')
        plt.xlabel(x_label, fontsize=font_size, fontweight=font_weight)
        plt.ylabel(y_label, fontsize=font_size, fontweight=font_weight)

        plt.axhline(self.__horizontal_line, color='black', linestyle='solid', linewidth=5, zorder=-1)
        if self.__horizontal_line == 1 / sqrt(2):
            plt.text(0.05, 0.72, "$1 / \sqrt{2}$", fontsize=font_size)
        elif self.__horizontal_line == 1 / 2:
            plt.text(0.05, 0.53, "$1 / 2$", fontsize=font_size)

        plt.grid(linewidth=2, color='gray', linestyle='dotted', alpha=0.5)
        plt.legend(fontsize=font_size-10, loc=1)

        plt.savefig(path_to_save_plot + '/' + self.__png_name + '.png', bbox_inches='tight')
        plt.close()

    def process(self):
        self.__intensity_rt.process()
        self.__track.process()

        self.__df_propagation = self.__track.propagation.copy()
        self.__df_propagation['i_max / i_0'] /= self.__df_propagation['i_max / i_0'][0]

        self.__parameters = self.__track.parameters.copy()

        self.__add_analytics_to_df()

        self.__plot(self.__args.current_results_dir)
        self.__check()


test_dispersion = TestDispersion()
test_dispersion.process()
