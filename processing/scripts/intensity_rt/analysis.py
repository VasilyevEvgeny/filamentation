

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-3]))

from processing.core import parse_args, IntensityRT

PROJECTION_MODE = '2D'
STYLE_MODE = 'analysis'

args = parse_args()

intensity_rt = IntensityRT(args=args,
                           projection_mode=PROJECTION_MODE,
                           style_mode=STYLE_MODE,
                           log=True,
                           #maximum_intensity=1e16,
                           #normalize_to=1,
                           language='english')

intensity_rt.process()
