#!/bin/sh

make
./main.out -t -d --swap2 complete -a simple -p simple # VND is inefficient
./main.out -t -d --swap2 no -p reactive # Reactive Perturb is inefficient
./main.out -t --swap2 no  # ILS without \mu is inefficient
./main.out -t -d --swap2 no # Main ILS beats them
