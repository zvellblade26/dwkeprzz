#!/bin/sh

user=$(whoami)

xset r rate 250 60 &
setxkbmap -option caps:escape &

#picom &

feh --bg-fill --randomize /home/$user/Wallpapers/* &

dunst &

brightnessctl s 15 &

alacritty -o font.size=10 -e bash -c "fastfetch; pgtest-sh; exec bash" &

#firefox &

pavucontrol &

slstatus &

while true; do
    dwm >/dev/null 2>&1
done

exec dwm
