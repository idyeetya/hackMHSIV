#!/bin/bash

# Access the arguments passed from Node.js
d_intercept=$1
f_intercept=$2
d_scale=$3
f_scale=$4
max=$5

gcc -o ~/Documents/big_hackMHS/dangerous/text_editor.out ~/Documents/big_hackMHS/dangerous/text_edit.c
/Users/adityasaccount/Documents/big_hackMHS/dangerous/text_editor.out $max $f_scale $f_intercept $d_scale $d_intercept
#./Users/adityasaccount/Documents/big_hackMHS/dangerous/text_editor.out 800 200 50 1 1


arduino-cli core update-index
arduino-cli board list
arduino-cli board listall mkr
arduino-cli core install arduino:samd
arduino-cli core list
arduino-cli board attach -p /dev/tty.usbmodem* -b arduino:avr:uno
arduino-cli compile --fqbn arduino:avr:uno ~/Documents/big_hackMHS/hackmhs/hackmhs.ino
arduino-cli upload -p /dev/tty.usbmodem* --fqbn arduino:avr:uno ~/Documents/big_hackMHS/hackmhs/hackmhs.ino
