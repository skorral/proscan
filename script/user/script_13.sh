#!/bin/bash

# Liste des utilisateurs
echo -ne "\nLes comptes enregistrés dans la machine sont:\n"
cat /etc/passwd | grep bash | awk -F":" '{print $1}'
