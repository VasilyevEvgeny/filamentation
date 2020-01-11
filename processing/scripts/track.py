
import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-2]))

from processing.core import parse_args, Track

args = parse_args()

track = Track(args=args,
              language='english',
              intensity=True)

track.process()
