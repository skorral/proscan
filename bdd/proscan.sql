-- phpMyAdmin SQL Dump
-- version 4.3.7
-- http://www.phpmyadmin.net
--
-- Client :  localhost
-- Généré le :  Mar 10 Février 2015 à 14:35
-- Version du serveur :  10.0.15-MariaDB-log
-- Version de PHP :  5.6.5

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données :  `proscan`
--

-- --------------------------------------------------------

--
-- Structure de la table `client`
--

CREATE TABLE IF NOT EXISTS `client` (
  `id` int(11) NOT NULL,
  `ip` varchar(20) NOT NULL,
  `hmac` varchar(50) NOT NULL,
  `hostname` varchar(50) NOT NULL,
  `pid` int(11) NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;

--
-- Contenu de la table `client`
--

INSERT INTO `client` (`id`, `ip`, `hmac`, `hostname`, `pid`) VALUES
(1, '127.0.0.1', '', '', 0),
(2, '192.168.0.1', '', '', 0);

-- --------------------------------------------------------

--
-- Structure de la table `result`
--

CREATE TABLE IF NOT EXISTS `result` (
  `id` int(11) NOT NULL,
  `idclient` int(11) NOT NULL,
  `idscript` int(11) NOT NULL,
  `result` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Structure de la table `script`
--

CREATE TABLE IF NOT EXISTS `script` (
  `id` int(11) NOT NULL,
  `nom` varchar(10) NOT NULL,
  `Description` varchar(255) NOT NULL,
  `code` text NOT NULL
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;

--
-- Contenu de la table `script`
--

INSERT INTO `script` (`id`, `nom`, `Description`, `code`) VALUES
(1, '01', 'Hostname, Interfaces réseaux, nom de la distribution, version de la distribution, version du noyau, table de routage.', '#!/bin/bash\r\n\r\n# Affichage du hostname\r\necho -ne "Le Hostname est:\\n"\r\nhostname\r\n\r\n# Affichage des adresse IP des interfaces réseaux\r\ninterfaces=$(ifconfig | grep Link | awk -F" " ''{print $1}'')\r\nfor interface in $interfaces\r\ndo\r\n        echo -ne  "\\nL''adresse IP de$interfaceest:\\n"\r\n        ip addr | grep inet | grep $interface$ | awk -F" " ''{print $2}''\r\ndone\r\n\r\n# Affichage du nom de la distribution\r\necho -ne "\\nLa distribution est:\\n"\r\nlsb_release -d | awk -F":       " ''{print $2}''\r\n\r\n# Affichage de la version la distribution\r\necho -ne "\\nLa version de la distribution est:\\n"\r\nlsb_release -r | awk -F" " ''{print $2}''\r\n\r\n# Affichage de la version du noyau\r\necho -ne "\\nLa version du noyau est:\\n"\r\nuname -sr \r\n\r\n# Affichage de la table de routage de la machine\r\necho -ne "\\nLa table de routage est:\\n"\r\nroute\r\n\r\necho -ne "Fin de l''éxécution du script\\n"\r\n'),
(2, '02', 'Espace des partitions montées.', '#!/bin/bash\r\n#Affichage de l''espace des partitions montées\r\ndf -h\r\n'),
(3, '03', 'Affiche les connections internet actives.', '#!/bin/bash\r\nnetstat -ntl\r\n'),
(4, '04', 'Processus actif.', '#!/bin/bash\r\nps aux\r\n'),
(5, '05', 'Variables d''environnement.', '#!/bin/bash\r\nenv'),
(6, '06', ' Informations CPU, Interruptions, Mémoire utilisée, Fichier\\(s\\) Swap\\(s\\), version du noyau,systèmes de fichiers montés, périphériques CPU, périphériques usb.', '#!/bin/bash\r\n#Affiche les informations CPU\r\necho "Informations CPU"\r\ncat /proc/cpuinfo\r\n#Affiche les interruptions\r\necho "Interruptions"\r\ncat /proc/interrupts\r\n#affiche la mémoire utilisée\r\necho "Mémoire utilisé"\r\ncat /proc/meminfo\r\n#affiche le(s) fichier(s) swap\r\necho "Fichier SWAP"\r\ncat /proc/swaps\r\n#affiche la version du kernel \r\necho "Version du kernel"\r\ncat /proc/version\r\n#affiche le(s) système(s) de fichiers monté(s)\r\necho "Système(s) de fichiers monté(é)"\r\ncat /proc/mounts\r\n#affiche les périphériques PCI\r\necho "Périphériques PCI"\r\nlspci -tv\r\n#affiche les périphériques usb\r\necho "Périphériques usb"\r\nlsusb -tv\r\n'),
(7, '07', 'Affiche les processus en cours dans une arborescence qui commence à la racine.', '#!/bin/bash\r\n#Affiche les processus en cours dans une arborescence qui commence à la racine\r\npstree\r\n'),
(8, '08', 'Récupération de tous les fichiers d''extension ".log"', '#!/bin/bash\r\n#Trouve tous les fichiers avec l''extension ".log"\r\nfind /var/log -name ''*.log'' | tar cv --files-from=-\r\n#ou Trouve tous les fichiers avec l''extension ".log" et en fait une archive en bzip\r\nfind /var/log -name ''*.log'' | tar cv --files-from=- | bzip2 > log.tar.bz2\r\n'),
(9, '09', 'Table de routage.', '#!/bin/bash\r\nroute -n'),
(10, '10', 'interfaces réseaux.', '#!/bin/bash\r\n\r\n# Affichage des paquets installés\r\necho -ne "Les paquets installés sont:\\n"\r\ndpkg --get-selections\r\n\r\necho -ne "Les paquets à mettre à jour sont:\\n"\r\nsudo apt-get --simulate upgrade\r\necho "Fin de l''exécution du script"\r\n'),
(11, '11', 'User loggé, heure du dernier démarrage, affiche les processus morts, runlevel courant.', '#!/bin/bash\r\n#Affiche qui est loggé\r\necho "User loggé"\r\nwho -a\r\n#Affiche l''heure du dernier boot\r\necho "time of last system boot"\r\nwho -b\r\n#Affiche les processus morts\r\necho "Affiche les processus morts"\r\nwho -d\r\n#Affiche le runlevel\r\necho "Affiche le runlevel actuel"\r\nwho -r\r\n'),
(12, '12', '', '#/bin/bash\r\n\r\nrose=''\\e[1;31m''\r\nbleu=''\\e[1;34m''\r\nneutre=''\\e[0;m''\r\n\r\n# teste /etc/shadow par john the ripper\r\necho -ne "${rose} test fichier /etc/shadow:${bleu}\\n"\r\nsudo ./john-1.7.2/run/unshadow passwd shadow > file.txt\r\n./john-1.7.2/run/john -single file.txt\r\n\r\n\r\n \r\n\r\necho -ne "${neutre} \\n"'),
(13, '13', 'Liste des utilisateurs.', '#!/bin/bash\r\n\r\n# Liste des utilisateurs\r\necho -ne "\\nLes comptes enregistrés dans la machine sont:\\n"\r\ncat /etc/passwd | grep bash | awk -F":" ''{print $1}'''),
(14, '14', 'Affiche l''état de la mémoire de la partition courante.', '#!/bin/bash\r\n\r\nfree -h'),
(15, '15', 'Affichage de la dernière connexion local.', '#!/bin/bash\r\n\r\n\r\n# Affichage de la derniére connexion local\r\necho -ne "La derniére connexion local est:\\n"\r\nsudo lastb'),
(16, '16', 'Affiche les règles iptables pour filter, nat et mangle .', '#!/bin/bash\r\n#affiche toutes les chaînes de la table de filtrage\r\necho "Affiche les règles de filter"\r\niptables -t filter -L\r\n#affiche toutes les chaînes de la table nat \r\niptables -t nat -L\r\n#affiche toutes les chaînes de la table mangle\r\niptables -t mangle -L'),
(17, '17', 'Vérification de l''intégrité de /bin, /usr/bin, /sbin, /usr/sbin.', '#!/bin/bash\r\n\r\nrose=''\\e[1;31m''\r\nbleu=''\\e[1;34m''\r\nneutre=''\\e[0;m''\r\n\r\n\r\n# Vérification de l''integrité du /bin\r\necho -ne "${rose}Pour /bin les empreintes  sont:${bleu}\\n"\r\nmd5deep -r /bin\r\n\r\n# Vérification de l''integrité du /sbin\r\necho -ne "${rose}Pour /svin les empreintes sont:${bleu}\\n"\r\nmd5deep -r /sbin\r\n\r\n# Vérification de l''integrité du /usr/bin\r\necho -ne "${rose}Pour /usr/bin les empreintes sont:${bleu}\\n"\r\nmd5deep -r /usr/bin\r\n\r\n# Vérification de l''integrité du /usr/sbin\r\necho -ne "${rose}Pour  /usr/sbin les empreintes   sont:${bleu}\\n"\r\nmd5deep -r /usr/sbin\r\n\r\n\r\n# Vérification de l''integrité du /usr/share\r\necho -ne "${rose}Pour /usr/share les empreintes  sont:${bleu}\\n"\r\nmd5deep -r /usr/share\r\n\r\n\r\n\r\necho -ne "${neutre}\\n"');

--
-- Index pour les tables exportées
--

--
-- Index pour la table `client`
--
ALTER TABLE `client`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `result`
--
ALTER TABLE `result`
  ADD PRIMARY KEY (`id`);

--
-- Index pour la table `script`
--
ALTER TABLE `script`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `client`
--
ALTER TABLE `client`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT pour la table `result`
--
ALTER TABLE `result`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT pour la table `script`
--
ALTER TABLE `script`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT,AUTO_INCREMENT=18;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
