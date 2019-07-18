

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-2]))

from processing.core import parse_args, IntensityRT, Track


args = parse_args()


plot_intensity_rt = IntensityRT(args=args,
                                mode='flat',
                                language='russian',
                                t_left=150 * 10**-15,
                                t_right=-150 * 10**-15,
                                r_right=200 * 10**-6)
plot_intensity_rt.process()



plot_track = Track(args=args,
                   language='english',
                   intensity=True)
plot_track.process()
