#!/bin/bash
while true 
do 
  num=$((RANDOM % 10 + 1))
  img="/home/teaper/.config/chadwm/scripts/bgimgs/Travel$num.png"
  feh --bg-fill "$img" 
  sleep 300 
done
