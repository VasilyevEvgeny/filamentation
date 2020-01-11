import argparse

import sys
sys.path.insert(0, '/'.join((sys.path[0].replace('\\', '/')).split('/')[:-2]))

from processing.core import IonizationTable


def parse_args():
    """Parses arguments from command line"""

    parser = argparse.ArgumentParser()
    parser.add_argument('--path_to_ionization_table')

    return parser.parse_args()


args = parse_args()
ionization_table = IonizationTable(path_to_ionization_table=args.path_to_ionization_table,
                                   language='english')
ionization_table.process()
