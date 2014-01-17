#!/bin/bash
# Removes useless text, colons, etc. from VDOT files

FILE=$1

cat $FILE | grep -v "SPEED IN MPH" | grep -v "RTMS STAT" |grep -v pv >$FILE.mod
cat $FILE.mod | tr '\n' '\r' >$FILE.mod2
cat $FILE.mod2 | sed -r '{s/\t+/ /g}' >$FILE.mod3
cat $FILE.mod3 | sed '{s/\r\r\s\r\r/#####/g}' >$FILE.mod4
cat $FILE.mod4 | tr '#####' '\r\n' >$FILE.mod5
cat $FILE.mod5 | tr '\r' ' ' >$FILE.mod6
cat $FILE.mod6 | tr -s '\n' >$FILE.mod7
cat $FILE.mod7 | sed -e '{s/FWDLK SPEED ?//g}' -e '{s/Dir..................//g}' >$FILE.mod8
cat $FILE.mod8 | sed -e '{s/[A-Z]://g}' -e '{s/[A-Z]//g}' -e '{s/ \. / /g}' -e '{s/#/ /g}'  -e '{s/?/0/g}' -e '{s/85%://g}' -e '{s/: /:/g}' -e '{s/:00 //g}' >$FILE.mod9
cat $FILE.mod9 | sed -r '{s/ +/ /g}' >$FILE.mod10
cat $FILE.mod10 | sed -r '{s/^ +//g}' >$FILE.mod11
mv $FILE.mod11 $FILE.new
rm $FILE.mod*
