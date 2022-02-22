#!/bin/sh

gcc -o launcher launcher.c wrappers/MoveFun.c -lwiringPi
./launcher