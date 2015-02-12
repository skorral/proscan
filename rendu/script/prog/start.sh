#!/bin/sh
sudo cp etcinitproscan  /etc/init.d/proscan
sudo chmod +x /etc/init.d/proscan
sudo update-rc.d proscan default 80
