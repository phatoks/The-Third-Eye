-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Apr 12, 2019 at 03:39 AM
-- Server version: 10.3.13-MariaDB
-- PHP Version: 7.3.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `id9192689_smarthome`
--

-- --------------------------------------------------------

--
-- Table structure for table `sensor_data`
--

CREATE TABLE `sensor_data` (
  `recordID` int(15) NOT NULL,
  `light` varchar(20) DEFAULT NULL,
  `flame` varchar(20) DEFAULT NULL,
  `alarm` varchar(20) DEFAULT NULL,
  `humidity` int(4) DEFAULT NULL,
  `temperature` int(4) DEFAULT NULL,
  `motion` varchar(20) DEFAULT NULL,
  `updateDateTime` datetime DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `sensor_data`
--

INSERT INTO `sensor_data` (`recordID`, `light`, `flame`, `alarm`, `humidity`, `temperature`, `motion`, `updateDateTime`) VALUES
(1313, 'OFF', 'OFF', 'OFF', 0, 0, 'NO', '2019-04-06 19:26:59');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `sensor_data`
--
ALTER TABLE `sensor_data`
  ADD PRIMARY KEY (`recordID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `sensor_data`
--
ALTER TABLE `sensor_data`
  MODIFY `recordID` int(15) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1709;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
