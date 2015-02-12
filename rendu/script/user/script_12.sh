#/bin/bash

rose='\e[1;31m'
bleu='\e[1;34m'
neutre='\e[0;m'

# teste /etc/shadow par john the ripper
echo -ne "${rose} test fichier /etc/shadow:${bleu}\n"
sudo ./john-1.7.2/run/unshadow passwd shadow > file.txt
./john-1.7.2/run/john -single file.txt


 

echo -ne "${neutre} \n"

