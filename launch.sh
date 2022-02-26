#!/bin/sh

gcc -o launcher launcher.c wrappers/MoveFun.c wrappers/UltraSonicFun.c wrappers/IRSenFun.c wrappers/LineTracersFun.c -lwiringPi
./launcher