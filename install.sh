#!/bin/sh

echo "#####   1. CHECKING USER   #####"
sleep 2;
user=$(ls /home)
echo "user is ----->$user<-----??   [Y/n]"

read ans
if [[ "$ans" =~ ^[Yy]$ || "$ans" == "" ]]; then
	continue
else
	echo "ERROR"
	echo "ERROR"
	echo "ERROR"
	echo "ERROR"
	echo "#####   Script has failed!   #####"
fi

# Refresh sudo privileges and keep them alive during the script execution
sudo -v
while true; do sudo -v; sleep 60; done &
# Store the background process ID
SUDO_LOOP_PID=$!
cd "/home/$user" || { echo "Failed to change directory to HOME"; exit 1; }
set -e  # Exit script on any error
# WORKING DIRECTORY
osdwm="/home/$user/dwkeprzz"
fdir="/home/$user/.local/share/fonts"
cdir="/home/$user/.config"
pac() {
    sudo pacman -S --needed --noconfirm "$@"
}

echo ""
echo ""
echo ""
echo "#####   2. INSTALLING PACKAGES   #####"
sleep 2;
# Installing Packages
pac xorg-server xorg-xinit xorg-xset xorg-xev base-devel || { echo "xorg-server xorg-xinit xorg-xset xorg-xev base-devel installation failed!"; exit 1; }
pac pipewire pipewire-alsa pipewire-pulse pipewire-jack wireplumber pavucontrol || { echo "pipewire pipewire-alsa pipewire-pulse pipewire-jack wireplumber pavucontrol installation failed!"; exit 1; }
pac alacritty dunst fastfetch feh neovim brightnessctl picom zoxide || { echo "alacritty dunst fastfetch feh neovim brightnessctl picom zoxide installation failed!"; exit 1; }
pac thunar tumbler ntfs-3g tree unzip zip bc xclip cronie btop fzf xfce4-screenshooter xdotool || { echo "thunar tumbler ntfs-3g tree unzip zip bc xclip cronie btop fzf xfce4-screenshooter xdotool installation failed!"; exit 1; }
pac firefox libreoffice-still || { echo "Firefox and LibreOffice installation failed!"; exit 1; }



echo ""
echo ""
echo ""
echo "#####   3. MAKING DIRECTORIES FOR FONTS   #####"
sleep 2;
# Fonts Installation
[ -d "$fdir" ] || mkdir -p "$fdir"
echo "Fonts directory ready"



echo ""
echo ""
echo ""
echo "#####   4. CONFIGURING SUCKLESS   #####"
sleep 2;
cp -r "$osdwm/dwkevinm/" "/home/$user/" || { echo "Failed to configure SUCKLESS"; exit 1; }
[ -d "$cdir" ] || mkdir -p "$cdir"
cp -r "$osdwm/dotconfig/"* "$cdir/" || { echo "Failed to copy dotconfig files"; exit 1; }
cp "$osdwm/bashrc" "/home/$user/.bashrc" || { echo "Failed to copy bashrc"; exit 1; }
cp "$osdwm/xinitrc" "/home/$user/.xinitrc" || { echo "Failed to copy xinitrc"; exit 1; }



echo ""
echo ""
echo ""
echo "#####   5. CONFIGURING SCRIPT   #####"
sleep 2;
# Configuring scripts
chmod +x "$osdwm/bin/"* || { echo "Failed to set executable permissions for scripts"; exit 1; }
sudo cp -r "$osdwm/bin/"* /usr/bin/ || { echo "Failed to copy scripts to /usr/bin"; exit 1; }
# Creating Windows mounting Directories
mkdir -p "/home/$user/DATA_D" "/home/$user/windows" "/home/$user/SamsungGalaxyA50"  || { echo "Failed to create directories"; exit 1; }



echo ""
echo ""
echo ""
echo "#####   6. CHECKING PACKAGES   #####"
sleep 2;
# List of packages to check
packages_to_check=(
	"libxft" "imlib2" "libxinerama" "libx11"
	"xorg-server" "xorg-xinit" "xorg-xset" "xorg-xev" "base-devel"
	"pipewire" "pipewire-alsa" "pipewire-pulse" "pipewire-jack" "wireplumber" "pavucontrol"
	"alacritty" "dunst" "fastfetch" "feh" "neovim" "brightnessctl" "picom" "zoxide"
	"thunar" "tumbler" "ntfs-3g" "tree" "unzip" "zip" "bc" "xclip" "cronie" "btop" "fzf" "xfce4-screenshooter" "xdotool"
	"firefox" "libreoffice-still"
)
# Function to check if a package is installed
check_installed() {
    uninstalled_packages=()  # Array to hold uninstalled packages

    for pkg in "$@"; do
        if sudo pacman -Q "$pkg" > /dev/null 2>&1; then
			continue
        else
            uninstalled_packages+=("$pkg")  # Add uninstalled package to the array
        fi
    done

    # Check if there are any uninstalled packages and echo them
    if [ ${#uninstalled_packages[@]} -gt 0 ]; then
		echo "The following packages are NOT installed:"
        for uninstalled in "${uninstalled_packages[@]}"; do
            echo "- $uninstalled"
        done
		echo "	    We need it for the system to work, install it!"
    else
        echo "All packages have successfully installed."
    fi
}

# Call the function with the list of packages
check_installed "${packages_to_check[@]}"


echo "" >> "/home/$user/.bash_profile"
echo "startx" >> "/home/$user/.bash_profile"


echo ""
echo ""
echo ""
echo "#####   7. CONFIGURING SLOCK   #####"
sleep 2;
# Configuring SLOCK
sudo cp -r "$osdwm/slock@.service" /etc/systemd/system/ || { echo "Failed to copy slock service file"; exit 1; }
echo "Running 'sudo systemctl enable slock@$user' to run slock on suspend"
sudo systemctl enable slock@$user || { echo "Failed to enable slock@$user service"; exit 1; }
echo "slock@$user service has been enabled"



echo ""
echo ""
echo ""
echo "#####   8. CONFIGURING FSTAB   #####"
sleep 2;
# FSTAB configuration
echo "" > "$osdwm/fstab"
echo "# /dev/sda3 (C:/)" >> "$osdwm/fstab"
echo "/dev/sda3 /home/$user/windows ntfs-3g defaults,noauto,x-systemd.automount,x-systemd.idle-timeout=60,x-systemd.device-timeout=5s,windows_names,uid=1000,gid=1000,umask=0022,fmask=0022 0 0" >> "$osdwm/fstab"
echo "" >> "$osdwm/fstab"
echo "# /dev/sdb3 (D:/)" >> "$osdwm/fstab"
echo "/dev/sdb3 /home/$user/DATA_D ntfs-3g defaults,noauto,x-systemd.automount,x-systemd.idle-timeout=60,x-systemd.device-timeout=5s,windows_names,uid=1000,gid=1000,umask=0022,fmask=0022 0 0" >> "$osdwm/fstab"
sudo sh -c "cat \"$osdwm/fstab\" >> /etc/fstab" || { echo "Failed to append generated fstab to /etc/fstab"; exit 1; }
sudo mount -a || { echo "Invalid fstab entries!"; exit 1; }
sudo systemctl daemon-reload || { echo "Failed to reload daemon"; exit 1; }
echo "Daemon reloaded successfully"



echo ""
echo ""
echo ""
echo "#####   9. WINDOWS ON GRUB   #####"
sleep 2;
winefpar() {
    # List the devices with numbers, removing "Start", "End", and "Sectors" columns
    echo "Which one is the Windows EFI partition?"
	 echo ""
    sudo fdisk -l | grep -E "Device|^/dev/sda|^/dev/sdb" | awk '{print $1, $5, $6, $7}' | nl
	 echo ""

    # Prompt user for input
    echo -n "Enter the number to select: "
    read device_number

    # Get the device name based on the input
    device_name=$(sudo fdisk -l | grep -E "Device|^/dev/sda|^/dev/sdb" | awk '{print $1, $5, $6, $7}' | nl | sed -n "${device_number}p" | awk '{print $2}')

    # Display the selected device name
    if [ -n "$device_name" ]; then
        echo "You selected: $device_name"
    else
        echo "Invalid input. Please enter a valid number."
        return 1  # Indicate failure, prompt again
    fi

    # Get the UUID of the selected device
    uuid=$(sudo blkid "$device_name" | awk -F'"' '{print $2}')
    
    # Display the UUID
	 echo ""
    echo "UUID of selected device ($device_name): $uuid"
    
    echo "Is that correct? (y/n)"
    read ans
    if [[ "$ans" =~ ^[Yy]$ || "$ans" == "" ]]; then
        return 0  # Exit successfully
    else
        return 1  # Restart the loop
    fi
}
# Run the function in a loop until successful completion (user confirms the correct partition)
while ! winefpar; do
    # Loop continues if the function returns non-zero (failure)
    echo "Please try again."
done
echo "" > winef
echo "" >> winef
echo "menuentry \"Windows 10\" --class windows --class os {" >> winef
echo "	search --fs-uuid --no-floppy --set=root $uuid" >> winef
echo "   chainloader (\${root})/EFI/Microsoft/Boot/bootmgfw.efi" >> winef
echo "}" >> winef
sudo sh -c "cat \"winef\" >> /etc/grub.d/40_custom" || { echo "Failed to append generated windows EFI partition grub"; exit 1; }
echo "Windows successfully added to Grub"


echo ""
echo ""
echo ""
echo "#####   10. Killing sudo   #####"
sleep 2;
# At the end of the script, kill the background process to stop the loop
echo "killing sudo -v"
kill $SUDO_LOOP_PID
echo "Done"


echo ""
echo ""
echo ""
echo "######   #######   #     #   ######"
echo "#     #  #     #   ##    #   #     "
echo "#     #  #     #   #  #  #   ####  "
echo "#     #  #     #   #    ##   #     "
echo "######   #######   #     #   ######"
echo ""
echo ""
echo ""
echo "Do we Reboot? [Y/n]"
read ans
if [[ "$ans" =~ ^[Yy]$ || "$ans" == "" ]]; then
	echo "Rebooting"; sleep 3
	sudo systemctl reboot
else
	echo ""
	echo ""
	echo ""
	echo "#####   Script completed successfully!   #####"
fi
