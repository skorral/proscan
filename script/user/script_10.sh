
#!/bin/bash

bleuclair='\e[1;34m'
neutre='\e[0;m'
orange='\e[0;33m'
# Affichage des paquets installés
echo -ne "${orange}Les paquets installés sont:${bleuclair}\n"
dpkg --get-selections

echo -ne "${orange}Les paquets à mettre à jour sont:${bleuclair}\n"
sudo apt-get --simulate upgrade
echo -ne  "${neutre} \n"
