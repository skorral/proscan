#!/bin/bash
#Affiche les informations CPU
echo "Informations CPU"
cat /proc/cpuinfo
#Affiche les interruptions
echo "Interruptions"
cat /proc/interrupts
#affiche la mémoire utilisée
echo "Mémoire utilisé"
cat /proc/meminfo
#affiche le(s) fichier(s) swap
echo "Fichier SWAP"
cat /proc/swaps
#affiche la version du kernel 
echo "Version du kernel"
cat /proc/version
#affiche le(s) système(s) de fichiers monté(s)
echo "Système(s) de fichiers monté(é)"
cat /proc/mounts
#affiche les périphériques PCI
echo "Périphériques PCI"
lspci -tv
#affiche les périphériques usb
echo "Périphériques usb"
lsusb -tv

