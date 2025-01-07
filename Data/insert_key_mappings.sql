DELIMITER //
CREATE PROCEDURE InsertKeyMappings()
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
END //
DELIMITER ;

-- Call the stored procedure to insert the values
CALL InsertKeyMappings();