#!/bin/sh
cpp test.s -o out.s
sed -i -e 's/@/\n/g' out.s
sed -i -e 's/~//g' out.s
python asm.py out.s
