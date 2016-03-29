#!/bin/zsh
awk '{print toupper($0)}' < a.out > uppera.out
echo 'ibase=16;obase=2;' | bc < uppera.out | python padzero.py > bina.out

