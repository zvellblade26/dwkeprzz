#!/bin/sh
user=$(whoami)
export DMENU_PATH="/home/$user/.local/bin/"
xset r rate 250 60 &
setxkbmap -option caps:escape &
feh --bg-fill --randomize "/home/$user/Wallpapers/"* &
dunst &
brightnessctl s 15 &
#alacritty -e bash -c "fastfetch; exec bash" &
picom --no-fading-openclose &
while true; do
	dwm > /dev/null 2>&1
done
exec dwm
