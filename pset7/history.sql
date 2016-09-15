--
-- Database: `pset7`
--

CREATE DATABASE IF NOT EXISTS `pset7`;
USE `pset7`;

-- --------------------------------------------------------

--
-- Table structure for table `history`
--

CREATE TABLE IF NOT EXISTS `history` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `is_sold` BOOLEAN NOT NULL,
  `symbol` varchar(8) NOT NULL,
  `shares` int(10) unsigned NOT NULL,
  `price` float(10) unsigned NOT NULL,
  `order_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB;

INSERT INTO `history` (user_id, is_sold, symbol, shares, price) VALUES(9, TRUE, 'fb', 5, 127.77);