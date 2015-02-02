#!/bin/bash

rose='\e[1;31m'
bleu='\e[1;34m'
neutre='\e[0;m'

# Affichage de la derniére connexion local
echo -ne "${rose}La derniére connexion local est:${bleu}\n"
sudo lastb
echo -ne "${neutre} \n"
