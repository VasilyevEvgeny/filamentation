

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-3]))

from processing.core import parse_args, IntensityRT

STYLE_MODE = 'multimedia'

args = parse_args()

intensity_rt = IntensityRT(args=args,
                           projection_mode='2D',
                           style_mode=STYLE_MODE,
                           log=False,
                           maximum_intensity='local',
                           normalize_to=1,
                           language='english')

intensity_rt.process()
