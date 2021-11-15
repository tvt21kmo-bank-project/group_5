CREATE DATABASE  IF NOT EXISTS `bankdb` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `bankdb`;
-- MySQL dump 10.13  Distrib 8.0.27, for Linux (x86_64)
--
-- Host: 127.0.0.1    Database: bankdb
-- ------------------------------------------------------
-- Server version	8.0.27-0ubuntu0.20.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `asiakas`
--

DROP TABLE IF EXISTS `asiakas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakas` (
  `idasiakas` int NOT NULL AUTO_INCREMENT,
  `etunimi_asiakas` varchar(45) NOT NULL,
  `sukunimi_asiakas` varchar(45) NOT NULL,
  `osoite_asiakas` varchar(45) NOT NULL,
  `puhelin_asiakas` int NOT NULL,
  PRIMARY KEY (`idasiakas`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `asiakas_tili`
--

DROP TABLE IF EXISTS `asiakas_tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `asiakas_tili` (
  `asiakas_idasiakas` int NOT NULL,
  `tili_idtili` int NOT NULL,
  PRIMARY KEY (`asiakas_idasiakas`,`tili_idtili`),
  KEY `fk_asiakas_has_tili_tili1_idx` (`tili_idtili`),
  KEY `fk_asiakas_has_tili_asiakas1_idx` (`asiakas_idasiakas`),
  CONSTRAINT `fk_asiakas_has_tili_asiakas1` FOREIGN KEY (`asiakas_idasiakas`) REFERENCES `asiakas` (`idasiakas`),
  CONSTRAINT `fk_asiakas_has_tili_tili1` FOREIGN KEY (`tili_idtili`) REFERENCES `tili` (`idtili`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `kortti`
--

DROP TABLE IF EXISTS `kortti`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `kortti` (
  `idkortti` int NOT NULL,
  `pinkoodi` varchar(255) NOT NULL,
  `tili_idtili` int NOT NULL,
  `asiakas_idasiakas` int NOT NULL,
  PRIMARY KEY (`idkortti`,`tili_idtili`,`asiakas_idasiakas`),
  KEY `fk_Kortti_Tili1_idx` (`tili_idtili`),
  KEY `fk_kortti_asiakas1_idx` (`asiakas_idasiakas`),
  CONSTRAINT `fk_kortti_asiakas1` FOREIGN KEY (`asiakas_idasiakas`) REFERENCES `asiakas` (`idasiakas`),
  CONSTRAINT `fk_Kortti_Tili1` FOREIGN KEY (`tili_idtili`) REFERENCES `tili` (`idtili`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tili`
--

DROP TABLE IF EXISTS `tili`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tili` (
  `idtili` int NOT NULL,
  `saldo` double DEFAULT NULL,
  `idomistaja` int NOT NULL,
  `tilityyppi` set('credit','debit') NOT NULL,
  `luottoraja` double DEFAULT NULL,
  PRIMARY KEY (`idtili`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Table structure for table `tilitapahtumat`
--

DROP TABLE IF EXISTS `tilitapahtumat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tilitapahtumat` (
  `idtilitapahtumat` int NOT NULL AUTO_INCREMENT,
  `korttinumero` varchar(45) NOT NULL,
  `date` timestamp NOT NULL,
  `tapahtuma` varchar(45) NOT NULL,
  `summa` double NOT NULL,
  `tili_idTili` int NOT NULL,
  PRIMARY KEY (`idtilitapahtumat`,`tili_idTili`),
  KEY `fk_Tilitapahtumat_Tili1_idx` (`tili_idTili`),
  CONSTRAINT `fk_Tilitapahtumat_Tili1` FOREIGN KEY (`tili_idTili`) REFERENCES `tili` (`idtili`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-11-15 18:11:49
