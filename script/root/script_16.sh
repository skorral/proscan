#!/bin/bash
#affiche toutes les chaînes de la table de filtrage
echo "Affiche les règles de filter"
iptables -t filter -L
#affiche toutes les chaînes de la table nat 
iptables -t nat -L
#affiche toutes les chaînes de la table mangle
iptables -t mangle -L
