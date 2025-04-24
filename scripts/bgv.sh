#!/bin/bash
# sudo pacman -S libvdpau-va-gl xwinwrap-git mpv
# xwinwrap -ni -ov -fs -s -st -sp -b -nf -- mpv --loop --mute --no-osc --no-osd-bar --panscan=1 --hwdec=auto --vo=gpu -wid WID ~/.config/chadwm/scripts/bgimgs/2023拜年祭.mp4
xwinwrap -ni -ov -fs -s -st -sp -nf -- mpv --loop --mute --no-osc --no-osd-bar --panscan=1 --hwdec=vaapi --vo=gpu --gpu-api=vulkan -wid WID ~/.config/chadwm/scripts/bgimgs/2024拜年祭.mp4
