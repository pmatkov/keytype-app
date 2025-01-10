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
(1,'tom','15D0A1E0224A4E2B51E6FC7F55BF6F15124A80EA6634D6DCE5605BB3ADDCB27688828321BEFD1A2EFEBEA6DEA3A7FABDEC9DCEEEECB6EE871D4E192869D15C4E','regular','Thomas','Crown','tom@gmail.com',25,'âPNG\r\n\Z\n\0\0\0\rIHDR\0\0\0Z\0\0\0Z\0\0\08®A\0\0\0sRGB\0ÆŒÈ\0\0\0gAMA\0\0±è¸a\0\0\0	pHYs\0\0√\0\0√«o®d\0\0qIDATx^Ìù	tTUö«ø˚ﬁ´-©¨ÑÑ%QÅêÑd¥çÉ8ÙAqƒñvkœL´£s<””⁄Œh∑›.g<”Ì“c3Ç\rì@hFùQO7‚ Èv£e`Å@ÿ	Yã§íZﬁªÛ}˜›*®‘í™§™›˛<E›˚ΩJ’{ˇ˚›Ô~˜æEÁ|·ÙånßÔùAÁ0wÆﬂãÉB‹úáØL‡`üe‡√Ì›Xl«œ4c˘g¸ 7¯^¶±˙nóıœ£ﬂŸÍ¶œû©–˚Ægë„ò°sˆm¶¿<‡¸2`Ãr⁄Ø¬Œ^4x58éÂTﬁã ™¯7\ná<’Ä\"Máã,:L∞˘°DÛÉ~$^4}âç!æÈdgœñ	˜{‰∂¥ìv°˘øÅ“’P5G◊ç€∞≈∏‰©B»∫mñÀ˚Q`C|:>≤P¸ÃÕÙ‡ª7íË¯√–åøa\0[˚û^ø˘ñ\r†À-i!mB_2u∏SÂwqf‹á?[*Õx¸Ä€ae{&4˚”(¨·ª∆0Ü®™\nö¶â2SÃœ¯˝~y}ÿ!8†∑/…q√¢¨^∞1˙ûHÉå+øE[ôΩnkã4¶îî›Ω¨¢ÿß≥G‡æè“8§Y–e0x∂%>u€DùsCº,+äiEQ@Q!.Ωc¸¢\ZÜ∫_Ø◊+˛éÑ∑X1t£Æ^üWl+‘x øÆÃà-x∂¬¢Úœ¨›uT\ZSB ÑÓ∏≠\"O1ÿèPõ—˘L%œÅD˛ßìπp\0√°Î^‹ÜÇŸQhÖ•∫ÆÎ`†¯\nq≤‰πTW5z‹=‡Û˘ÑùçÇ\r‰Û˚0R\0T£gì‡÷®ﬁçpË≈≠/ÜÂÁ˘∂vJkRI∫–É]˚™ñ£g>ãB\róÊ0~z:>∆òLG©˚—3±5HdõÕ^èWàE°Å<‹–M/¶›^éØ¿Æ3,˚}ÅÌëôlÛ¡œä\\ê≠ƒé¸ÿÄîΩ¸0{˝Æ’¯£e\'©Bw,-Àò˙k,Œ7-ë9‰”‡ûcy‚HtøŸµ-VádÚNÚTü◊ÉRh=^EQÖ◊¢¬“B‚´BhÚÙhåµ˙·˘b‡ÏŒ?‰*‹õªvW£¥ö¿ﬁ\n‹u÷vKÂ(Úv¨∆ô†‘ç◊–i\0√∞†ò·#ºô\Z¿ÖÑ¥⁄‡»»õ#¬ÜqŸ\nv{d:ù¯ /ª√.…HPà˙qs¯0ªÈ∆Æa€—π¥Úªtl“:(˝%|˘{go€ÀxÄwISø¸¶pˇŸñâbˆä∫f1«Hâºíºú\ZÄâ8å·˜R%OFOW3Ê i∆bB¸\r∆rjÕÇ©!zwOOè˚≤(´˛qXó¨ıæ≤›Ê∫øtuìπ≥dPB7/û8“f≥¸~Õe“/µ9·çN[0lhöùTeSËsèâÏ¶gáA¢3 H4ë•ê»´U4Ü›náﬁﬁ^!x ı#®q~2ºÆ¿|;~¯üT’rì≥v€	iHòÌZ6u2◊çﬂcÒ\"”µ∞™g“Á D‹µär∏–ë1ÛhUû$Æä·G≈4è‚7•Äî˙ë®î˙—wí‡Üé+zª;¬3ÖÌPéÉd‹pﬁƒ¿®Œ^øÁœ“í\ZS∑È√6a1ﬂ¥ƒ«ñ+<z*\'Ëü£\r√/ ßU,c»êŸãI\\+\rúò7ìê8√ƒ¸ö¬ ÄÔ$r¿{X±!h†’\rLÒÛÙô\\ÊáWGµCNp‚√»iMQÆsÆ›πCö‚&a°ªQdøŒﬁ√øSÁxÈ≈AË{«Ú·tpˆg¬È‡Ql3&S∂`ù	˜6sPÃeï“øHq8Å¡í\Zc!Êÿ;#ÍqÉSyï¡|g]=\r¸qìP÷—zkUπü<9AëâçgÏa\"\"l‡Äß`Ë ±)€†âäÜq◊a≥@v¶rùp:0”¿#Ù·vÚH: 2âGﬁMa# d$h0%œx¸¶.t„ƒ)!ÿ—-ﬁmYZ>IZ‚\"Ó_i^6q§U∑~éêPL‡â\\ÿ„1CC4 FÂ¬åI#`JY!Tç	Ÿ6/êY`Ø¿AÌdkÏn<\r[˜ûÄ/æ:›Ù|)HH˚\\¡©Aj<?N|<Ω°SÚßã:≈BT¢`9§jlfVM}≥4≈$.°/π‹ë£uo∆è\'î] ™õ\n¢Ê∞S Ü√√K/áK.\Z&-Ò·ıÈ∞yG¨ˇ‡+¯∫…\\\"ë…ª)¨àˇ§‡‘ËÄÏ‰Ÿa™w#¶|ˇ˛ãªk.ã#ı£%ﬁò†H*Ú^¡[(M	CBØ°L√¨Üêóeá?\\£\n≤§%~»€«éŒÉØö \ZÈ‡âhÌtõaÛjzxv\0õù“KÆŒÙ¿8ú5‘§∏W∑ç|fwÛ[“ï~c¥Îñ Ô‚∆=â˝HiîÉô7m∆_3µ(‰¥≥*K‡µG¡OÓô•#sÂñ»ddfà‹ö(†»∞œ‹M3HYçJL°iÌ?Òí¨äjg‰ﬁ5Æ8°1&\nÜãk¶èÅ’èﬂœ˝√ò6aD0t–;•ÑBdúÍìáè“Ù{såøÿæ¥jå¨E$™–¥\nác˘\n,&ﬁß#p-\nÈ«2±»Å@3√++ä·ÖáØáuO,Ü[Áó”¡/vwª≈;ùx\n¬~ªt\\∞Ã‚Wëf“F‘\rÆΩïﬂC7∏FVçS·p±%‹{4ôU§ä‚¬l∏…epGu•¥ò\\ÎÙ‡˛$ÔlˆòyÆØ+Óê’0\"%-⁄„à˙¨¨&ç\n{Ë$ÑD./ç∫dùTfN-K&≥cûy8ÿ?€vÛÙY\r!¢–äèb»j“(∑ÖzÙm◊MÅÇs¶ójrùvYp`ÿ®Ï”Ë…\05+TTﬂc≤\ZBò–≠KÀKpr˚Ä¨&ï)Á•uwﬁP%k©gƒ0\'‰dög‘¶·≈Î‘÷`‡¸]7O!kA¬Ñ∆tˇ7¬ŒÒ%ÉBÂÛÂ\"N≈ÿB∞‡L.]Pòö©yÚ}vf‚3¡xAØŒ´⁄ø»jê°]K¶«˚^YM:Ùc”ÚLqG‰;≈{:ôPbŒ<+∆â˜î¡·ÆˆÂU!…|®G[åª±MB.	H& ¯ÒpÂ¬´Dπ§([ºß ≥3l\Z/[Jq±¥&t÷,µÓìUAPh 1”Ÿòl¥+f¬‘b”£«\'q¢í≈†ª[@ù9CZR˛}±|!	\n›µ∑r.⁄cŒnÖ≈¨∞r¨>(¡ÉMt)–‰àÑÊﬁn`£F\n◊K ∫n©BMMŒz4ÁÀd1%0Z¶ëûs¯ˆ•%i–\Z»®|ª8Ÿ¿4çbâ‹í\Zt≈j*~âÆÍƒ\\‡;¬í\"8-Q å™z∆Äñ¥MIa,º;-z2ß≥Ê}VÙíá˘ÕÊ\n©∫ €1”íÿK^ÉÖÆìsù¶hêüë¬.äEŸ*0:õ”“\"zW*°	åKô:ì BhUa◊—{™1ˆ5ÄbœBÔN˛Ù7>8æ^PmY`Ï? m©∆®¶Ö–ÿ∞I[<äÖæm;®VLÎ8vYz•Æ˚±G)x–6–w÷Kkj¡ÏCàÏÿ¬ÈôôﬁtÛ‰ØWF@≠¨\0u¡lb≥ß—ì0.˚ﬂﬁàΩ_ZSN◊©wÅíÈNJó»Ñ^ø¸oº\r¸ËIiI¸–Q’ΩûNë	Á0ßc]f\\!\ri√8‘˛˜?êµ4ÅÒ—øÒ]‡\'|U◊Ä¡Lrö¬õ(ÎiÖ∑µÔÌˇ“Ød¡[Ò˜∫È&Æ!a\"ù·)ìïÙÇ±í<(+©«8tHñÜ\0Œ ÏQ©[]È”Ωta4§Ô∑˙ÇŸz	]ˇû‚5√Ë\Z<©œ©πÀ∆ëîﬁú(“ ajgÑ±˘¿ˇÂVYI˙[PÌ‘Œ˚!è&,ôfyh–?˝ΩÌà¨%„pË€æ 6©`gRËHÔ¨°/4Åÿ¸Œ⁄í≤î&(æÉ_µ71jxO/¯:é$UlÆ{Ò;1.˜πzt® °Sw¶2^t]àlä=¯›û‹éﬂEw$x°zäQ=dY|\0&ÓºRM±€É·¯”OxÒ;Ñ»≥§Á∫ëò0Ë\"èn7kCávŸı`´XbämË¢À˚ª\\/¶ª∫NÉØÛò(ñíô`ª·~QJ–ô;h¬◊Î©ÇÂÄÂ¶ªA>	lÂﬂAµ=Ωªº≠ç‚]¨∫Em¥Õ¸ÏA–›mr6ﬁËK¡:°\Z‘â”Aõy≠¥\r∏Áß‘U—¢πiJ/,gÿyî¢QWúÖ†8Ú@o¡LÅ@œ4|n–{:’FO;äxµÅﬂ›*∂—g^Lh£æ∂I7b	}	g⁄‘Y`4~ºyh&-úÛœËÉÙ-8H¸†Å2Ôfp<≥î“–{n¥ï`õ∏Hy/ÜäΩÊπ^¸˚≥g˙l∞ˇÛã`ΩÛQ0,gØ¡K\Z)tH˜I-$nãR\0˚‘	∞]˚À,+Ú§Tx‰%.v?hES¿6yq‰øST8S4∂Ò\n8†éÉvñÜyÇ)Â(\n|≠†⁄);ß£É\n-Ï¨∏çJt∞\\¸IGﬂˇ∫èG_ƒÿœåÅ\ZåÒë?o‡tø°¶≈e– Ú°A‹ßNF7ô&÷®â‡7ÿV≈Ì∂íG\'-ó&q[Ÿ∞≥¢û˜\\ËÚÉ}k÷EÏ˛,≈3¿:æˇÛ∆j¡∞ã¨%∫áy˜pü˜Ö#`/€´^\"ˆıê2Œ∞¨dãﬁ’Ír7àoÏ∏µ‚ÏJa\0¥√ù(fõí\'DM§KNæÔ.(∫\"ˆÂYæCÔÅ˜e-uÿ8∞W˛ù\r—ËmmÉ-è>∫\'>≤¢ﬂÂm0å∑BÔ¨Ï»©´ü-aú}(L	‚fp=ñºaø:⁄∞K&\Z˜ˆØ3áÿgZ,cfÅµlû¨ùEÕ+Eëoç)2—Pª>në	/J}R{‘r®W´‡ò2\Z|Ê„ˆ\0ˇò˛™‡XN7–«\rÌ»~Pv´S‡4∆‡¡*ﬁéNh|≥ﬂ€Ù¿R:ü-k(rÓ≈`Ø∫\rè¿|®J4ZÎ˜@À∂ù≤ñ8fBÔ‘™‡àR\"zoB0NOÄ0jÈÏŸÇog≥˝P¸›•UÔM«>ÿ]GpF◊÷±◊ÄÂ‚´@Õ)€‘e®vl/3º^1\0&r¶ HqÏ.ﬂ%«8¸úz◊øõ¥5Ö¶\'bñ˙&ï£AµË	∑j?–up˝\rå¨cÄµÚˆ∏Æ	9¸˚˜†ß˘¥¨%ÍÕ4xûR˙?1Ö±˝≠¿ÉÉ}^5îZYå»aÂ\"—¢©¢≥a?ú¸‰sYãå◊uvøºæ|‚p5∆>Ÿ⁄{∫öﬁŸ(k…ÖúÆIπé+£§%2\n∞µ≤xVhÁ§ùõÒ+\"ŒÈ„i¡¡r`√õ8≠é|¸©œ∑àÃ·Ùó€E˛ΩÌ©Á‡¿oﬂ·!Ï\rµøπs*9™ãÙ0\núÎISì†–ÏI†\'Wº\"´A\\òÃ”¶oß\Z_ˇ_Y3Ò¥w¿Æ_˛\næze¯∫ŒÆË“Sgˇn¸È_ÜΩ!ÙÇ≈ñùª†eGzÆ≠£‹ª≥Øæ¿W†û¡XZ¿¨´p[p1òbq£\Z|åhZ8˛Ò°Î·ïJ∂<ˆ$¥lè.ö˚‰)ÿ˛ÙÛ∞-CL·Ë’P≥^nM=4H6*•}\'9g¿&nÔñãw,≠¸ú≈>DeJkËïn≤J/kv¥Ó‹--Ò·(\ZŸe•pÍ31–ßï2£\nÛô!Ë#ø»]_ˇ∞®H¬ÑnYVQ¨˘YÉ¡T˚mj“3åøTÏº*Ù]((ÔR¿óU∑˚î‹$\rH=uñ¡/)»#r¸Ù2ªÃØ˘K}E&¬Ñ&›Út3ûíßŒ˛%ÉöùÚ∫Ω?ó’\"\nMèˆÌ«Û≤˙\rq“\rè\rkoƒÁªEöÂg<áCÈÄûZ¯◊à\n˛ègØ≠¡¨-2QÖæ·≈qZÙ,•Û‚¬àÛ\0]√{˜πys_¢\nM\\W˚ÍÁò´<)´ﬂ+x∫zÌ⁄òœöé)4—ÓuQpOÛ}*˜ˇfvMÕk≤\Zï~Öæe√]”ï[±ÿdZæ!Ä\n˙÷RçˇΩ¨∆§_°âyÎV¥0?_Ñ!»%Mı0n±˙{ïÆ^◊ç8q	M,®[YØ\0[å”ÀÙ›·sû¬8oµÈÓÍYuu«•©_‚öò_ÛÍáLÅõ±ò¥≥Ê\ZfÜ·ª·Í∫∫=“		M\\˚ﬂØæÉ?∂$ñgÎa+(±ûrLûl—}◊ŒY∑&·U´ÑÖ&‘¨|[Qç0kÏê¶‹*ø ≈¶}Ó∆}èåqTeûπôê–ƒÇ5´>ÚÎ0ÛÏ∞≥2¥´g¥®π˚yKÓs§Ωf`Ï»T¸óœ´©Il›ˆ,4Q]˜ÍÕPg`yOöÇ∏,û–ÆŒ°pΩ67£˘™+◊¨Èˇ4}%4A©_á∑≥\Zª÷„X\ríëv˙|ß3ƒ9xó\næ˚Ê◊æv˚•+ﬁ¯-í§F“˜ó›;\r;ﬂjÙÊ)\rN ]*ÿ}Ü˛·Q8ÏŒ÷a< õ„Áüh∫qÁ‹uøI⁄Ì∂ÉˆËsYP˚_€⁄Ωù”97~åÌæê¬Ì´¬yßO—á±%≥ì)2ë2w[∑|˘CUü)Ù*K∞zûü™·ûccMá—Û¯C+Î¬Œé$Éî˜ÎM∑›[¡òÒ8g∞òã}°\\∫·‹√‘Z¿Û‘úööîﬁ˘ê∂\0∫˘ˆ{JΩ¿ƒ‚r¸ŸÑˇ?.IÖÛì\n„+5ÓyyNmmZûîíˆëjﬂÿöZ›ã£√mò¥.\0·Íìî@b|#éyµ ∏íﬂÕ{Ú…«≥ßê!M	>]≤ƒ·∂e]œôr„lf,„P¯d=ﬂ…ÀÄÔEÔ˝H}S°◊˝ﬁî\rÜlçfHÖÓÀGÀóÁ˙¸Ít‡l*S¯Dzr\n?\Z=ëÆÆÃ¬›\rŸ_é†°Ìÿ˝\r∫L¢ëq˛µ¢¿v´ÖmõµjUÇˇ#¨Tˇ“S›”ûørÌ\0\0\0\0IENDÆB`Ç'),
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
