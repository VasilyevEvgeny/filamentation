from datetime import datetime
from matplotlib import pyplot as plt

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-1]))

from processing.core import parse_args, BaseReadout


class Track(BaseReadout):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.__res_dir = self.__create_res_dir()

        self._readout_parameters()
        self._readout_propagation()

        self.__intensity = kwargs['intensity']

    def __create_res_dir(self):
        datetime_string = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
        dir_name = 'procesing_track_' + datetime_string
        return self._create_dir(dir_name=dir_name)

    def __plot_track(self):
        font_sizes = {'plot_ticks': 35, 'plot_labels': 40}
        font_weights = {'plot_ticks': 'normal', 'plot_labels': 'bold'}

        color = 'black'
        linewidth = 7
        alpha = 1.0
        linestyle = '-'

        z_abs_rus, z_rel_rus = '$\mathbf{z}$, см', '$\mathbf{z \ / \ z_{диф}}$'
        z_abs_eng, z_rel_eng = '$\mathbf{z}$, cm', '$\mathbf{z \ / \ z_{diff}}$'

        if self.__intensity:
            i_abs_rus, i_rel_rus = '$\mathbf{I_{макс}}$, ТВт/см$\mathbf{^2}$', '$\mathbf{I_{макс} \ / \ I_0}$'
            i_abs_eng, i_rel_eng = '$\mathbf{I_{max}}$, TW/cm$\mathbf{^2}$', '$\mathbf{I_{max} \ / \ I_0}$'

            pool = [{'filename': 'i_max_abs(z_abs)', 'z': 'z, [cm]', 'i': 'i_max, [TW/cm^2]',
                     'xlabel_rus': z_abs_rus, 'xlabel_eng': z_abs_eng,
                     'ylabel_rus': i_abs_rus, 'ylabel_eng': i_abs_eng},

                    {'filename': 'i_max_abs(z_rel)', 'z': 'z / z_diff', 'i': 'i_max, [TW/cm^2]',
                     'xlabel_rus': z_rel_rus, 'xlabel_eng': z_rel_eng,
                     'ylabel_rus': i_abs_rus, 'ylabel_eng': i_abs_eng},

                    {'filename': 'i_max_rel(z_abs)', 'z': 'z, [cm]', 'i': 'i_max / i_0',
                     'xlabel_rus': z_abs_rus, 'xlabel_eng': z_abs_eng,
                     'ylabel_rus': i_rel_rus, 'ylabel_eng': i_rel_eng},

                    {'filename': 'i_max_rel(z_rel)', 'z': 'z / z_diff', 'i': 'i_max / i_0',
                     'xlabel_rus': z_rel_rus, 'xlabel_eng': z_rel_eng,
                     'ylabel_rus': i_rel_rus, 'ylabel_eng': i_rel_eng}]

            for info in pool:
                plt.figure(figsize=(15, 5))
                plt.plot(self._df_propagation[info['z']], self._df_propagation[info['i']], color=color,
                         linewidth=linewidth, alpha=alpha, linestyle=linestyle)

                xlabel = self._initialize_label(self._language, info['xlabel_rus'], info['xlabel_eng'])
                ylabel = self._initialize_label(self._language, info['ylabel_rus'], info['ylabel_eng'])

                plt.xlabel(xlabel, fontsize=font_sizes['plot_labels'], fontweight=font_weights['plot_labels'])
                plt.ylabel(ylabel, fontsize=font_sizes['plot_labels'], fontweight=font_weights['plot_labels'])

                plt.xticks(fontsize=font_sizes['plot_ticks'], fontweight=font_weights['plot_ticks'])
                plt.yticks(fontsize=font_sizes['plot_ticks'], fontweight=font_weights['plot_ticks'])

                plt.grid(color='gray', linestyle=':', linewidth=2, alpha=0.5)

                plt.savefig(self.__res_dir + '/' + info['filename'] + '.png', bbox_inches='tight')
                plt.close()

    def process(self):
        self.__plot_track()


# parse args from command line
args = parse_args()
plot_track = Track(args=args,
                   language='english',
                   intensity=True)
plot_track.process()
