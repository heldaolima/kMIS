#!/bin/sh

make
./main.out -t --swap2 no -a simple -p reactive && ./main.out -t -d --swap2 no -p reactive -a simple && ./main.out -t -d --swap2 no -p simple -a simple && ./main.out -t -d --swap2 no -p simple -a reactive 
