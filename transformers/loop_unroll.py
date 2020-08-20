from dependence_analysis import analyze_dependence
from variable_map import VariableMap
import random
from sampler import Sampler
from math import factorial
from loguru import logger
from abstract_ast import get_loops, Access, AbstractLoop, Program, Op, Replacer, Literal

class UnrollReplacer(Replacer):
    def __init__(self, var, offset):
        self.var = var
        self.offset = offset
    def should_replace(self, node):
        return type(node) == Access and node.var == self.var
    def replace(self, node):
        return Op('+', [node.clone(), Literal(int, self.offset)])

class LoopUnroll:
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
                unroll = random.choice([True, False])
                if not unroll:
                    continue
                factor = random.randint(1, 4)
                loops = get_loops(cloned.pattern)
                loop = loops[loop_id]
                loop_shapes_before = []
                loop_shapes_after = []
                loop_var_index = None
                unroll_shape = None
                for i, shape in enumerate(loop.loop_shapes):
                    if shape.loop_var.var == loop_var:
                        loop_var_index = i
                        unroll_shape = shape.clone()
                        unroll_shape.step = Literal(int, factor)
                        break
                    else:
                        loop_shapes_before.append(shape)
                assert(loop_var_index is not None)
                for shape in loop.loop_shapes[loop_var_index+1:]:
                    loop_shapes_after.append(shape)

                unrolled_body = []
                for f in range(0, factor):
                    innermost_body = []
                    replacer = UnrollReplacer(loop_var, f)
                    for stmt in loop.body:
                        unrolled_stmt = stmt.clone()
                        unrolled_stmt.replace(replacer)
                        innermost_body.append(unrolled_stmt)
                    if len(loop_shapes_after) == 0:
                        unrolled_body += innermost_body
                    else:
                        unrolled_body.append(AbstractLoop(loop_shapes_after, innermost_body))

                if len(loop_shapes_before) == 0:
                    loop.loop_shapes = [unroll_shape]
                    loop.body = unrolled_body
                else:
                    loop.loop_shapes = loop_shapes_before
                    loop.body = [AbstractLoop([unroll_shape], unrolled_body)]
            yield cloned
