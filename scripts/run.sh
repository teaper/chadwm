#!/bin/sh
xrdb merge ~/.config/.Xresources
xbacklight -set 30 &
xset r rate 200 50 &
picom &

fcitx5 -d &
# flameshot &
# sudo pacman -S udisks2 udiskie https://wiki.archlinux.org/title/Udisks_(%E7%AE%80%E4%BD%93%E4%B8%AD%E6%96%87)#udiskie
udiskie &

#禁用触摸板 xinput <disable / enable> id
xinput disable $(xinput | awk '/Touchpad/{print $0}' | awk '{print $6}' | awk -F '=' '{print $2}')


~/.config/chadwm/scripts/bar.sh &

# ~/.config/chadwm/scripts/bg.sh &
# ~/.config/chadwm/scripts/bgv.sh &
# feh --bg-fill /home/teaper/.config/chadwm/scripts/bgimgs/Travel9.png
feh --bg-fill /home/teaper/.config/chadwm/scripts/bgimgs/122770110_p0.png

# eww 官方文档：https://elkowar.github.io/eww/eww.html
while type dwm >/dev/null; do dwm && continue || break; done
