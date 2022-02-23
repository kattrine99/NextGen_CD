#!/bin/sh

gcc -o launcher launcher.c wrappers/MoveFun.c wrappers/UltraSonic.c wrappers/IRSenFun.c -lwiringPi
./launcher