

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-3]))

from processing.core import parse_args, IntensityRT

args = parse_args()

intensity_rt = IntensityRT(args=args,
                           projection_mode='flat',
                           style_mode='analysis',
                           log=False,
                           maximum_intensity=1e16,
                           normalize_to=1,
                           language='english',
                           t_left=150 * 10**-15,
                           t_right=-150 * 10**-15,
                           t_labels=['+100', '+50', '0', '-50', '-100'],
                           r_right=300 * 10**-6,
                           r_labels=['-200', '-100', '0', '+100', '+200'])

intensity_rt.process()
