#!/bin/bash

find .. -maxdepth 1 -name "*.c" > uncrustify_file_list.txt
find .. -maxdepth 1 -name "*.h" >> uncrustify_file_list.txt

#sed '/bsp_pins_conf.h/d' ./uncrustify_file_list.txt
grep -v bsp_pins_conf.h uncrustify_file_list.txt > temp && mv temp uncrustify_file_list.txt

uncrustify --no-backup -c uncrustify.cfg -F uncrustify_file_list.txt
