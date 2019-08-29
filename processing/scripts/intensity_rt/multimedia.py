

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-3]))

from processing.core import parse_args, IntensityRT

args = parse_args()

intensity_rt = IntensityRT(args=args,
                           projection_mode='flat',
                           style_mode='multimedia',
                           #log=True,
                           #maximum_intensity='local',
                           normalize_to='i_0',
                           language='english',
                           t_left=150 * 10**-15,
                           t_right=-150 * 10**-15,
                           t_labels=['+100', '0', '-100'],
                           r_right=200 * 10**-6,
                           r_labels=['-150', '0', '+150'])

from multiprocessing import freeze_support

# if __name__ == '__main__':
#     freeze_support()
intensity_rt.process()
