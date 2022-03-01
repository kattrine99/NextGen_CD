#!/bin/sh

gcc -o kill kill.c wrappers/MoveFun.c -lwiringPi
./kill