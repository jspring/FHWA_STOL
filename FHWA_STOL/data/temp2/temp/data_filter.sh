#!/bin/bash
# Removes useless text, colons, etc. from VDOT files

FILE=$1

cat $FILE | grep -v "SPEED IN MPH" | grep -v "RTMS"  >$FILE.mod
cat $FILE.mod | tr '\n' '\r' >$FILE.mod2
cat $FILE.mod2 | sed -r '{s/\t+/ /g}' >$FILE.mod3
cat $FILE.mod3 | sed -r '{s/--------\r\rpv/#######/g}' >$FILE.mod4
cat $FILE.mod4 | sed -r '{s/-+//g}' >$FILE.mod5
cat $FILE.mod5 | sed -r '{s/\r//g}' >$FILE.mod6
cat $FILE.mod6 | sed -r '{s/#######/\r/g}' >$FILE.mod7
cat $FILE.mod7 | tr '\r' '\n' >$FILE.mod8
cat $FILE.mod8 | tr -s '\n' >$FILE.mod9
cat $FILE.mod9 | sed -e '{s/FWDLK SPEED ?//g}' -e '{s/Dir..................//g}' >$FILE.mod10
cat $FILE.mod10 | sed -e '{s/MESSAGE NO\.//g}' -e '{s/VOLUME://g}' -e '{s/MED://g}' -e '{s/LARGE://g}' -e '{s/TRUCK://g}' -e '{s/STATION ID\.//g}' -e '{s/OCCUPANCY://g}' -e '{s/SIDEFRD SPD://g}' -e '{s/SPEED 85%://g}' -e '{s/GAP://g}' -e '{s/ \. / /g}' -e '{s/#/ /g}'  -e '{s/?/0/g}' -e '{s/pv//g}' -e '{s/: /:/g}' >$FILE.mod11
cat $FILE.mod11 | sed -r '{s/ +/ /g}' >$FILE.mod12
cat $FILE.mod12 | sed -e '{s/[0-9][0-9] [0-9][0-9] 2013 [0-9][0-9]:[0-9][0-9]:[0-9][0-9]:[0-9][0-9] /BREAK &/g}' >$FILE.mod13
mv $FILE.mod13 $FILE.new
#rm $FILE.mod*
#22 02 2013 17:28:22:00
