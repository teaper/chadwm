#!/bin/bash
while true 
do 
  num=$((RANDOM % 14 + 1))
  img="/home/teaper/.config/chadwm/scripts/bgimgs/Tuya$num.png"
  feh --bg-fill "$img" 
  sleep 300 
done





#while true 
#do 
#  num=$((RANDOM % 12 + 1))
#  img="/home/teaper/.config/chadwm/scripts/bgimgs/Travel$num.png"
#  feh --bg-fill "$img" 
#  sleep 300 
#done
