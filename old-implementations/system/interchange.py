from random import Random
from dependence import analyze_dependence, is_valid
from loop_analyzer import analyze_loops
from math import factorial
from loguru import logger
ATTEMPTS_PER_MUTATION = 10
DEBUG = True
class Interchange:
    def __init__(self, seed=0):
        self.rand = Random(seed)
        self.hashes = set()
    def mutate(self, program, loop_analysis):
        dep_graph_before = analyze_dependence(program, loop_analysis)
        explored_space = set()
        space_size = 0
        for which_loop, loop in enumerate(program.loops):
            depth = len(loop.loop_vars)
            space_size += factorial(depth)
            original_order = tuple(range(depth))
            space_id = (which_loop, original_order)
            explored_space.add(space_id)

        unexplored_space_size = space_size - len(explored_space)
        logger.debug(f'Unexplored space size is {unexplored_space_size}')
        for attempt in range(unexplored_space_size):
            logger.debug('attempt')
            cloned_program = program.clone()

            # find a random loop
            n_loops = len(cloned_program.loops)

            space_id = next(iter(explored_space))
            while space_id in explored_space:
                which_loop = self.rand.randint(0, n_loops-1)

                # shuffle that loop
                # exclude the dummy loop_var
                loop_vars = cloned_program.loops[which_loop].loop_vars
                new_order = list(range(0, len(loop_vars)-1))
                self.rand.shuffle(new_order)
                new_order.append(len(loop_vars)-1)
                space_id = (which_loop, tuple(new_order))
            logger.debug(f'found a new order {new_order}')
            loop_vars[:] = [loop_vars[i] for i in new_order]
            logger.debug(loop_vars)
            # make sure it's actually a mutation
            if program.is_syntactically_equal(cloned_program):
                if DEBUG:
                    logger.debug(f'Attempt {attempt + 1}: Mutated loop did not change.')
                continue

            # make sure this mutation doesn't exist
            program_hash = hash(cloned_program.pprint())
            if program_hash in self.hashes:
                if DEBUG:
                    logger.debug(f'Attempt {attempt + 1}: This mutation has already been created!')
                continue

            # make sure it's a legal mutation
            dep_graph_after = analyze_dependence(cloned_program, loop_analysis)
            if not is_valid(dep_graph_before, dep_graph_after):
                if DEBUG:
                    logger.debug(f'Attempt {attempt + 1}: This transformation is invalid!')
                continue

            self.hashes.add(program_hash)
            return cloned_program
        return None
