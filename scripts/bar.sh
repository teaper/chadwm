#!/bin/sh

# ^c$var^ = fg color
# ^b$var^ = bg color

interval=0

# load colors
. ~/.config/chadwm/scripts/bar_themes/onedark

cpu() {
  cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)

  printf "^c$black^ ^b$green^ CPU"
  printf "^c$green^ ^b$grey^ $cpu_val"
}

pkg_updates() {
  # updates=$(doas xbps-install -un | wc -l) # void
  updates=$(checkupdates | wc -l)   # arch
  # updates=$(aptitude search '~U' | wc -l)  # apt (ubuntu,debian etc)
  if [ -z "$updates" ]; then
    printf "  ^c$black^ ^b$green^  "
    printf "^c$green^ ^b$black^ $updates"
  else
    printf "  ^c$black^ ^b$green^  "
    printf "^c$green^ ^b$black^ $updates"
  fi
}

# 补充： pacman -S docker docker-compose
docker_ps() {
  dockers=$(docker ps -q | wc -l)
  printf "^c$blue^   $dockers"
}

battery() {
  get_capacity="$(cat /sys/class/power_supply/BAT0/capacity)"
  printf "^c$red^   $get_capacity"
}

brightness() {
  printf "^c$white^   "
  printf "^c$white^%.0f\n" $(cat /sys/class/backlight/*/brightness)
}

mem() {
  printf "^c$blue^^b$black^  "
  printf "^c$blue^ $(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

wlan() {
	case "$(cat /sys/class/net/wl*/operstate 2>/dev/null)" in
	up) printf "^c$black^ ^b$blue^ 󰤨  ^d^%s" " ^c$blue^已连接" ;;
	down) printf "^c$black^ ^b$red^ 󰤭  ^d^%s" " ^c$red^已断开" ;;
	esac
}

clock() {
	printf "^c$black^ ^b$darkblue^ 󱑆 "
	printf "^c$black^ ^b$blue^ $(date '+%m/%d %H:%M') "
}

while true; do

  [ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] && updates=$(pkg_updates)
  interval=$((interval + 1))

  sleep 1 && xsetroot -name "$updates $(docker_ps) $(battery) $(brightness) $(cpu) $(mem) $(wlan) $(clock)"
done
