#!/bin/bash
WALLPAPER_FOLDER="/home/teaper/.config/chadwm/scripts/bgimgs"
WALLPAPER_INDEX=25
#从第25张图片开始，2分钟换一张，超过 30 重新放第 1 张
while true
do
    WALLPAPER_FILE="${WALLPAPER_FOLDER}/Travel${WALLPAPER_INDEX}.png"
    feh --bg-fill "$WALLPAPER_FILE"

    WALLPAPER_INDEX=$((WALLPAPER_INDEX + 1))
    if [ $WALLPAPER_INDEX -gt 30 ]
    then
        WALLPAPER_INDEX=1
    fi

    sleep 120
done
