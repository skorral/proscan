#!/bin/bash

noir='\e[0;30m'
gris='\e[1;30m'
rougefonce='\e[0;31m'
rose='\e[1;31m'
vertfonce='\e[0;32m'
vertclair='\e[1;32m'
orange='\e[0;33m'
jaune='\e[1;33m'
bleufonce='\e[0;34m'
bleuclair='\e[1;34m'
bleu='\e[1;34m'
violetfonce='\e[0;35m'
violetclair='\e[1;35m'
cyanfonce='\e[0;36m'
cyanclair='\e[1;36m'
grisclair='\e[0;37m'
blanc='\e[1;37m'
neutre='\e[0;m'

# Affichage du hostname
echo -ne "${rose}Le Hostname est:${bleu}\n"
hostname

# Affichage des adresse IP des interfaces réseaux
interfaces=$(ifconfig | grep Link | awk -F" " '{print $1}')
for interface in $interfaces
do
	echo -ne  "\n${rose}L'adresse IP de ${jaune}$interface ${rose}est:${bleu}\n"
	ip addr | grep inet | grep $interface$ | awk -F" " '{print $2}'
done

# Affichage du nom de la distribution
echo -ne "\n${rose}La distribution est:${bleu}\n"
lsb_release -d | awk -F":	" '{print $2}'

# Affichage de la version la distribution
echo -ne "\n${rose}La version de la distribution est:${bleu}\n"
lsb_release -r | awk -F" " '{print $2}'

# Affichage de la version du noyau
echo -ne "\n${rose}La version du noyau est:${bleu}\n"
uname -sr

# Affichage de la table de routage de la machine
echo -ne "\n${rose}La table de routage est:${bleu}\n"
route

echo -ne "${neutre}Fin de l'éxécution du script\n"
