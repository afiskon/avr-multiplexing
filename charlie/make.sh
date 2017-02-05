#!/bin/sh

set -e

avr-gcc -mmcu=attiny85 -Os main.c -o main.o
avr-objcopy -j .text -j .data -O ihex main.o main.hex
