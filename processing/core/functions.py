import argparse


def parse_args():
    """Parses arguments from command line"""

    parser = argparse.ArgumentParser()
    parser.add_argument('--current_results_dir')
    parser.add_argument('--insert_datetime', default=True)

    return parser.parse_args()