USE gameDB;

DELIMITER $$

DROP PROCEDURE IF EXISTS `usp_gameuser_select`$$

CREATE PROCEDURE `usp_gameuser_select` (
	IN `in_account_id` BIGINT
) 
BEGIN
	DECLARE _gameuser_id BIGINT DEFAULT -1;

	-- todo : gameuser must exist in gameusers table
	SELECT gameuser_id into _gameuser_id FROM `gameusers` WHERE `account_id` = in_account_id;
	
	IF _gameuser_id = -1 THEN
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT='gameuser not exist';
	END IF;
	
	SELECT gameuser_id, account_id, c_date, m_date FROM `gameusers` WHERE `gameuser_id` = _gameuser_id;
	SELECT id, gameuser_id, basis_id, c_date, m_date FROM `characters` WHERE `gameuser_id` = _gameuser_id;
	SELECT id, gameuser_id, basis_id, item_cnt, item_cnt_prev, c_date, m_date FROM `items` WHERE `gameuser_id` = _gameuser_id;
	SELECT id, gameuser_id, basis_id, c_date, m_date FROM `costumes` WHERE `gameuser_id` = _gameuser_id;

END$$

DELIMITER ;
