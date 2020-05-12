from parser import parse_file
from loguru import logger
from transformers.loop_interchange import LoopInterchange

program, _ = parse_file('valid-interchange.loop')
print(program.pprint())

loop = program.loops[0]

class Limits:
    def __init__(self):
        self.default_min = 0
        self.default_max = 1000
        self.mins = {}
        self.maxes = {}
    def set_min(self, var, value):
        self.mins[var] = value
        return self
    def set_max(self, var, value):
        self.maxes[var] = value
        return self
    def get_min(self, var):
        return self.mins[var] if var in self.mins else self.default_min
    def get_max(self, var):
        return self.maxs[var] if var in self.maxs else self.default_max
    
limits = Limits()

def iterate_mutations(program):
    loop_interchange = LoopInterchange()
    for mutation in loop_interchange.transform(program):
        yield mutation

for mutation in iterate_mutations(program):
    print('printing mutation')
    print(mutation.pprint())
