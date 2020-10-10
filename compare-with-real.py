from parser import parse_file
from os import listdir
from random import shuffle
from shutil import copyfile
from pathlib import Path
from loguru import logger
from dependence_analysis import analyze_dependence
from variable_map import create_instance, VariableMap
from transformers.loop_unroll import LoopUnroll

def get_next_batch(n):    
    done_dir = '/mnt/d/real-patterns/patterns/done'
    existing = listdir(done_dir)

    dst_dir = '/mnt/d/real-patterns/patterns'


    cant_dir = f'{dst_dir}/cant'
    cant = listdir(cant_dir)

    blacklisted = cant + existing

    src_dir = '/mnt/d/real-patterns/code'
    srcs = [name for name in listdir(src_dir)
            if name not in blacklisted]
    shuffle(srcs)

    for name in srcs[:n]:
        copyfile(f'{src_dir}/{name}', f'{dst_dir}/skip/{name}')

# get_next_batch(10)
def test_parse():    
    d = '/mnt/d/real-patterns/patterns'
    loop_unroll = LoopUnroll(4)
    for s in listdir(d):
        if not s.endswith('.c'):
            continue
        path = f'{d}/{s}'
        logger.info(f'parsing {path}')
        try:
            var_map = VariableMap()
            var_map.set_min('dst_ystride', 2)
            var_map.set_max('dst_ystride', 5)
            var_map.set_min('src_ystride', 2)
            var_map.set_max('src_ystride', 5)
            var_map.set_min('scalar_index', 1)
            var_map.set_max('scalar_index', 32)
            var_map.set_min('stride', 1)
            var_map.set_max('stride', 30)
            var_map.set_min('stride1', 1)
            var_map.set_max('stride1', 10)
            var_map.set_min('stride2', 1)
            var_map.set_max('stride2', 10)
            var_map.set_min('offset1', 2)
            var_map.set_max('offset1', 5)
            var_map.set_min('offset2', 2)
            var_map.set_max('offset2', 5)
            var_map.set_min('offset3', 2)
            var_map.set_max('offset3', 5)
            var_map.set_min('offset4', 2)
            var_map.set_max('offset4', 5)
            var_map.set_min('offset5', 2)
            var_map.set_max('offset5', 5)
            var_map.set_min('small1_greater_eq', 1)
            var_map.set_max('small1_greater_eq', 30)
            var_map.set_min('small1_less_eq', 30)
            var_map.set_max('small1_less_eq', 60)
            var_map.set_min('small2_greater_eq', 1)
            var_map.set_max('small2_greater_eq', 30)
            var_map.set_min('small2_less_eq', 30)
            var_map.set_max('small2_less_eq', 60)
            var_map.set_min('small3_greater_eq', 1)
            var_map.set_max('small3_greater_eq', 30)
            var_map.set_min('small3_less_eq', 30)
            var_map.set_max('small3_less_eq', 60)
            var_map.set_min('small4_greater_eq', 1)
            var_map.set_max('small4_greater_eq', 30)
            var_map.set_min('small4_less_eq', 30)
            var_map.set_max('small4_less_eq', 60)
            var_map.set_min('medium1_greater_eq', 1)
            var_map.set_max('medium1_greater_eq', 10)
            var_map.set_min('medium1_less_eq', 100)
            var_map.set_max('medium1_less_eq', 110)

            pattern, _ = parse_file(path)
            instance = create_instance(pattern, var_map)
            logger.info(instance.pprint())
            mutation = next(loop_unroll.transform(instance))
            logger.info('4')
            logger.info(mutation.pprint())
        except Exception as e:
            print(e)

# get_next_batch(20)
# exit(0)

import sys
logger.remove()
logger.add(sys.stderr, level='DEBUG')
test_parse()
