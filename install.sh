#!/bin/bash

git clone --branch next https://github.com/orangepi-xunlong/wiringOP.git
cd wiringOP
./build clean
./build
cd ../


gcc -o fan-control binary-fan-control.c -lwiringPi
chmod +x fan-control

sudo cp ./fan-control /bin/fan-control
echo '@reboot root /bin/fan-control' | sudo tee /etc/cron.d/opi5-fan-control

echo 'install success, please reboot'
