-- MySQL dump 10.13  Distrib 5.6.34, for Linux (x86_64)
--
-- Host: localhost    Database: alpes_outillage_reparation
-- ------------------------------------------------------
-- Server version	5.6.34-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Client`
--

DROP TABLE IF EXISTS `Client`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Client` (
  `idClient` int(11) NOT NULL DEFAULT '0',
  `nomClient` varchar(45) DEFAULT NULL,
  `prenomClient` varchar(45) DEFAULT NULL,
  `telephoneClient` varchar(45) DEFAULT NULL,
  `emailClient` varchar(45) DEFAULT NULL,
  `adresseClient` varchar(45) DEFAULT NULL,
  `cpClient` varchar(6) DEFAULT NULL,
  `villeClient` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idClient`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Client`
--

LOCK TABLES `Client` WRITE;
/*!40000 ALTER TABLE `Client` DISABLE KEYS */;
INSERT INTO `Client` VALUES (1,'Lesieur','Robin','06 58 15 65 70','r.lesieur13@gmail.com','15 rue Aubanel','05000','Gap'),(2,'Thomassin','Gilles','04 92 53 41 92','gthomassingap@gmail.com','le Collet','05110','Lardier et Valença'),(3,'Duval','Christophe','06 56 25 41 12','gthom@btsinfogap.org','11 bis Place aux herbes','05000','Gap'),(4,'Feraud','Gérard','04 24 36 25 96','gferaud@gmail.com','15 rue Carnot','05000','Gap');
/*!40000 ALTER TABLE `Client` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Commande`
--

DROP TABLE IF EXISTS `Commande`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Commande` (
  `idCommande` int(11) NOT NULL DEFAULT '0',
  `dateCommande` date DEFAULT NULL,
  `dateLivraisonPrevue` date DEFAULT NULL,
  `dateReception` date DEFAULT NULL,
  `idFournisseur` int(11) NOT NULL,
  PRIMARY KEY (`idCommande`),
  KEY `idFournisseur` (`idFournisseur`),
  CONSTRAINT `Commande_ibfk_1` FOREIGN KEY (`idFournisseur`) REFERENCES `Fournisseur` (`idFournisseur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Commande`
--

LOCK TABLES `Commande` WRITE;
/*!40000 ALTER TABLE `Commande` DISABLE KEYS */;
/*!40000 ALTER TABLE `Commande` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Devis_Reparation`
--

DROP TABLE IF EXISTS `Devis_Reparation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Devis_Reparation` (
  `idDevis` int(11) NOT NULL DEFAULT '0',
  `etatDevis` varchar(30) not NULL,
  PRIMARY KEY (`idDevis`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Devis_Reparation`
--

LOCK TABLES `Devis_Reparation` WRITE;
/*!40000 ALTER TABLE `Devis_Reparation` DISABLE KEYS */;
INSERT INTO `Devis_Reparation` VALUES (1,'à réaliser'),(2,'à communiquer'),(3,'communiqué'),(4,'accepté'),(5,'refusé');
/*!40000 ALTER TABLE `Devis_Reparation` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Etat_Reparation`
--

DROP TABLE IF EXISTS `Etat_Reparation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Etat_Reparation` (
  `idEtat` int(11) NOT NULL DEFAULT '0',
  `libelleEtat` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idEtat`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Etat_Reparation`
--

LOCK TABLES `Etat_Reparation` WRITE;
/*!40000 ALTER TABLE `Etat_Reparation` DISABLE KEYS */;
INSERT INTO `Etat_Reparation` VALUES (1,'Plannifier'),(2,'Diagnostiquer'),(4,'Commander Pieces'),(5,'Commencer reparation'),(6,'Finir reparation'),(7,'Ranger en magasin'),(8,'Prevenir client'),(10,'Donner au Client'),(12,'Historiser'),(14,'Supprimer');
/*!40000 ALTER TABLE `Etat_Reparation` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Fournisseur`
--

DROP TABLE IF EXISTS `Fournisseur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Fournisseur` (
  `idFournisseur` int(11) NOT NULL DEFAULT '0',
  `nomFournisseur` varchar(45) DEFAULT NULL,
  PRIMARY KEY (`idFournisseur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Fournisseur`
--

LOCK TABLES `Fournisseur` WRITE;
/*!40000 ALTER TABLE `Fournisseur` DISABLE KEYS */;
/*!40000 ALTER TABLE `Fournisseur` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Marque`
--

DROP TABLE IF EXISTS `Marque`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Marque` (
  `idMarque` int(11) NOT NULL,
  `libelleMarque` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`idMarque`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Marque`
--

LOCK TABLES `Marque` WRITE;
/*!40000 ALTER TABLE `Marque` DISABLE KEYS */;
INSERT INTO `Marque` VALUES (1,'Honda'),(2,'Stihl'),(3,'Husqvarna'),(4,'silex'),(5,'Gardena');
/*!40000 ALTER TABLE `Marque` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Modele`
--

DROP TABLE IF EXISTS `Modele`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Modele` (
  `idModel` int(11) NOT NULL,
  `codeModel` varchar(50) NOT NULL,
  `marque` int(11) DEFAULT NULL,
  `nature` varchar(75) DEFAULT NULL,
  `typeMoteur` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`idModel`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Modele`
--

LOCK TABLES `Modele` WRITE;
/*!40000 ALTER TABLE `Modele` DISABLE KEYS */;
INSERT INTO `Modele` VALUES (1,'550XP 45SN',3,'Tronconneuse',0),(2,'550XP 50SN',3,'Tronconneuse',0),(3,'MS 170',2,'Tronconneuse',0),(4,'MS 180',2,'Tronconneuse',0),(5,'HR 21',1,'Tondeuse',0),(6,'BL 510 SHQ',1,'Tondeuse',0),(7,'Inverter EU 20i',1,'Groupe Electrogne',1),(8,'EasyCut 48 PLUS',5,'Taille Haie',5);
/*!40000 ALTER TABLE `Modele` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Produit`
--

DROP TABLE IF EXISTS `Produit`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Produit` (
  `refProduit` varchar(45) NOT NULL DEFAULT '',
  `libelleProduit` varchar(45) DEFAULT NULL,
  `stocke` tinyint(1) DEFAULT NULL,
  `idCommande` int(11) NOT NULL,
  `idProduit` int(11) NOT NULL,
  PRIMARY KEY (`refProduit`),
  KEY `idCommande` (`idCommande`,`idProduit`),
  CONSTRAINT `Produit_ibfk_1` FOREIGN KEY (`idCommande`, `idProduit`) REFERENCES `ProduitCommande` (`idCommande`, `idProduit`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Produit`
--

LOCK TABLES `Produit` WRITE;
/*!40000 ALTER TABLE `Produit` DISABLE KEYS */;
/*!40000 ALTER TABLE `Produit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ProduitCommande`
--

DROP TABLE IF EXISTS `ProduitCommande`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `ProduitCommande` (
  `idProduit` int(11) NOT NULL DEFAULT '0',
  `qteProduit` int(11) DEFAULT NULL,
  `idCommande` int(11) NOT NULL,
  PRIMARY KEY (`idCommande`,`idProduit`),
  CONSTRAINT `ProduitCommande_ibfk_1` FOREIGN KEY (`idCommande`) REFERENCES `Commande` (`idCommande`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ProduitCommande`
--

LOCK TABLES `ProduitCommande` WRITE;
/*!40000 ALTER TABLE `ProduitCommande` DISABLE KEYS */;
/*!40000 ALTER TABLE `ProduitCommande` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Reparation`
--

DROP TABLE IF EXISTS `Reparation`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Reparation` (
  `idReparation` int(11) NOT NULL DEFAULT '0',
  `panneReparation` varchar(255) DEFAULT NULL,
  `outilRef` int(11) NOT NULL,
  `dateArrivee` date DEFAULT NULL,
  `tempsPasse` int(11) DEFAULT NULL,
  `dateFinalisation` date DEFAULT NULL,
  `idClient` int(11) NOT NULL,
  `idDevis` int(11) DEFAULT NULL,
  `idEtat` int(11) NOT NULL,
  `idUtilisateur` int(11) DEFAULT NULL,
  PRIMARY KEY (`idReparation`),
  KEY `idClient` (`idClient`),
  KEY `idDevis` (`idDevis`),
  KEY `idEtat` (`idEtat`),
  KEY `idUtilisateur` (`idUtilisateur`),
  CONSTRAINT `Reparation_ibfk_1` FOREIGN KEY (`idClient`) REFERENCES `Client` (`idClient`),
  CONSTRAINT `Reparation_ibfk_2` FOREIGN KEY (`idDevis`) REFERENCES `Devis_Reparation` (`idDevis`),
  CONSTRAINT `Reparation_ibfk_3` FOREIGN KEY (`idEtat`) REFERENCES `Etat_Reparation` (`idEtat`),
  CONSTRAINT `Reparation_ibfk_5` FOREIGN KEY (`idUtilisateur`) REFERENCES `Utilisateur` (`idUtilisateur`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Reparation`
--

LOCK TABLES `Reparation` WRITE;
/*!40000 ALTER TABLE `Reparation` DISABLE KEYS */;
INSERT INTO `Reparation` VALUES (101,'&&&&&&&&',5,'2017-02-03',NULL,NULL,2,2,2,1),(102,'chane trop srre&&&&&&&&',2,'2017-02-04',NULL,NULL,1,2,2,1),(103,'affuter la lâme&&&&&&&&',5,'2017-02-05',NULL,NULL,1,2,2,1),(104,'&&&&&&&&',0,'2017-02-05',NULL,NULL,4,2,2,1),(105,'&&&&&&&&',7,'2017-02-06',NULL,NULL,3,NULL,1,NULL),(106,'fil abimé&&&&&&&&',8,'2017-02-06',NULL,NULL,4,NULL,1,NULL);
/*!40000 ALTER TABLE `Reparation` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Utilisateur`
--

DROP TABLE IF EXISTS `Utilisateur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Utilisateur` (
  `idUtilisateur` int(11) NOT NULL DEFAULT '0',
  `nomUtilisateur` varchar(45) DEFAULT NULL,
  `typeUtilisateur` int(11) NOT NULL,
  `supprime` tinyint(1) DEFAULT '0',
  PRIMARY KEY (`idUtilisateur`),
  KEY `fk_typeUtil` (`typeUtilisateur`),
  CONSTRAINT `fk_typeUtil` FOREIGN KEY (`typeUtilisateur`) REFERENCES `typeUtilisateur` (`idType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Utilisateur`
--

LOCK TABLES `Utilisateur` WRITE;
/*!40000 ALTER TABLE `Utilisateur` DISABLE KEYS */;
INSERT INTO `Utilisateur` VALUES (1,'JDUPOND',1,0),(2,'GDUVAL',1,0),(3,'Yolande',5,0),(4,'Chef',6,0);
/*!40000 ALTER TABLE `Utilisateur` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `typeUtilisateur`
--

DROP TABLE IF EXISTS `typeUtilisateur`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `typeUtilisateur` (
  `idType` int(11) NOT NULL,
  `libelleType` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`idType`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `typeUtilisateur`
--

LOCK TABLES `typeUtilisateur` WRITE;
/*!40000 ALTER TABLE `typeUtilisateur` DISABLE KEYS */;
INSERT INTO `typeUtilisateur` VALUES (1,'Apprentis'),(2,'Technicien thermique'),(3,'Technicien electrique'),(4,'Technicien polyvalent'),(5,'Organisateur/Gestion'),(6,'Responsable');
/*!40000 ALTER TABLE `typeUtilisateur` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-02-06  7:55:48
