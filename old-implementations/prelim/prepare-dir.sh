#!/bin/bash -xe
[ -z $1 ] && echo "Directory not specified" && exit

mkdir -p $1
cp -r argparse dummy util test $1
cp run.c.template meson.template $1
cp ast.py build.py check.py config.py format.py main.py measure.py report.py run.py util.py $1
