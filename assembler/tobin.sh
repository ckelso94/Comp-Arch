#!/bin/zsh
awk '{print toupper($0)}' < dats-fmt.txt > uppera.out
echo 'ibase=16;obase=2;' | bc < uppera.out | python padzero.py > bina.out

