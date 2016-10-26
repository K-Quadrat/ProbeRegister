#!/bin/bash
rm main
rm main.o
gcc -c -I/usr/include/mysql main.cpp
gcc -o main main.o -L/usr/lib/x86_64-linux-gnu -lmysqlclient -lm
./main
