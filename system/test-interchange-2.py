from parser import parse_file
from loguru import logger
from transformers.loop_interchange import LoopInterchangeV2

program, _ = parse_file('valid-interchange.loop')
print(program.pprint())

def iterate_mutations(program):
    loop_interchange = LoopInterchangeV2()
    for mutation in loop_interchange.transform(program):
        yield mutation

for mutation in iterate_mutations(program):
    print(mutation.pprint())
