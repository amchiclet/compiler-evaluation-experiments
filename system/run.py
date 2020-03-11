import argparse
from parser import parse_file

arg_parser = argparse.ArgumentParser()
arg_parser.add_argument('--input', required=True)
args = arg_parser.parse_args()
parse_file(args.input)

