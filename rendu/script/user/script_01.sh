#!/bin/bash


# Affichage du hostname
echo -ne "Le Hostname est:\n"
hostname

# Affichage des adresse IP des interfaces réseaux
interfaces=$(ifconfig | grep Link | awk -F" " '{print $1}')
for interface in $interfaces
do
	echo -ne  "\nL'adresse IP de$interfaceest:\n"
	ip addr | grep inet | grep $interface$ | awk -F" " '{print $2}'
done

# Affichage du nom de la distribution
echo -ne "\nLa distribution est:\n"
lsb_release -d | awk -F":	" '{print $2}'

# Affichage de la version la distribution
echo -ne "\nLa version de la distribution est:\n"
lsb_release -r | awk -F" " '{print $2}'

# Affichage de la version du noyau
echo -ne "\nLa version du noyau est:\n"
uname -sr

# Affichage de la table de routage de la machine
echo -ne "\nLa table de routage est:\n"
route

echo -ne "Fin de l'éxécution du script\n"
