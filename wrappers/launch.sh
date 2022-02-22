#!/bin/sh

gcc -o car check.c MoveFun.c -lwiringPi
./car