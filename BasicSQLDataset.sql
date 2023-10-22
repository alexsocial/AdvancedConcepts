/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`classicmodels` /*!40100 DEFAULT CHARACTER SET latin1 */;

USE `classicmodels`;

/*Table structure for table `customer` */

DROP TABLE IF EXISTS `customer`;

CREATE TABLE `customer` (
	`cust_email` varchar(50) NOT NULL,
    `cust_fname` varchar(50) NOT NULL,
    `cust_lname` varchar(50) NOT NULL,
    `cust_uname` varchar(35) UNIQUE NOT NULL,
    `cust_address` varchar(200) NOT NULL,
    `cust_password` varchar(35) NOT NULL,
    PRIMARY KEY(`cust_email`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*Table structure for table `payment` */

DROP TABLE IF EXISTS `payment`;

CREATE TABLE `payment` (
	`pay_id` int(15) NOT NULL AUTO_INCREMENT,
    `pay_product` varchar(75) NOT NULL,
    `pay_amnt` double(12,2) NOT NULL,
    `pay_buyer` varchar(50) NOT NULL,
    PRIMARY KEY(`pay_id`),
    KEY `pay_buyer` (`pay_buyer`),
    CONSTRAINT `pay_ibfk_1` FOREIGN KEY (`pay_buyer`) REFERENCES `customer` (`cust_email`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*Table structure for table `product` */

DROP TABLE IF EXISTS `product`;

CREATE TABLE `product` (
	`product_id` int(12) NOT NULL AUTO_INCREMENT,
    `product_type` varchar(50) NOT NULL,
    `product_photo` longblob DEFAULT NULL, /*For now, at least until I can throw in PHP*/
    `product_price` double (24,2) NOT NULL,
    `product_name` varchar(75) NOT NULL,
    PRIMARY KEY (`product_id`),
    KEY `product_type` (`product_type`),
    CONSTRAINT `prod_ibfk_1` FOREIGN KEY (`product_type`) REFERENCES `category` (`category_name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*Table structure for table `category` */

DROP TABLE IF EXISTS `category`;

CREATE TABLE `category` (
	`category_id` int(8) NOT NULL AUTO_INCREMENT,
    `category_name` varchar(50) UNIQUE NOT NULL,
    PRIMARY KEY (`category_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*Table structure for table `cart_item` */

DROP TABLE IF EXISTS `cart_item`;

CREATE TABLE `cart_item` (
	`item_id` int(25) NOT NULL,
    `item_customer` varchar(50) NOT NULL,
    `item_price` double(24,2) NOT NULL DEFAULT 0.0,
    `item_discount` double(24,2) NOT NULL DEFAULT 0.0,
    `item_quantity` int(5) NOT NULL DEFAULT 0,
    PRIMARY KEY (`item_id`),
    KEY `item_customer` (`item_customer`),
    KEY `item_id` (`item_id`),
    KEY `item_price` (`item_price`),
    CONSTRAINT `ibfk_cart_item_1` FOREIGN KEY (`item_customer`) REFERENCES customer (`cust_email`),
    CONSTRAINT `ibfk_cart_item_2` FOREIGN KEY (`item_id`) REFERENCES product (`product_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*Table structure for table `cart` */

DROP TABLE IF EXISTS `cart`;

CREATE TABLE `cart` (
    `cart_id` int(35) NOT NULL AUTO_INCREMENT,
    `cart_price` double(24,2) NOT NULL DEFAULT 0,
    PRIMARY KEY(`cart_id`) /*Use PHP to create a full system*/
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


/* 
Table insertions
In order of tables above
*/
insert  into `customer` (`cust_email`, `cust_fname`, `cust_lname`, `cust_uname`, `cust_address`, `cust_password`) values

("google@gmail.com", "John", "Google", "Googol", "1600 Amphitheatre Parkway, Mountain View, California", "qwertyasdf4321"),

("power@gmail.com", "John", "Power", "Devilborn", "1600 Amphitheatre Parkway, Mountain View, California", "i_am_invincible"),

("achaban2019@fau.edu", "Alex", "Chaban", "anitsocial", "123 Movie Street", "1337_4Dm!N_puRp0Ses");

insert  into `product` (`product_name`, `product_photo`, `product_type`, `product_price`) values

("Majora's Mask", NULL, "Cosmetics", 5000.00),

("The Team Captain", NULL, "Cosmetics", 15750.00),

("Rathalos Mail", NULL, "Armor", 200.00),

("Leather Cap", NULL, "Armor", 5.50),

("Dawnbreaker", NULL, "Weapons", 7777.77),

("Tanooki Leaf", NULL, "Consumables", 3.10);

insert  into `category` (`category_name`) values

("Cosmetics"),

("Weapons"),

("Consumables"),

("Armor"),

("Miscallenous");


/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;