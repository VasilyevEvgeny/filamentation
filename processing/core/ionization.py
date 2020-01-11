import pandas as pd
from numpy import max as maximum
from matplotlib import pyplot as plt


class IonizationTable:
    def __init__(self, **kwargs):
        self._path_to_ionization_table = kwargs['path_to_ionization_table']
        self._path_to_save_plot = self._path_to_ionization_table + '.png'

        self.__language = kwargs['language']

        self._df_ionization_table = None

    @staticmethod
    def _initialize_label(language, russian, english):
        if language == 'russian':
            return russian
        else:
            return english

    def __make_title_from_filename(self, filename):
        model, medium, lambda_0 = tuple(filename.split('_'))
        if medium == 'SiO2':
            medium = 'SiO$_\mathbf{2}$'
        elif medium == 'CaF2':
            medium = 'CaF$_\mathbf{2}$'

        title_rus = 'model          : %s\nmedium       : %s\nwavelength : %s нм' % (model, medium, lambda_0)
        title_eng = 'model          : %s\nmedium       : %s\nwavelength : %s nm' % (model, medium, lambda_0)

        return self._initialize_label(self.__language, title_rus, title_eng)

    def __limit_max_intensity(self, max_intensity=10**18):
        max_idx = len(self._df_ionization_table)
        for i in range(len(self._df_ionization_table)):
            if self._df_ionization_table.loc[i, 'intensity'] > max_intensity:
                max_idx = i
                break
        self._df_ionization_table = self._df_ionization_table[:max_idx]

    def __normalize_df(self):
        self._df_ionization_table['intensity'] /= 10**17
        self._df_ionization_table['rate'] /= 10**12

    def _readout(self):
        columns = ['intensity', 'rate']
        self._df_ionization_table = pd.read_csv(self._path_to_ionization_table, sep='    ',
                                                header=None, index_col=False, names=columns, engine='python')

        self.__limit_max_intensity()
        self.__normalize_df()

    def _plot(self):
        font_size = {'title': 30,  'plot_ticks': 20, 'plot_labels': 30}
        font_weight = {'title': 'bold', 'plot_ticks': 'normal', 'plot_labels': 'bold'}
        linewidth = 5

        fig = plt.figure(figsize=(12, 10))
        plt.plot(self._df_ionization_table['intensity'], self._df_ionization_table['rate'],
                 color='black', linestyle='-', linewidth=linewidth)

        x_label = self._initialize_label(self.__language,
                                         'I, $\mathbf{\\times 10^{13}}$ Вт/см$\mathbf{^2}$',
                                         'I, $\mathbf{\\times 10^{13}}$ W/cm$\mathbf{^2}$')
        y_label = self._initialize_label(self.__language,
                                         '$\mathbf{R_E}$, $\mathbf{\\times 10^{12}}$ c$\mathbf{^{-1}}$',
                                         '$\mathbf{R_E}$, $\mathbf{\\times 10^{12}}$ s$\mathbf{^{-1}}$')
        plt.xlabel(x_label, fontsize=font_size['plot_labels'], fontweight=font_weight['plot_labels'])
        plt.ylabel(y_label, fontsize=font_size['plot_labels'], fontweight=font_weight['plot_labels'])

        n_y_ticks = 7
        dyticks = maximum(self._df_ionization_table['rate']) / (n_y_ticks - 1)
        y_ticks = [i * dyticks for i in range(n_y_ticks)]
        y_ticklabels = ['%01.3f' % round(e, 3) for e in y_ticks]

        plt.xticks(fontsize=font_size['plot_ticks'], fontweight=font_weight['plot_ticks'])
        plt.yticks(y_ticks, y_ticklabels, fontsize=font_size['plot_ticks'], fontweight=font_weight['plot_ticks'])

        filename = self._path_to_ionization_table.split('/')[-1]
        title = self.__make_title_from_filename(filename)
        plt.text(0, 1.1 * maximum(self._df_ionization_table['rate']), s=title, fontsize=font_size['title'], fontweight=font_weight['title'])

        plt.grid(linestyle=':', linewidth=2)

        # bbox
        bbox_width = 11
        bbox_height = 10.5
        bbox = fig.bbox_inches.from_bounds(0, 0, bbox_width, bbox_height)

        plt.savefig(self._path_to_save_plot, bbox_inches=bbox, dpi=100)
        plt.close()

    def process(self):
        self._readout()
        self._plot()
