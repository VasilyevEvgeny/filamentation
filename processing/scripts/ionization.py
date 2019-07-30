

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-2]))

from processing.core import Ionization


ion = Ionization()
