
import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-3]))

from processing.core import parse_args, PlasmaRT

PROJECTION_MODE = 'flat'
STYLE_MODE = 'analysis'

args = parse_args()

plasma_rt = PlasmaRT(args=args,
                     projection_mode=PROJECTION_MODE,
                     style_mode=STYLE_MODE,
                     log=True,
                     #maximum='local',
                     #normalize_to='N_0',
                     language='english')

plasma_rt.process()
