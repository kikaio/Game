USE gameDB;

DELIMITER $$

DROP PROCEDURE IF EXISTS `usp_gameuser_create`$$

CREATE PROCEDURE `usp_gameuser_create` (
	IN `in_account_id` BIGINT 
	, IN `in_def_character_str` VARCHAR(100) 
	, IN `in_def_items_str` VARCHAR(100) 
	, IN `in_def_costumes_str` VARCHAR(100) 
)
BEGIN
	DECLARE gameuser_id BIGINT DEFAULT 0;
	DECLARE is_gameuser_exists BOOLEAN DEFAULT FALSE;
	DECLARE character_str, item_str, costume_str VARCHAR(100);
	
	
	#------------------------------------------------------------------------------------------------
	/*
	DECLARE EXIT HANDLER FOR SQLEXCEPTION
	BEGIN
		ROLLBACK;
		SELECT -9 as state;
	END;
	*/
	#------------------------------------------------------------------------------------------------
	START TRANSACTION;
	-- gameuser 가 존재하는 지 확인
	SELECT EXISTS (SELECT 1 FROM gameusers WHERE `account_id`=`in_account_id`) INTO is_gameuser_exists;
	IF is_gameuser_exists THEN
	 -- excecption 처리
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'game user already exists in gameusers table';
	END IF;

	INSERT INTO `gameusers` (`account_id`) VALUES (`in_account_id`);
	SET gameuser_id = LAST_INSERT_ID();
	
	-- def 문자열들은 _ 기준으로 나눠 관련 table에 data를 넣어준다.
	characters:LOOP 
	IF LENGTH(`in_def_character_str`) = 0 THEN
		LEAVE characters;
	END IF;
	SET character_str = SUBSTRING_INDEX(in_def_character_str, '_', 1);
	SET in_def_character_str = SUBSTRING(in_def_character_str, LENGTH(character_str)+2);
	IF LENGTH(character_str) = 0 THEN 
		LEAVE characters;
	END IF;
	IF `character_str` REGEXP '^[0-9]+$' THEN 
		INSERT INTO `characters` (`gameuser_id`, `basis_id`) VALUES (`gameuser_id`, CAST(character_str as UNSIGNED));
	ELSE 
	 -- todo : exception 발생
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'character_str is not numeric.';
	END IF;
	END LOOP;
	
	
	items:LOOP 
	IF LENGTH(`in_def_items_str`) = 0 THEN
		LEAVE items;
	END IF;
	SET item_str = SUBSTRING_INDEX(in_def_items_str, '_', 1);
	SET in_def_items_str = SUBSTRING(in_def_items_str, LENGTH(item_str)+2);
	IF LENGTH(item_str) = 0 THEN 
		LEAVE items;
	END IF;
	IF `item_str` REGEXP '^[0-9]+$' THEN 
		INSERT INTO `items` (`gameuser_id`, `basis_id`) VALUES (`gameuser_id`, CAST(item_str as UNSIGNED));
	ELSE 
	 -- todo : exception 발생
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'item_str is not numeric.';
	END IF;
	END LOOP;
	
	costumes:LOOP 
	IF LENGTH(`in_def_costumes_str`) = 0 THEN
		LEAVE costumes;
	END IF;
	SET costume_str = SUBSTRING_INDEX(in_def_costumes_str, '_', 1);
	SET in_def_costumes_str = SUBSTRING(in_def_costumes_str, LENGTH(costume_str)+2);
	IF LENGTH(costume_str) = 0 THEN 
		LEAVE costumes;
	END IF;
	IF `costume_str` REGEXP '^[0-9]+$' THEN 
		INSERT INTO `costumes` (`gameuser_id`, `basis_id`) VALUES (`gameuser_id`, CAST(costume_str as UNSIGNED));
	ELSE 
	 -- todo : exception 발생
		SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'costume_str is not numeric.';
	END IF;
	END LOOP;
COMMIT;

END$$

DELIMITER ;