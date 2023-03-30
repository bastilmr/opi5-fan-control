#! /usr/bin/bash

# ----------------------------------------------------- Links ------------------------------------------------------ #

# https://github.com/orangepi-xunlong/wiringOP

# ---------------------------------------------------- Colors ------------------------------------------------------ #

Cyan='\033[1;36m'
NoColor='\033[0m'

wiringOP="--branch next https://github.com/orangepi-xunlong/wiringOP.git"

# ----------------------------------------------------- Setup ------------------------------------------------------ #

# Welcome + Enter sudo password
clear
echo -e "${Cyan}"
printf "Welcome \360\237\246\204 \360\237\220\247 \360\237\220\263 \360\237\222\273 \n\n"
printf "Please enter your 'sudo' password: "
read -s password
echo -e "${NoColor} \n"

# Update
echo -e "${Cyan}Update Packages.. ${NoColor}"
sleep 1
echo $password | sudo -S apt update

# Upgrade
echo -e "\n${Cyan}Upgrade Packages.. ${NoColor}"
sleep 1
echo $password | sudo -S apt upgrade -y
sleep 2

# Install Git
echo -e "\n${Cyan}Install Git.. ${NoColor}"
sleep 1
echo $password | sudo -S apt install git -y
sleep 2

# Clone wiringOP
echo -e "\n${Cyan}Clone wiringOP.. ${NoColor}"
sleep 1
echo $password | sudo -S git clone $wiringOP
sleep 2

# Install wiringOP
echo -e "\n${Cyan}Install wiringOP.. ${NoColor}"
sleep 1
cd wiringOP/
./build clean
sleep 1
# ./build
cd ..
sleep 2

# Remove wiringOP
echo -e "\n${Cyan}Remove wiringOP Directory.. ${NoColor}"
sleep 1
echo $password | sudo -S rm -rf wiringOP/
sleep 2

# Test wiringOP
echo -e "\n${Cyan}Test wiringOP.. ${NoColor}"
sleep 1
gpio readall