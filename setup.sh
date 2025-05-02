#!/usr/bin/env bash
set -e
sudo apt update
sudo apt install -y dkms build-essential linux-headers-$(uname -r)
sudo dkms add -m imx586 -v 0.1 || true
sudo dkms build -m imx586 -v 0.1
sudo dkms install -m imx586 -v 0.1
echo "Driver installed. Integrate the appropriate dtsi and reboot."
