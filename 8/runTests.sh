#!/bin/bash

make

./LogicHandler &
sleep 0.1
./IOHandler ../test_sets/corrects/1.txt ./test_results/corrects/1.txt

./LogicHandler &
sleep 0.1
./IOHandler ../test_sets/corrects/2.txt ./test_results/corrects/2.txt

./LogicHandler &
sleep 0.1
./IOHandler ../test_sets/incorrects/1.txt ./test_results/incorrects/1.txt

./LogicHandler &
sleep 0.1
./IOHandler ../test_sets/incorrects/2.txt ./test_results/incorrects/2.txt
