import random
import dependence_analysis as da
from abstract_ast import get_ordered_loops, Replacer, AbstractLoop, Literal, LoopShape, Access, Op

def merge_min_map(existing, new):
    for v, d in new.items():
        if v not in existing:
            existing[v] = d
        else:
            existing[v] = min(existing[v], d)

def get_min_distances(graph):
    min_distances = {}
    for deps in graph.iterate_dependences():
        for dep in deps:
            distances = da.get_min_distance(dep.source_ref, dep.sink_ref)
            merge_min_map(min_distances, distances)
    print(min_distances)
    return min_distances

def swap(i, j, l):
    t = l[i]
    l[i] = l[j]
    l[j] = t

def reorder(new_order, l):
    l[:] = [l[i] for i in new_order]

def is_positive(dv):
    for d in dv:
        if d == '>':
            return True
        if d == '<':
            return False
    return False

class UnrollReplacer(Replacer):
    def __init__(self, var, offset):
        self.var = var
        self.offset = offset
    def should_replace(self, node):
        return type(node) == Access and node.var == self.var
    def replace(self, node):
        return Op('+', [node.clone(), Literal(int, self.offset)])

def iterate_direction_vectors(graph, loop):
    for deps in graph.iterate_dependences_among(loop.body):
        for dep in deps:
            yield dep.direction_vector

def is_permutable(graph, loop, new_order):
    for dv in iterate_direction_vectors(graph, loop):
        cloned = list(dv)
        reorder(new_order, cloned)
        if is_positive(cloned):
            return False
    return True

# act as if moving it to innermost and check whether its positive or not
def is_legal(graph, loop, dim, factor):
    permutation = list(range(len(loop.loop_shapes)))
    del permutation[dim]
    permutation.append(dim)
    print(f'new permutation {permutation}')
    if is_permutable(graph, loop, permutation):
        print('its permutable, so its ok')
        return True
    min_distances = get_min_distances(graph)
    shape = loop.loop_shapes[dim]
    loop_var = shape.loop_var.var
    distance = factor * shape.step.val
    print(f'its not permutable, gotta check the factor ({factor}) distance ({distance})')
    if loop_var not in min_distances:
        print(f'loop var {loop_var} not found in min_distances')
        return False
    print(f'min distance for {loop_var} is {min_distances[loop_var]}')
    return distance <= min_distances[loop_var]
    
class LoopUnrollAndJam:
    def transform(self, instance):
        cloned = instance.clone()
        graph = da.analyze_dependence(cloned.pattern)
        min_distances = get_min_distances(graph)
        print(min_distances)

        # choose a loop var at random in loop_vars [0:-1]
        loops = get_ordered_loops(cloned.pattern)
        weights = [len(loop.loop_shapes) for loop in loops]
        which_loop = random.choices(loops, weights, k=1)[0]
        n_dims = len(which_loop.loop_shapes)
        # pick a dimension except the last
        which_dim = random.randint(1, n_dims-1) - 1  # zero indexed
        which_shape = which_loop.loop_shapes[which_dim]
        which_var = which_shape.loop_var.var

        # randomize unroll and jam factor
        factor = random.randint(2, 3)
        is_ok = is_legal(graph, which_loop, which_dim, factor)
        print(is_ok)
        if not is_ok:
            return None

        before_unroll_shapes = [shape.clone() for shape in which_loop.loop_shapes[:which_dim]]
        unrolled_shapes = []
        unroll_greater_eq = which_shape.greater_eq.val
        unroll_step = which_shape.step.val * factor
        unroll_n_iterations = (which_shape.less_eq.val - which_shape.greater_eq.val + which_shape.step.val) // unroll_step
        unroll_less_eq = unroll_greater_eq + ((unroll_n_iterations - 1) * unroll_step)
        unroll_shape = LoopShape(which_shape.loop_var.clone(),
                                 Literal(int, unroll_greater_eq),
                                 Literal(int, unroll_less_eq),
                                 Literal(int, unroll_step))
        unrolled_shapes = [unroll_shape] + [shape.clone() for shape in which_loop.loop_shapes[which_dim+1:]]
                                                                                              
        unrolled_body = []
        for f in range(0, factor):
            replacer = UnrollReplacer(which_var, f * which_shape.step.val)
            for stmt in which_loop.body:
                unrolled_stmt = stmt.clone()
                unrolled_stmt.replace(replacer)
                unrolled_body.append(unrolled_stmt)
        unrolled_loop = AbstractLoop(unrolled_shapes, unrolled_body)
    
        # Build the remainder shape
        remainder_greater_eq = unroll_less_eq + unroll_step
        remainder_less_eq = which_shape.less_eq.val
        remainder_step = which_shape.step.val
        remainder_shape = LoopShape(which_shape.loop_var.clone(),
                                    Literal(int, remainder_greater_eq),
                                    Literal(int, remainder_less_eq),
                                    Literal(int, remainder_step))
        remainder_shapes = [remainder_shape] + [shape.clone() for shape in which_loop.loop_shapes[which_dim+1:]]
        remainder_body = [stmt.clone() for stmt in which_loop.body]
        remainder_loop = AbstractLoop(remainder_shapes, remainder_body)

        sequence = [unrolled_loop, remainder_loop]
        if len(before_unroll_shapes) > 0:
            print('before unroll shapes yay')
            sequence = [AbstractLoop(before_unroll_shapes, sequence)]
        else:
            print('nothing before unroll')
    
        # Replace the original loop with the unroll sequence
        parent_block = which_loop.surrounding_loop
        index = parent_block.find_stmt(which_loop)
        parent_block.remove_stmt(which_loop)
        parent_block.insert_stmts(index, sequence)

        return cloned

