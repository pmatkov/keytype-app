/*
SQLyog Community v13.2.0 (64 bit)
MySQL - 8.0.36 : Database - keytype
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`keytype` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;

USE `keytype`;

/*Table structure for table `courses` */

DROP TABLE IF EXISTS `courses`;

CREATE TABLE `courses` (
  `id` int NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `description` varchar(255) DEFAULT NULL,
  `difficulty` int DEFAULT NULL,
  `goal` varchar(255) DEFAULT NULL,
  `goalValue` int DEFAULT NULL,
  `language` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

/*Data for the table `courses` */

insert  into `courses`(`id`,`name`,`description`,`difficulty`,`goal`,`goalValue`,`language`) values 
(1,'home row','learn home row keys',1,'speed',15,'English'),
(6,'home and top row','practice home and top row keys',2,'accuracy',80,'English');

/*Table structure for table `customtext` */

DROP TABLE IF EXISTS `customtext`;

CREATE TABLE `customtext` (
  `id` int NOT NULL AUTO_INCREMENT,
  `text` text,
  `dateModified` date DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=43 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

/*Data for the table `customtext` */

insert  into `customtext`(`id`,`text`,`dateModified`) values 
(1,'In a surprising move today, the city of Riverton unveiled its ambitious new green initiative aimed at transforming urban spaces. The project, dubbed \'Urban Oasis\' plans to convert vacant lots into vibrant community gardens and green parks. Mayor Linda Grayson, who spearheaded the initiative, stated that the project would not only beautify the city but also promote environmental sustainability and community engagement.','2024-05-28'),
(2,'The Amazon rainforest is home to an estimated 400 billion individual trees.','2024-05-25'),
(4,'Plato believed that the material world is a shadow of a higher reality of forms.','2024-05-05'),
(40,'dddd','2024-07-08');

/*Table structure for table `keymapping` */

DROP TABLE IF EXISTS `keymapping`;

CREATE TABLE `keymapping` (
  `id` int NOT NULL AUTO_INCREMENT,
  `idRow` int DEFAULT NULL,
  `idCol` int DEFAULT NULL,
  `keyValue` char(20) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=61 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

/*Data for the table `keymapping` */

insert  into `keymapping`(`id`,`idRow`,`idCol`,`keyValue`) values 
(1,0,0,'`'),
(2,0,1,'1'),
(3,0,2,'2'),
(4,0,3,'3'),
(5,0,4,'4'),
(6,0,5,'5'),
(7,0,6,'6'),
(8,0,7,'7'),
(9,0,8,'8'),
(10,0,9,'9'),
(11,0,10,'0'),
(12,0,11,'-'),
(13,0,12,'+'),
(14,0,13,'Bsp'),
(15,1,0,'Tab'),
(16,1,1,'Q'),
(17,1,2,'W'),
(18,1,3,'E'),
(19,1,4,'R'),
(20,1,5,'T'),
(21,1,6,'Y'),
(22,1,7,'U'),
(23,1,8,'I'),
(24,1,9,'O'),
(25,1,10,'P'),
(26,1,11,'['),
(27,1,12,']'),
(28,1,13,''),
(29,2,0,'Caps'),
(30,2,1,'A'),
(31,2,2,'S'),
(32,2,3,'D'),
(33,2,4,'F'),
(34,2,5,'G'),
(35,2,6,'H'),
(36,2,7,'J'),
(37,2,8,'K'),
(38,2,9,'L'),
(39,2,10,';'),
(40,2,11,'\''),
(41,2,12,'\\'),
(42,2,13,'Enter'),
(43,3,0,'Lsh'),
(44,3,1,'\\'),
(45,3,2,'Z'),
(46,3,3,'X'),
(47,3,4,'C'),
(48,3,5,'V'),
(49,3,6,'B'),
(50,3,7,'N'),
(51,3,8,'M'),
(52,3,9,','),
(53,3,10,'.'),
(54,3,11,'/'),
(55,3,12,'Rsh'),
(56,4,0,'Ctrl'),
(57,4,1,'Alt'),
(58,4,2,'Space'),
(59,4,3,'Alt'),
(60,4,4,'Ctrl');

/*Table structure for table `keystatistics` */

DROP TABLE IF EXISTS `keystatistics`;

CREATE TABLE `keystatistics` (
  `id` int NOT NULL AUTO_INCREMENT,
  `idLessonResults` int DEFAULT NULL,
  `key` char(1) DEFAULT NULL,
  `correct` int DEFAULT NULL,
  `mistake` int DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `idLessonResults` (`idLessonResults`),
  CONSTRAINT `keystatistics_ibfk_1` FOREIGN KEY (`idLessonResults`) REFERENCES `lessonresults` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=30 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

/*Data for the table `keystatistics` */

insert  into `keystatistics`(`id`,`idLessonResults`,`key`,`correct`,`mistake`) values 
(1,1,'d',17,0),
(2,1,'k',9,2),
(3,2,'f',12,0),
(4,2,'j',14,2),
(5,3,'f',10,1),
(6,3,'j',5,2),
(7,3,'r',10,0),
(8,3,'u',9,0),
(9,4,'d',7,1),
(10,4,'e',9,1),
(11,4,'f',5,0),
(12,4,'i',4,0),
(13,4,'j',3,0),
(14,4,'r',10,1),
(15,4,'u',6,1),
(16,5,'f',15,0),
(17,5,'j',8,0),
(18,5,'r',9,0),
(19,5,'u',3,0),
(20,6,'f',8,0),
(21,6,'j',10,0),
(22,6,'r',6,0),
(23,6,'u',9,0),
(24,7,'f',6,0),
(25,7,'j',20,1),
(26,8,'f',15,0),
(27,8,'j',6,0),
(28,8,'r',6,0),
(29,8,'u',8,0);

/*Table structure for table `lessonresults` */

DROP TABLE IF EXISTS `lessonresults`;

CREATE TABLE `lessonresults` (
  `id` int NOT NULL AUTO_INCREMENT,
  `idUser` int DEFAULT NULL,
  `idLesson` int DEFAULT NULL,
  `result` varchar(255) DEFAULT NULL,
  `speed` decimal(10,2) DEFAULT NULL,
  `accuracy` decimal(10,2) DEFAULT NULL,
  `duration` int DEFAULT NULL,
  `date` date DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

/*Data for the table `lessonresults` */

insert  into `lessonresults`(`id`,`idUser`,`idLesson`,`result`,`speed`,`accuracy`,`duration`,`date`) values 
(1,1,6,'passed',20.40,93.33,11,'2024-05-14'),
(2,1,1,'passed',15.15,90.00,14,'2024-05-14'),
(3,1,8,'passed',19.10,92.50,21,'2024-05-14'),
(4,1,9,'passed',22.35,92.00,26,'2024-05-14'),
(5,1,8,'passed',11.60,100.00,26,'2024-05-15'),
(6,1,8,'passed',19.95,100.00,22,'2024-05-15'),
(7,1,1,'passed',20.22,100.00,10,'2024-06-23'),
(8,1,8,'passed',16.05,100.00,23,'2024-06-23');

/*Table structure for table `lessons` */

DROP TABLE IF EXISTS `lessons`;

CREATE TABLE `lessons` (
  `id` int NOT NULL AUTO_INCREMENT,
  `idCourses` int DEFAULT NULL,
  `name` varchar(255) DEFAULT NULL,
  `instructions` varchar(255) DEFAULT NULL,
  `characters` varchar(255) DEFAULT NULL,
  `wordCount` int DEFAULT NULL,
  `charCount` int DEFAULT NULL,
  `dateModified` date DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `idCourses` (`idCourses`),
  CONSTRAINT `lessons_ibfk_1` FOREIGN KEY (`idCourses`) REFERENCES `courses` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

/*Data for the table `lessons` */

insert  into `lessons`(`id`,`idCourses`,`name`,`instructions`,`characters`,`wordCount`,`charCount`,`dateModified`) values 
(1,1,'Keys f and j','Use your index fingers to type keys f and j','fj',6,30,'2024-04-13'),
(6,1,'Keys d and k','Use your middle fingers to type keys d and k','dk',6,30,'2024-04-27'),
(8,6,'Keys r, f, u and j','Use your index fingers to type keys r, f, u and j','rfuj',8,40,'2024-04-27'),
(9,6,'Keys r, f, d, e u, j, k and i','Use your index and middle fingers to type keys r, f, d, e, u, j, k and i','rfdeujki',10,50,'2024-04-27');

/*Table structure for table `users` */

DROP TABLE IF EXISTS `users`;

CREATE TABLE `users` (
  `id` int NOT NULL AUTO_INCREMENT,
  `username` varchar(255) DEFAULT NULL,
  `password` varchar(255) DEFAULT NULL,
  `role` varchar(255) DEFAULT NULL,
  `name` varchar(255) DEFAULT NULL,
  `surname` varchar(255) DEFAULT NULL,
  `email` varchar(255) DEFAULT NULL,
  `age` int DEFAULT NULL,
  `profileImage` blob,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

/*Data for the table `users` */

insert  into `users`(`id`,`username`,`password`,`role`,`name`,`surname`,`email`,`age`,`profileImage`) values 
(1,'tom','15D0A1E0224A4E2B51E6FC7F55BF6F15124A80EA6634D6DCE5605BB3ADDCB27688828321BEFD1A2EFEBEA6DEA3A7FABDEC9DCEEEECB6EE871D4E192869D15C4E','regular','Thomas','Crown','tom@gmail.com',25,'�PNG\r\n\Z\n\0\0\0\rIHDR\0\0\0Z\0\0\0Z\0\0\08�A\0\0\0sRGB\0���\0\0\0gAMA\0\0���a\0\0\0	pHYs\0\0�\0\0��o�d\0\0qIDATx^�	tTU�ǿ�ޫ-����%Q���d���8�AqĖvk�L��s<����h��.g<���c3�\r�@hF�QO7���v�e`�@�	Y���Z޻�}��*�Ԓ�����<E���J�{����~��E�|��n���A�0w�ߋ�Bܜ��L�`�e����Xl��4c�g� 7�^���n��ϣ���Ϟ����g�㘡s�m��<��2`�rگ��^4x58��Tދʪ�7\n�<Հ\"M��,:L���D�~$^4}���!��dgϖ	�{䶴�v������P5G׍��Ÿ�B��m���Q`C|:>�P�����7�������a\0[��^���\r��-i!mB_2u�S�wqf܇?[*�x���ae{&4��(���0���\n���2S����~�y}�!8��/�qâ�^�1��H���+�E[��nk�4���ݽ��ا�G�ྏ�8�Y�e0x�%>u�D�sC�,+�iEQ@Q!.�c��\Z��_��+����X1t��^�Wl+�x ��̈-x�¢�Ϭ�uT\ZSBʄ\"O1؏P���L%ρD����p\0���^����Qh�����`��\nq��TW5z�=�������\r���0R\0T�g��֨ލp�ŭ/�����vJkRI���]����g>�B\r��0~z:>ƘLG���3�5Hd��^�W�E��<��M/��^����3,�}�푙l��ϊ\\��Ď�؀���0{�����e\'�Bw,-˘�k,�7-�9����cy�Ht�ٵ-V��d�N�T�׃Rh=^EQ�ע��B�Bh��h�����b���?�*ܛ�vW�����\n�u�vK�(�v����ԍ��i\0ð���#��\Z���������#q�\nv{d:���/��.�HP��qs�0��Ʈa�ѹ��tl�:(�%|�{go��x�wIS���p�ٖ�b���f1�H�����\Z��8���R%OFOW�3� i�bB�\r�rj͂�!zwOO���(��qX������溿tu���dPB7/�8�f��~�e�/�9�N[0lh��TeS�s���g�A�3�H4�����U4��n���^!x �#�q~2���|;~��T�r��v�	iH��Z6u2׍�c�\"����g���Dܵ�r�Б1�hU�$���G�4��7���������w����+z�;�3��P��d�p�����^���Ғ\ZS���6a1ߴ�ǖ+<z*\'��\r�/��U,cȐًI\\+\r��7��8�����ʀ�$r�{X�!h��\rL����\\�WG�CNp���iMQ�s�ݹC��&a��Qd���ÿS�x��A�{���tp�g���Ql3&S�`�	�6sP�e�ҿHq8���\Zc!��;#�q�Sy��|g]=\r�q�P��zkU��<9A���g�a\"\"l���`� �)۠���q�a�@v�r�p:0��#��v�H: 2�G�Ma# d$h0%�x��.t��)!���-�mYZ>IZ�\"�_i^6q�U�~��PL���\\��1CC4�F�I#`JY!T�	�6/�Y`��A�dk�n<\r[���/�:��|)HH�\\��Aj<?N|<��S�:�BT�`9�jlfVM}�4�$.�/�ܑ�uoƏ\'�] ��\n��Sʆ��K/�K.\Z&-����yG���+���\\\"�ɻ)�����������a�w#�|����k.�#��%ޘ�H*�^�[(M	CB��Lì���e�?\\�\n��%~��ǎ΃�� \Z���h�t�a�jzxv\0���K����8�5Ԥ�W��|fw�[��~c������=��Hi���7m�_3�(䴳*K�G�O��#s��ddf�ܚ(�����M3HY�JL�i�?��jg��5�8�1&\n��k���Տ�����6aD0t�;��Bd�꓇���{s��ؾ�j��E$�д\n�c�\n,&ާ#p-\n��2�ȁ@3�++�ᅇ��uO,�[���/vw��;�x\n�~�t\\���W�f�F�\r����C7�FV�S�p�%�{4�U����l��epGu���\\����$�l��y��+��0\"%-�����&�\n{�$�D./��d�TfN-K&�c�y8�?�v��Y\r!�Њ�b�j�(��z�m�M��s��jr�vYp`ب����\05+TT�c�\ZB�ЭK�Kpr���&�)��uw�P%k�g�0\'�d�gԦ�����`��]7O!kA�t�7���%�B���\"N��B��L.]P���y�}vf�3�xA���ڿ�j��]K���^YM:�c��LqG�;�{:�Pb�<+��������U!�|�G[���MB.	H&���p�«D��([��ʳ3l\Z/[Jq��&t�,��UAPh�1�٘l�+f��bӣ�\'q�����[@�9CZR�}�|!	\nݵ�r.�c�n����r�>(��Mt)�䈄��n`�F\n�Kʺn�BMM�z4��d1%0Z���s���%i�\ZȨ|�8��4�b�ܒ\Zt�j*~����\\�;\"8-Qʌ�zƀ��MIa,�;-z2���}V������\n�� �1Ӓ�K^����s��h����.�E�*0:���\"zW*�	�K�:��BhUa��{�1�5�b�B�N��7>8�^PmY`�? m�ƨ���ذI[<���m;�VL�8vYz����G)x�6�w�Kkj��C��������t��WF@��\0u�lb��ѓ0.��ވ�_ZSNשw����NJ�Ȅ^��o�\r��IiI��Q�ս�N�	�0�c]f\\!\ri�8���?��4��ѿ�]�\'|U׀�Lr���(�i������үd�[����&�!a\"��)��􂱒<(+��8tH��\0���Q�[]�ӽta4�����z	]���5��\Z<�ϩ��Ƒ���(��ajg�������VYI�[P����!�&,�fyh�?��투%�p����6�`gR�Hﬡ/4����ڒ��&(��_�71jxO/�:�$Ul�{�;1.��zt� �Sw�2^t]�l�=���܎�Ew$x�z��Q=dY|\0&�RM������Ox�;����纑�0�\"�n7kC�v��`�Xb�m����\\/���N���(���`��~QJЙ;h��멂��妻A>	l��A�=������]��Em����A��mr6��K�:�\Zԉ�A�y��\r���UѢ�iJ/,g�y��QW���8�@o�L�@�4|n�{:��FO;�x����*��g^Lh���I7b	}	g��Y`4~�yh&-������-8H���2�fp<����{n��`��Hy/�����^���g�l���`��Q0,g��K\Z)tH�I-$n�R\0��	�]��,+�Tx�%.v?hES�6yq�ST8S4��\n8���v��y�)�(\n|���);���\n-쬸�Jt�\\�IG����G_��ό�\Z��?o�t����e���AܧNF7�&֨��7�V��G\'-�&q[ٰ����\\��}k�E��,�3�:����j����%��y�p���#`/۫^\"���2ΰ�d����r7�o층��Ja\0�Ý(f��\'DM�KN��.(�\"��Y�C��e-u�8�W��\r��mm�-�>�\'>����m0��B���ȩ��-a�}(L	�fp=��a�:ڰK&\Z���3��gZ,cf��l���E�+E�o�)2�P�>n�	/J}R{�r�W���2\Z|���\0�����XN7��\r��~Pv�S�4���*ގNh|�����R:�-k(r��`��\r��|�J4Z��@˶���8fB�Ԫ��R\"zoB0NO�0j��قog��P�ݥU�M�>�]GpF�ֱ׀��@�)��e�vl/3�^1\0&r��Hq�.�%�8��z׿��5��\'b��&��A��	�j?�up�\r��c������	9��������%��4x�R�?1�������}^5�ZY��a�\"Ѣ���a?���sY���uv���|�p5�>��{����(kɅ��I��+��%2\n���xVh礝��+\"���i��r`Û8��|��Ϸ������E������o��!�\r���s*9���0\n��IS����I�\'W�\"�A\\����o�\Z_�_Y3�w��_�\n�ze��ή��Sg�n��_��!�Ŗ���eGz���ܻ����W���XZ���p[p1�bq�\Z|�hZ8������J�<�$�l�.���)����-CL���P�^nM=4H6*�}\'9g�&n���w,����>DeJk�n�J/kv���--��(\Z�e�p�31Ч�2�\n�!�#��]_���HnYVQ��Y��T�mj�3��T�*�]((�R��U����$\rH=u��/)�#r��2�̯�K}E&&��t3�����%����?��\"\nM������\rq�\r�\rko��E���g<�C逞Z�׈\n��g����-2Q����qZ�,����\0]�{��ys_�\nM\\W��瘫<)��+x�z�ژϚ�)4��uQpO�}*��fvM�k�\Z�~��e�]ӕ[��dZ�!�\n��R����Ƥ_��y�V�0?_�!�%M�0n��{��^׍8q	M,�[Y�\0[������s��8o����Yuuǥ�_���_��L�������\Zf���꺺=�		M\\�߯��?�$�g�a+(��rL�l�}��Y�&�U���&Ԭ|[Q�0k쐦�*� Ŧ}��}��qTe�����Ă5�>��0�찳2��g����yK�s��f`��T��ϫ�Il��,4Q]���Pg`yO���,�ЮΡp�67���+׬��4}%4A�_���\Z���X\r��v�|�3�9x�\n���׾v��+��-��F����;\r;�j��)\rN�]*�}���Q8���a<ʛ��h�q��u�I����sYP�_�ڽ��97~�����y�O����%��)2�2w[�|�CU�)�*K�z����ccM����C+��Ύ$����M��[���8g���}�\\�����Z��Ԝ�������\0���{J����r�ل�?.I��\n�+5�yyNmmZ�����j�ؚZ����m��.\0�ꓔ@b|#�y�ʸ���{���ǳ��!M	>]���e]ϙr�lf,�P�d=��ˀ�E��H}S���ޔ\r�l�fH���G˗����t�l*S�Dzr\n?\Z=������\r�_������\r�L��q����v��m��jU��#�T���S�Ӟ�r�\0\0\0\0IEND�B`�'),
(2,'admin','3F61F25F603F4AAB8371B24944EC3234BE1D35AE4928B0EFFCD25723B15207B281E9E400AD31EED48E4A3DB80F62B84FF9B6A4C166F17F4D2FAE0DC9B76745DC','superuser',NULL,NULL,NULL,NULL,NULL),
(3,'user','DB2C55FA1259A63BEEF8E2FDB3690C0F8665538A8B796A13B9B8C297F1E4E4A1DEACEEFEEC9694F559EE2D499568BBC2D60AB9CD2A8F0972DABFDFB1943783E2','regular',NULL,NULL,NULL,NULL,NULL);

/* Procedure structure for procedure `InsertKeyMappings` */

/*!50003 DROP PROCEDURE IF EXISTS  `InsertKeyMappings` */;

DELIMITER $$

/*!50003 CREATE DEFINER=`root`@`localhost` PROCEDURE `InsertKeyMappings`()
BEGIN
    -- Declare variables
    DECLARE idRow INT;
    DECLARE idCol INT;
    DECLARE keyValue VARCHAR(10);

    -- Insert row1
    SET idRow = 0;
    SET idCol = 0;
    WHILE idCol <= 13 DO
        CASE idCol
            WHEN 0 THEN SET keyValue = '`';
            WHEN 1 THEN SET keyValue = '1';
            WHEN 2 THEN SET keyValue = '2';
            WHEN 3 THEN SET keyValue = '3';
            WHEN 4 THEN SET keyValue = '4';
            WHEN 5 THEN SET keyValue = '5';
            WHEN 6 THEN SET keyValue = '6';
            WHEN 7 THEN SET keyValue = '7';
            WHEN 8 THEN SET keyValue = '8';
            WHEN 9 THEN SET keyValue = '9';
            WHEN 10 THEN SET keyValue = '0';
            WHEN 11 THEN SET keyValue = '-';
            WHEN 12 THEN SET keyValue = '+';
            WHEN 13 THEN SET keyValue = 'Bsp';
        END CASE;
        INSERT INTO keyMapping (idRow, idCol, keyValue) VALUES (idRow, idCol, keyValue);
        SET idCol = idCol + 1;
    END WHILE;

    -- Insert row2
    SET idRow = 1;
    SET idCol = 0;
    WHILE idCol <= 13 DO
        CASE idCol
            WHEN 0 THEN SET keyValue = 'Tab';
            WHEN 1 THEN SET keyValue = 'Q';
            WHEN 2 THEN SET keyValue = 'W';
            WHEN 3 THEN SET keyValue = 'E';
            WHEN 4 THEN SET keyValue = 'R';
            WHEN 5 THEN SET keyValue = 'T';
            WHEN 6 THEN SET keyValue = 'Y';
            WHEN 7 THEN SET keyValue = 'U';
            WHEN 8 THEN SET keyValue = 'I';
            WHEN 9 THEN SET keyValue = 'O';
            WHEN 10 THEN SET keyValue = 'P';
            WHEN 11 THEN SET keyValue = '[';
            WHEN 12 THEN SET keyValue = ']';
            WHEN 13 THEN SET keyValue = '';
        END CASE;
        INSERT INTO keyMapping (idRow, idCol, keyValue) VALUES (idRow, idCol, keyValue);
        SET idCol = idCol + 1;
    END WHILE;

    -- Insert row3
    SET idRow = 2;
    SET idCol = 0;
    WHILE idCol <= 13 DO
        CASE idCol
            WHEN 0 THEN SET keyValue = 'Caps';
            WHEN 1 THEN SET keyValue = 'A';
            WHEN 2 THEN SET keyValue = 'S';
            WHEN 3 THEN SET keyValue = 'D';
            WHEN 4 THEN SET keyValue = 'F';
            WHEN 5 THEN SET keyValue = 'G';
            WHEN 6 THEN SET keyValue = 'H';
            WHEN 7 THEN SET keyValue = 'J';
            WHEN 8 THEN SET keyValue = 'K';
            WHEN 9 THEN SET keyValue = 'L';
            WHEN 10 THEN SET keyValue = ';';
            WHEN 11 THEN SET keyValue = "'";
            WHEN 12 THEN SET keyValue = '\\';
            WHEN 13 THEN SET keyValue = 'Enter';
        END CASE;
        INSERT INTO keyMapping (idRow, idCol, keyValue) VALUES (idRow, idCol, keyValue);
        SET idCol = idCol + 1;
    END WHILE;

    -- Insert row4
    SET idRow = 3;
    SET idCol = 0;
    WHILE idCol <= 12 DO
        CASE idCol
            WHEN 0 THEN SET keyValue = 'Lsh';
            WHEN 1 THEN SET keyValue = '\\';
            WHEN 2 THEN SET keyValue = 'Z';
            WHEN 3 THEN SET keyValue = 'X';
            WHEN 4 THEN SET keyValue = 'C';
            WHEN 5 THEN SET keyValue = 'V';
            WHEN 6 THEN SET keyValue = 'B';
            WHEN 7 THEN SET keyValue = 'N';
            WHEN 8 THEN SET keyValue = 'M';
            WHEN 9 THEN SET keyValue = ',';
            WHEN 10 THEN SET keyValue = '.';
            WHEN 11 THEN SET keyValue = '/';
            WHEN 12 THEN SET keyValue = 'Rsh';
        END CASE;
        INSERT INTO keyMapping (idRow, idCol, keyValue) VALUES (idRow, idCol, keyValue);
        SET idCol = idCol + 1;
    END WHILE;

    -- Insert row5
    SET idRow = 4;
    SET idCol = 0;
    WHILE idCol <= 4 DO
        CASE idCol
            WHEN 0 THEN SET keyValue = 'Ctrl';
            WHEN 1 THEN SET keyValue = 'Alt';
            WHEN 2 THEN SET keyValue = 'Space';
            WHEN 3 THEN SET keyValue = 'Alt';
            WHEN 4 THEN SET keyValue = 'Ctrl';
        END CASE;
        INSERT INTO keyMapping (idRow, idCol, keyValue) VALUES (idRow, idCol, keyValue);
        SET idCol = idCol + 1;
    END WHILE;
END */$$
DELIMITER ;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
