from ..base_rt import BaseRT
from matplotlib import pyplot as plt


class BaseRTFlat(BaseRT):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

    def _initialize_ticks(self):
        if self._ticks:
            t_ticks = self._calc_ticks_t(self._t_labels)
            r_ticks = self._calc_ticks_r(self._r_labels)
            plt.xticks(t_ticks, self._t_labels, fontsize=self._font_size['plot_ticks'])
            plt.yticks(r_ticks, self._r_labels, fontsize=self._font_size['plot_ticks'])
        else:
            plt.xticks([])
            plt.yticks([])

    def _initialize_labels(self):
        if self._labels:
            plt.xlabel(self._t_label, fontsize=self._font_size['plot_labels'], fontweight=self._font_weight['plot_labels'])
            plt.ylabel(self._r_label, fontsize=self._font_size['plot_labels'], fontweight=self._font_weight['plot_labels'],
                       labelpad=-30)

    def _initialize_grid(self):
        plt.grid(color='white', linestyle=':', linewidth=3, alpha=0.5)

    def _initialize_aspect(self, ax):
        ax.set_aspect(self._aspect)

    def _initialize_bbox(self, fig):
        bbox = None
        if isinstance(self._bbox, str):
            if self._bbox == 'tight':
                bbox = self._bbox
            else:
                raise Exception('Wrong bbox string!')
        else:
            if isinstance(self._bbox, tuple):
                if len(self._bbox) == 4:
                    x_ld, y_ld, w, h = self._bbox
                    bbox = fig.bbox_inches.from_bounds(x_ld, y_ld, w, h)
                else:
                    raise Exception('Wrong bbox tuple!')
        return bbox