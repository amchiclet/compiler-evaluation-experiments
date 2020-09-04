from dependence_analysis import analyze_dependence
from variable_map import VariableMap
import random
from sampler import Sampler
from math import factorial
from loguru import logger
from abstract_ast import get_loops, Access, AbstractLoop, Program, Op, Replacer, Literal, LoopShape

class UnrollReplacer(Replacer):
    def __init__(self, var, offset):
        self.var = var
        self.offset = offset
    def should_replace(self, node):
        return type(node) == Access and node.var == self.var
    def replace(self, node):
        return Op('+', [node.clone(), Literal(int, self.offset)])

# TODO: reuse rather than copy-paste
class IdGenerator:
    def __init__(self, current=0):
        self.current = current
    def next_id(self):
        r = self.current
        self.current += 1
        return r

class LoopUnroll:
    def __init__(self, max_factor):
        self.max_factor = max_factor

    def transform(self, instance):
        loops = get_loops(instance.pattern)
        loop_vars = []
        for loop_id, loop in loops.items():
            for shape in loop.loop_shapes:
                assert(type(shape.loop_var) == Access)
                loop_vars.append((loop_id, shape.loop_var.var))

        # sort by depth
        def depth_rec(node, id_var_pair, current_depth):
            loop_id, loop_var = id_var_pair
            if type(node) == Program:
                for stmt in node.body:
                    return depth_rec(stmt, id_var_pair, current_depth+1)
            elif type(node) == AbstractLoop:
                if node.node_id == loop_id:
                    for i, shape in enumerate(node.loop_shapes):
                        if shape.loop_var.var == loop_var:
                            return (current_depth, i)
                    raise RuntimeError(f'Loop var {loop_var} not found in {node.pprint()}')
                for stmt in node.body:
                    return depth_rec(stmt, id_var_pair, current_depth+1)
            else:
                return (current_depth + 1, 0)

        def depth(id_var_pair):
            return depth_rec(instance.pattern, id_var_pair, 0)

        sorted_loop_vars = sorted(loop_vars, key=depth, reverse=True)

        # TODO: assign unique node ids
        while True:
            cloned = instance.clone()

            for loop_id, loop_var in sorted_loop_vars:
                factor = random.randint(1, self.max_factor)
                if factor == 1:
                    continue
                loops = get_loops(cloned.pattern)
                loop = loops[loop_id]
                loop_shapes_before = []
                loop_shapes_after = []
                loop_var_index = None
                unroll_shape = None
                remainder_shape = None
                for i, shape in enumerate(loop.loop_shapes):
                    if shape.loop_var.var == loop_var:
                        loop_var_index = i
                        original_step = shape.step.clone()

                        # Build the unroll shape
                        # only support literals for simplicity
                        assert(type(shape.greater_eq) == Literal and shape.greater_eq.ty == int)
                        assert(type(shape.less_eq) == Literal and shape.less_eq.ty == int)
                        assert(type(shape.step) == Literal and shape.step.ty == int)

                        unroll_greater_eq = shape.greater_eq.val
                        unroll_step = shape.step.val * factor
                        unroll_n_iterations = (shape.less_eq.val - shape.greater_eq.val + shape.step.val) // (shape.step.val * factor)
                        unroll_less_eq = unroll_greater_eq + ((unroll_n_iterations - 1) * unroll_step)
                        unroll_shape = LoopShape(shape.loop_var.clone(),
                                                 Literal(int, unroll_greater_eq),
                                                 Literal(int, unroll_less_eq),
                                                 Literal(int, unroll_step))

                        # Build the remainder shape
                        remainder_greater_eq = unroll_less_eq + unroll_step
                        remainder_less_eq = shape.less_eq.val
                        remainder_step = shape.step.val
                        remainder_shape = LoopShape(shape.loop_var.clone(),
                                                    Literal(int, remainder_greater_eq),
                                                    Literal(int, remainder_less_eq),
                                                    Literal(int, remainder_step))
                        break
                    else:
                        loop_shapes_before.append(shape)

                assert(loop_var_index is not None)
                assert(unroll_shape is not None)
                assert(remainder_shape is not None)

                for shape in loop.loop_shapes[loop_var_index+1:]:
                    loop_shapes_after.append(shape)

                unrolled_body = []
                for f in range(0, factor):
                    unrolled_innermost_body = []
                    replacer = UnrollReplacer(loop_var, f)
                    for stmt in loop.body:
                        unrolled_stmt = stmt.clone()
                        unrolled_stmt.replace(replacer)
                        unrolled_innermost_body.append(unrolled_stmt)
                    if len(loop_shapes_after) == 0:
                        unrolled_body += unrolled_innermost_body
                    else:
                        shapes = [shape.clone() for shape in loop_shapes_after]
                        unrolled_body.append(AbstractLoop(shapes,
                                                          unrolled_innermost_body))

                remainder_innermost_body = [stmt.clone() for stmt in loop.body]
                if len(loop_shapes_after) == 0:
                    remainder_body = remainder_innermost_body
                else:
                    shapes = [shape.clone() for shape in loop_shapes_after]
                    remainder_body = [AbstractLoop(shapes, remainder_innermost_body)]

                unrolled_loop = AbstractLoop([unroll_shape], unrolled_body)
                remainder_loop = AbstractLoop([remainder_shape], remainder_body)

                # The unroll sequence is the unrolled loop followed by the remainder loop
                if len(loop_shapes_before) == 0:
                    unroll_sequence = [unrolled_loop, remainder_loop]
                else:
                    # The surrounding loop needs to preserve the loop_id
                    # since the surrounding loops may be unrolled as well
                    unroll_sequence = [AbstractLoop(loop_shapes_before,
                                                    [unrolled_loop, remainder_loop],
                                                    loop_id)]

                # Replace the original loop with the unroll sequence
                index = loop.surrounding_loop.find_stmt(loop)
                loop.surrounding_loop.remove_stmt(loop)
                loop.surrounding_loop.insert_stmts(index, unroll_sequence)

            yield cloned
