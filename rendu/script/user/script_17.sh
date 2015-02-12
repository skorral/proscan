#!/bin/bash

rose='\e[1;31m'
bleu='\e[1;34m'
neutre='\e[0;m'


# Vérification de l'integrité du /bin
echo -ne "${rose}Pour /bin les empreintes  sont:${bleu}\n"
md5deep -r /bin

# Vérification de l'integrité du /sbin
echo -ne "${rose}Pour /svin les empreintes sont:${bleu}\n"
md5deep -r /sbin

# Vérification de l'integrité du /usr/bin
echo -ne "${rose}Pour /usr/bin les empreintes sont:${bleu}\n"
md5deep -r /usr/bin

# Vérification de l'integrité du /usr/sbin
echo -ne "${rose}Pour  /usr/sbin les empreintes   sont:${bleu}\n"
md5deep -r /usr/sbin


# Vérification de l'integrité du /usr/share
echo -ne "${rose}Pour /usr/share les empreintes  sont:${bleu}\n"
md5deep -r /usr/share



echo -ne "${neutre}\n"
