--
-- Database: `pset7`
--

CREATE DATABASE IF NOT EXISTS `pset7`;
USE `pset7`;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE IF NOT EXISTS `portfolios` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` int(10) unsigned NOT NULL,
  `symbol` varchar(8) NOT NULL,
  `shares` int(10) unsigned NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY (`user_id`, `symbol`)
) ENGINE=InnoDB;

