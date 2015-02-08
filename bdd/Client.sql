-- phpMyAdmin SQL Dump
-- version 4.2.11
-- http://www.phpmyadmin.net
--
-- Client :  localhost
-- Généré le :  Dim 08 Février 2015 à 12:05
-- Version du serveur :  5.6.21
-- Version de PHP :  5.6.3

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Base de données :  `Client`
--

-- --------------------------------------------------------

--
-- Structure de la table `Client`
--

CREATE TABLE IF NOT EXISTS `Client` (
`id` int(11) NOT NULL COMMENT 'identifiant',
  `ip` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT 'adresse ip du client',
  `hmac` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT 'hmac du client',
  `hostname` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT 'Nom de l''hôte du client',
  `pid` int(11) NOT NULL COMMENT 'pid du processus chargé de communiqué avec ce client'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- --------------------------------------------------------

--
-- Structure de la table `Result`
--

CREATE TABLE IF NOT EXISTS `Result` (
`id` int(11) NOT NULL,
  `idclient` int(11) NOT NULL,
  `idscript` int(11) NOT NULL,
  `result` varchar(1000) COLLATE utf8_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

-- --------------------------------------------------------

--
-- Structure de la table `Script`
--

CREATE TABLE IF NOT EXISTS `Script` (
`id` int(11) NOT NULL COMMENT 'identifiant',
  `nom` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT 'nom du script',
  `description` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT 'description rapide du script',
  `code` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT 'code du script'
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Index pour les tables exportées
--

--
-- Index pour la table `Client`
--
ALTER TABLE `Client`
 ADD PRIMARY KEY (`id`), ADD UNIQUE KEY `hmac` (`hmac`);

--
-- Index pour la table `Result`
--
ALTER TABLE `Result`
 ADD PRIMARY KEY (`id`);

--
-- Index pour la table `Script`
--
ALTER TABLE `Script`
 ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT pour les tables exportées
--

--
-- AUTO_INCREMENT pour la table `Client`
--
ALTER TABLE `Client`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'identifiant';
--
-- AUTO_INCREMENT pour la table `Result`
--
ALTER TABLE `Result`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT pour la table `Script`
--
ALTER TABLE `Script`
MODIFY `id` int(11) NOT NULL AUTO_INCREMENT COMMENT 'identifiant';
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
