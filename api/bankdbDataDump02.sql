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
  `puhelin_asiakas` varchar(45) NOT NULL,
  PRIMARY KEY (`idasiakas`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `asiakas`
--

LOCK TABLES `asiakas` WRITE;
/*!40000 ALTER TABLE `asiakas` DISABLE KEYS */;
INSERT INTO `asiakas` VALUES (1,'Liisa','Pakastepizza','Vatsahaavankatu 12','+3588511935'),(2,'Kalle','Nallela','Migreenitie 1','+3588511408'),(3,'Tiina','Meriviima','Legionellatie 15','+35885401582'),(4,'Vihtori','Pehtoori','Borrelioosikuja 4','+35885401403');
/*!40000 ALTER TABLE `asiakas` ENABLE KEYS */;
UNLOCK TABLES;

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
-- Dumping data for table `asiakas_tili`
--

LOCK TABLES `asiakas_tili` WRITE;
/*!40000 ALTER TABLE `asiakas_tili` DISABLE KEYS */;
/*!40000 ALTER TABLE `asiakas_tili` ENABLE KEYS */;
UNLOCK TABLES;

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
  CONSTRAINT `fk_Kortti_Tili1` FOREIGN KEY (`tili_idtili`) REFERENCES `tili` (`idtili`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `kortti`
--

LOCK TABLES `kortti` WRITE;
/*!40000 ALTER TABLE `kortti` DISABLE KEYS */;
INSERT INTO `kortti` VALUES (1,'$2a$10$tK6Mj1Z7o5EdvWv/1JSB..9czE3Sr/4niFcfRWQ07R2oa51CGcpjK',1,1),(2,'$2a$10$wcY0pSi04e48AcSkJ6uUx.JLoMvnNjW5JX8kL/AflEGnI2u6DUFym',2,2),(3,'$2a$10$H0zOsigCLUrU/l4qL1ic8urX4b2iGEG46gW0Lr2LCRtZAGL0GDZV6',3,3),(4,'$2a$10$NcwdE.BJAMCNmuR0HPhcaOr/y8PL9diWU0ZYGPkMgPUKQixI3EIOa',4,4),(5,'$2a$10$Fk6LmJNkzKbacbwQPfzxGeUkpi/tQlc6etJi1WSMXXxwZuA97hvMC',5,4);
/*!40000 ALTER TABLE `kortti` ENABLE KEYS */;
UNLOCK TABLES;

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
-- Dumping data for table `tili`
--

LOCK TABLES `tili` WRITE;
/*!40000 ALTER TABLE `tili` DISABLE KEYS */;
INSERT INTO `tili` VALUES (1,1200,1,'debit',NULL),(2,NULL,2,'credit',900),(3,2500,3,'credit,debit',3000),(4,3160,4,'debit',NULL),(5,NULL,4,'credit',4000);
/*!40000 ALTER TABLE `tili` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `tilitapahtumat`
--

DROP TABLE IF EXISTS `tilitapahtumat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `tilitapahtumat` (
  `idtilitapahtumat` int NOT NULL AUTO_INCREMENT,
  `date` timestamp NOT NULL,
  `tapahtuma` varchar(45) NOT NULL,
  `summa` double NOT NULL,
  `tili_idTili` int NOT NULL,
  `idkortti` int NOT NULL,
  PRIMARY KEY (`idtilitapahtumat`,`tili_idTili`),
  KEY `fk_Tilitapahtumat_Tili1_idx` (`tili_idTili`),
  CONSTRAINT `fk_Tilitapahtumat_Tili1` FOREIGN KEY (`tili_idTili`) REFERENCES `tili` (`idtili`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `tilitapahtumat`
--

LOCK TABLES `tilitapahtumat` WRITE;
/*!40000 ALTER TABLE `tilitapahtumat` DISABLE KEYS */;
INSERT INTO `tilitapahtumat` VALUES (1,'2021-11-20 09:25:05','Nosto',20,1,1),(2,'2021-11-20 09:25:05','Nosto',40,5,5),(3,'2021-11-24 16:50:47','credit_nosto',20,2,2),(4,'2021-11-24 16:51:57','credit_nosto',20,2,2),(5,'2021-11-24 17:06:09','debit_nosto',40,4,4);
/*!40000 ALTER TABLE `tilitapahtumat` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'bankdb'
--
/*!50003 DROP PROCEDURE IF EXISTS `transfer_credit` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`gerhard`@`localhost` PROCEDURE `transfer_credit`(IN tilitunnus INT,IN korttitunnus INT, IN maara DOUBLE)
BEGIN
DECLARE tilitesti INT DEFAULT 0;
START TRANSACTION;
UPDATE tili SET luottoraja = luottoraja - maara WHERE idtili = tilitunnus AND luottoraja > maara;
SET tilitesti = row_count();
 
IF(tilitesti > 0) THEN
	COMMIT;
    INSERT INTO tilitapahtumat(date,tapahtuma,summa,tili_idTili,idkortti)
    VALUES(NOW(),'credit_nosto',maara,tilitunnus,korttitunnus);
    ELSE 
    ROLLBACK;
END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `transfer_debit` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`gerhard`@`localhost` PROCEDURE `transfer_debit`(IN tilitunnus INT,IN korttitunnus INT, IN maara DOUBLE)
BEGIN
DECLARE tilitesti INT DEFAULT 0;
START TRANSACTION;
UPDATE tili SET saldo = saldo - maara WHERE idtili = tilitunnus AND saldo > maara;
SET tilitesti = row_count();
 
IF(tilitesti > 0) THEN
	COMMIT;
    INSERT INTO tilitapahtumat(date,tapahtuma,summa,tili_idTili,idkortti)
    VALUES(NOW(),'debit_nosto',maara,tilitunnus,korttitunnus);
    ELSE 
    ROLLBACK;
END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-11-24 19:21:57
