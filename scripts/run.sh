#!/bin/sh
xrdb merge ~/.Xresources 
xbacklight -set 30 &
#feh --bg-fill ~/Pictures/wall/chad.png &
feh --bg-fill ~/Pictures/wall/yinm.jpg
#feh --bg-fill ~/Pictures/wall/8c.png
xset r rate 200 50 &
picom &

fcitx5 -d &
# flameshot &
# sudo pacman -S udisks2 udiskie https://wiki.archlinux.org/title/Udisks_(%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87)#udiskie
udiskie &

#禁用触摸板 xinput <disable / enable> id
xinput disable $(xinput | awk '/Touchpad/{print $0}' | awk '{print $6}' | awk -F '=' '{print $2}')
~/.config/chadwm/scripts/bar.sh &
# eww 官方文档：https://elkowar.github.io/eww/eww.html
while type dwm >/dev/null; do dwm && continue || break; done
