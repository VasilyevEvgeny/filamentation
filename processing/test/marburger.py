from unittest import TestCase
from numpy import sqrt, linspace
import pandas as pd
from pandas import read_csv
pd.options.mode.chained_assignment = None
from matplotlib import pyplot as plt
from glob import glob
from yaml import safe_load
from cerberus import Validator

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-2]))

from processing.core import parse_args, BaseReadout


class TestMarburger(BaseReadout, TestCase):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        # true
        self.__p_rel_min = 2
        self.__p_rel_max = 11
        self.__p_rels_true = linspace(self.__p_rel_min, self.__p_rel_max, 1000)
        self.__z_fil_rels_true = self.__calculate_z_fil_rels_true()

        self.__eps = 0.2

        # plot
        self.__font_size = {'title': 40,  'plot_ticks': 40, 'plot_labels': 50, 'legend': 40}
        self.__font_weight = {'title': 'bold', 'plot_ticks': 'normal', 'plot_labels': 'bold', 'legend': 'bold'}

        # save
        self.__filename = 'marburger'
        self.__ext = '.png'
        self.__dpi = 100

    def __readout_parameters(self, dir):
        with open(dir + '/parameters.yml', 'r') as f:
            parameters = safe_load(f)

        validator = Validator(self._schema)
        if not validator.validate(parameters):
            raise Exception(validator.errors)

        return parameters

    def __dirs(self):
        dirs = []
        for path in glob(args.current_results_dir + '/*'):
            path = path.replace('\\', '/')
            if path.split('/')[-1] != self.__filename + self.__ext:
                dirs.append(path)

        return dirs

    @staticmethod
    def __get_p_rels_pred(dirs):
        p_rels = []
        for dir in dirs:
            p_rels.append(float(dir.split('=')[-1]))

        return p_rels

    @staticmethod
    def __marburger(p_rel):
        return 0.367 / sqrt((sqrt(p_rel) - 0.852)**2 - 0.0219)

    def __calculate_z_fil_rels_true(self):
        z_fil_rel_trues = []
        for p_rel in self.__p_rels_true:
            z_fil_rel_trues.append(self.__marburger(p_rel))

        return z_fil_rel_trues

    def __check(self, p_rels_pred, z_fil_rels_pred):
        for i in range(len(p_rels_pred)):
            p_rel = p_rels_pred[i]
            z_fil_rel_true = self.__marburger(p_rel)
            self.assertLess(abs(z_fil_rels_pred[i] - z_fil_rel_true) / z_fil_rel_true, self.__eps)

    def __plot_marbuger(self, data):
        plt.subplots(figsize=(15, 10))

        label_numerical = self._initialize_label(self._language,
                                                 'Численное моделирование',
                                                 'Numerical modeling')
        label_analytics = self._initialize_label(self._language,
                                                 'Формула Марбургера',
                                                 'Marburger formula')

        plt.plot(self.__p_rels_true, self.__z_fil_rels_true, linewidth=10, color='blue', zorder=-1, label=label_analytics)
        plt.scatter(data['p_rels'], data['z_fil_rels'], linewidth=10, color='red', zorder=0, label=label_numerical)

        x_label = self._initialize_label(self._language,
                                         '$\mathbf{P_0 \ / \ P_{кр}}$',
                                         '$\mathbf{P_0 \ / \ P_{cr}}$')

        y_label = self._initialize_label(self._language,
                                         '$\mathbf{z \ / \ z_{диф}}$',
                                         '$\mathbf{z \ / \ z_{diff}}$')

        plt.xlabel(x_label, fontsize=self.__font_size['plot_labels'], fontweight=self.__font_weight['plot_labels'])
        plt.ylabel(y_label, fontsize=self.__font_size['plot_labels'], fontweight=self.__font_weight['plot_labels'])

        plt.xticks(fontsize=self.__font_size['plot_ticks'], fontweight=self.__font_weight['plot_ticks'])
        plt.yticks(fontsize=self.__font_size['plot_ticks'], fontweight=self.__font_weight['plot_ticks'])

        plt.grid(linewidth=2, color='gray', linestyle='dotted', alpha=0.5)

        plt.legend(fontsize=self.__font_size['legend'], loc=1)

        plt.savefig(args.current_results_dir + '/' + self.__filename + self.__ext, bbox_inches='tight', dpi=self.__dpi)
        plt.close()

    def process(self):
        dirs = self.__dirs()
        data = {'p_rels': [], 'z_fil_rels': []}
        for dir in dirs:

            parameters = self.__readout_parameters(dir)

            p_rel = float((dir.split('/')[-1]).split('=')[-1])

            df_propagation = read_csv(dir + '/propagation.csv', sep='|')
            df_propagation.columns = [name.lstrip() for name in df_propagation.columns]

            # add z / z_diff
            df_propagation['z / z_diff'] = df_propagation['z, [m]'] / parameters['pulsed_beam']['z_diff']

            z_fil = list(df_propagation['z / z_diff'])[-1]

            # make data
            data.update({'p_rels': data['p_rels'] + [p_rel]})
            data.update({'z_fil_rels': data['z_fil_rels'] + [z_fil]})

            self.__plot_marbuger(data)

        self.__check(data['p_rels'], data['z_fil_rels'])


args = parse_args()
marburger = TestMarburger(args=args,
                          language='english')
marburger.process()
