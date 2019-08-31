

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-3]))

from processing.core import parse_args, IntensityRT

STYLE_MODE = 'multimedia'

t_left = 150 * 10**-15
t_right = -150 * 10**-15
t_labels = ['+100', '0', '-100']
r_right = 200 * 10**-6
r_labels = ['-150', '0', '+150']
font_size = {'title': 40,  'plot_ticks': 40, 'plot_labels': 50, 'colorbar_ticks': 40, 'colorbar_label': 50}
font_weight = {'title': 'bold', 'plot_ticks': 'normal', 'plot_labels': 'bold', 'colorbar_ticks': 'bold', 'colorbar_label': 'bold'}
fig_size = (9, 7)
aspect = 'auto'
bbox = (-0.8, -1.0, 10.3, 10.0)
log_ticks = [-1.0, 0.0, +1.0]
log_ticks_prec = 0
ticks = True
title = True
labels = True
label_pad = -90
y = 1.2

if self._normalize_to == 'I_0':
    label_pad = -60
    y = 1.25
else:
    label_pad = -100
    y = 1.4

dpi = 100

args = parse_args()

intensity_rt = IntensityRT(args=args,
                           projection_mode='flat',
                           style_mode=STYLE_MODE,
                           log=False,
                           maximum_intensity='local',
                           normalize_to=1,
                           language='english')

intensity_rt.process()
