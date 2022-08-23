#!/bin/sh

xrdb merge ~/.Xresources 
xbacklight -set 30 &
feh --bg-fill ~/Pictures/wall/chad.png &
xset r rate 200 50 &
picom &

fcitx5 -d &
# flameshot &

~/.config/chadwm/scripts/bar.sh &
# eww 官方文档：https://elkowar.github.io/eww/eww.html
while type dwm >/dev/null; do dwm && continue || break; done
