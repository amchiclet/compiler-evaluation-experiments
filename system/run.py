import argparse
from parser import parse_file
from dependence import analyze_dependence

arg_parser = argparse.ArgumentParser()
arg_parser.add_argument('--input', required=True)
args = arg_parser.parse_args()
program, node_id = parse_file(args.input)
analyze_dependence(program)
