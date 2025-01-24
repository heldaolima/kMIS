#!/bin/sh

make
./main.out -t --swap2 no -a simple -p reactive # ILS-1
&& ./main.out -t -d --swap2 no -p reactive -a simple # ILS-2
&& ./main.out -t -d --swap2 no -p simple -a simple # ILS-3
&& ./main.out -t -d --swap2 no -p simple -a reactive # ILS-4
