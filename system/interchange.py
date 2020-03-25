from random import Random
from dependence import analyze_dependence, is_valid

ATTEMPTS_PER_MUTATION = 10
DEBUG = False
class Interchange:
    def __init__(self, seed=0):
        self.rand = Random(seed)
        self.hashes = set()
    def mutate(self, program):
        dep_graph_before = analyze_dependence(program)
        for attempt in range(ATTEMPTS_PER_MUTATION):
            cloned_program = program.clone()

            # find a random loop
            n_loops = len(cloned_program.loops)
            which_loop = self.rand.randint(0, n_loops-1)

            # shuffle that loop
            self.rand.shuffle(cloned_program.loops[which_loop].loop_vars)

            # make sure it's actually a mutation
            if program.is_syntactically_equal(cloned_program):
                if DEBUG:
                    print(f'Attempt {attempt + 1}: Mutated loop did not change.')
                continue

            # make sure this mutation doesn't exist
            program_hash = hash(cloned_program.pprint())
            if program_hash in self.hashes:
                if DEBUG:
                    print(f'Attempt {attempt + 1}: This mutation has already been created!')
                continue

            # make sure it's a legal mutation
            dep_graph_after = analyze_dependence(cloned_program)
            if not is_valid(dep_graph_before, dep_graph_after):
                if DEBUG:
                    print(f'Attempt {attempt + 1}: This transformation is invalid!')
                continue

            self.hashes.add(program_hash)
            return cloned_program
        return None
