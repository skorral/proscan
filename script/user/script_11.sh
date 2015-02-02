#!/bin/bash
#Affiche qui est loggé
echo "User loggé"
who -a
#Affiche l'heure du dernier boot
echo "time of last system boot"
who -b
#Affiche les processus morts
echo "Affiche les processus morts"
who -d
#Affiche le runlevel
echo "Affiche le runlevel actuel"
who -r
