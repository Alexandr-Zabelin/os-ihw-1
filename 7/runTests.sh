#!/bin/bash

make

./Main ../test_sets/corrects/1.txt ./test_results/corrects/1.txt
./Main ../test_sets/corrects/2.txt ./test_results/corrects/2.txt

./Main ../test_sets/incorrects/1.txt ./test_results/incorrects/1.txt
./Main ../test_sets/incorrects/2.txt ./test_results/incorrects/2.txt
