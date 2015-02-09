
#!/bin/bash

# Affichage des paquets installés
echo -ne "Les paquets installés sont:\n"
dpkg --get-selections

echo -ne "Les paquets à mettre à jour sont:\n"
sudo apt-get --simulate upgrade
echo "Fin de l'exécution du script"
