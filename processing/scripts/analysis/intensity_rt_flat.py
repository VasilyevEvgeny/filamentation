import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-3]))

from processing.core.rt.flat import IntensityRTFlat
from processing.core.functions import parse_args


args = parse_args()

res_dir_name = 'analysis_I(r,t)_flat'

t_left = 150 * 10**-15
t_right = -150 * 10**-15
t_labels = ['+100', '+50', '0', '-50', '-100']
r_right = 300 * 10**-6
r_labels = ['-200', '-100', '0', '+100', '+200']
font_size = {'title': 40,
             'plot_ticks': 20,
             'plot_labels': 40,
             'colorbar_ticks': 20,
             'colorbar_label': 40}
font_weight = {'title': 'bold',
               'plot_ticks': 'normal',
               'plot_labels': 'bold',
               'colorbar_ticks': 'bold',
               'colorbar_label': 'bold'}

fig_size = (25, 20)
aspect = 1
bbox = 'tight'
log_ticks = [-1.0, -0.5, 0.0, +0.5, +1.0]
log_ticks_prec = 1

ticks = True
title = True
labels = True
colorbar = True

dpi = 100



intensity_rt_flat = IntensityRTFlat(args=args,
                                    log=True,
                                    #maximum=1e16,
                                    #normalize_to=1,
                                    language='english',
                                    res_dir_name=res_dir_name,
                                    t_left=t_left,
                                    t_right=t_right,
                                    t_labels=t_labels,
                                    r_right=r_right,
                                    r_labels=r_labels,
                                    font_size=font_size,
                                    font_weight=font_weight,
                                    fig_size=fig_size,
                                    aspect=aspect,
                                    bbox=bbox,
                                    log_ticks=log_ticks,
                                    log_ticks_prec=log_ticks_prec,
                                    ticks=ticks,
                                    title=title,
                                    labels=labels,
                                    colorbar=colorbar,
                                    dpi=dpi
                                    )

intensity_rt_flat.process()
