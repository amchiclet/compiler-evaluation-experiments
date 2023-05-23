from pathlib import Path
from codegen.c_generator import generate_code
from shutil import copytree
from csv import writer

def conf_contents(codelet):
    return (f'<?xml version="1.0" ?>\n'
            f'<codelet>\n'
            f'  <language value="C"/>\n'
            f'  <label name="{codelet}"/>\n'
            f'  <function name="core"/>\n'
            f'  <binary name="wrapper"/>\n'
            f'</codelet>\n')

def meta_contents(batch, code, codelet):
    return (f'application name=LoopGen\n'
            f'batch name={batch}\n'
            f'code name={code}\n'
            f'codelet name={codelet}\n')

def data_contents(n_iterations, n_elements):
    return f'{n_iterations} {n_elements}\n'

def data_contents_var_ints(n_iterations, var_ints):
    int_inputs_str = ' '.join([str(i) for i in var_ints])
    return f'{n_iterations} {int_inputs_str}\n'

def batch_dir(application, batch, base='.'):
    return f'{base}/{application}/{batch}'

def codelet_dir(application, batch, code, codelet, base='.'):
    return f'{batch_dir(application, batch, base)}/{code}/{codelet}'

def source_info_file(codelet_dir):
    return f'{codelet_dir}/src_info.csv'

def meta_file(codelet_dir):
    return f'{codelet_dir}/codelet.meta'

def conf_file(codelet_dir):
    return f'{codelet_dir}/codelet.conf'

def data_file(codelet_dir):
    return f'{codelet_dir}/codelet.data'

def prepare_output_dir(dst_dir):
    copytree('c-template', dst_dir, dirs_exist_ok=True)

def name_many(nodes, delimiter=''):
    return delimiter.join([name(node) for node in nodes])

def name(node):
    from pattern_ast import Hex, Assignment, AbstractLoop, Literal, Access, Program, Op
    ty = type(node)
    if ty == Literal:
        return 'x'
    if ty == Hex:
        return node.str_val
    if ty == Assignment:
        return f'_set_{name(node.lhs)}{name(node.rhs)}'
    if ty == Access:
        return f'{node.var}{name_many(node.indices)}'
    if ty == AbstractLoop:
        return '_then_'.join([name(stmt) for stmt in node.body])
    if ty == Op:
        op_map = {
            '+': '_add_',
            '*': '_mul_'
        }
        return f'{op_map[node.op]}{name_many(node.args)}'
    if ty == Program:
        assert(len(node.body) == 1)
        return name(node.body[0])
    print(ty)

def generate_codelet_full(application, batch, code, codelet,
                          n_iterations, n_elements, instance,
                          init_value_map=None):
    dst_dir = codelet_dir(application, batch, code, codelet)
    Path(dst_dir).mkdir(parents=True, exist_ok=True)
    # prepare_output_dir(dst_dir)

    Path(meta_file(dst_dir)).write_text(meta_contents(batch, code, codelet))
    Path(conf_file(dst_dir)).write_text(conf_contents(codelet))
    Path(data_file(dst_dir)).write_text(data_contents(n_iterations, n_elements))

    generate_code(dst_dir, instance, init_value_map=init_value_map, template_dir='codelet-template')

def generate_codelet_var_ints(application, batch, code, codelet,
                              n_iterations, int_inputs, instance,
                              init_value_map=None):
    dst_dir = codelet_dir(application, batch, code, codelet)
    Path(dst_dir).mkdir(parents=True, exist_ok=True)
    # prepare_output_dir(dst_dir)

    Path(meta_file(dst_dir)).write_text(meta_contents(batch, code, codelet))
    Path(conf_file(dst_dir)).write_text(conf_contents(codelet))
    Path(data_file(dst_dir)).write_text(data_contents_var_ints(n_iterations, int_inputs))

    generate_code(dst_dir, instance, init_value_map=init_value_map, template_dir='codelet-template-int-inputs')

def generate_codelet_files(application, batch, code, codelet, n_iterations, int_inputs):
    dst_dir = codelet_dir(application, batch, code, codelet)
    Path(dst_dir).mkdir(parents=True, exist_ok=True)
    # prepare_output_dir(dst_dir)

    Path(meta_file(dst_dir)).write_text(meta_contents(batch, code, codelet))
    Path(conf_file(dst_dir)).write_text(conf_contents(codelet))
    Path(data_file(dst_dir)).write_text(data_contents_var_ints(n_iterations, int_inputs))

    return dst_dir

class SourceInfo:
    def __init__(self):
        self.name = ''
        self.n_stmts = 0
        self.scalars = []
        self.arrays = []
        self.ops = []
        self.extra_columns = []

    def header(extra_headers):
        return ['name',
                '# stmts',
                'scalar refs',
                'array refs',
                'ops'] + extra_headers

    def columns(self):
        # print_sum formats a list representing a summation
        # Example: given [3, 5, 2], returns '3+5+2 = 10'
        def print_sum(l):
            if len(l) == 1:
                return str(l[0])
            return f'{"+".join(map(str, l))} = {sum(l)}'

        return [self.name,
                str(self.n_stmts),
                print_sum(self.scalars),
                print_sum(self.arrays),
                print_sum(self.ops)] + self.extra_columns

class SourceInfoFlex():
    def __init__(self, ordered_header):
        self.m = {}
        self.ordered_header = ordered_header

    def __setitem__(self, key, value):
        if key not in self.ordered_header:
            raise KeyError(f'{key} is not in allowed keys ({self.ordered_header})')
        self.m[key] = value

    def __getitem__(self, key):
        return self.m[key]

    def header(self):
        return self.ordered_header

    def columns(self):
        r = []
        for key in self.ordered_header:
            if key in self.m:
                r.append(self.m[key])
            else:
                r.append('')
        return r

def generate_batch_summary(application, batch, source_infos, extra_headers=None):
    dst_dir = batch_dir(application, batch)
    Path(dst_dir).mkdir(parents=True, exist_ok=True)

    with open(source_info_file(dst_dir), 'w', newline='') as csvfile:
        w = writer(csvfile, dialect='excel')
        extra_headers = [] if extra_headers is None else extra_headers
        w.writerow(SourceInfo.header(extra_headers))
        for si in source_infos:
            w.writerow(si.columns())

def generate_batch_summary_flex(application, batch, source_infos, header):
    dst_dir = batch_dir(application, batch)
    Path(dst_dir).mkdir(parents=True, exist_ok=True)

    with open(source_info_file(dst_dir), 'w', newline='') as csvfile:
        w = writer(csvfile, dialect='excel')
        w.writerow(header)
        for si in source_infos:
            w.writerow(si.columns())
