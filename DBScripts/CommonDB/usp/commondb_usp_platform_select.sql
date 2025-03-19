
DELIMITER $$
USE CommonDB$$
DROP PROCEDURE IF EXISTS `usp_platform_select`$$

create procedure `usp_platform_select`(
	IN in_s_id varchar(50)
	, IN in_p_type int
	, IN in_token varchar(300)
	, IN in_refresh_token varchar(300)
	, IN in_def_main_hero_id int
	, IN in_def_main_frame_id int 
	, IN in_def_greeting_ment varchar(50)
)
BEGIN
	SET @is_exist = 0;
	SET @new_a_id = 0;

	SELECT EXISTS (
		SELECT 1 FROM `platforms`WHERE `s_id` = in_s_id AND `p_type` = in_p_type
	) as success INTO @is_exist;
	IF @is_exist = 0 THEN
		INSERT INTO `accounts` (`c_date`, `m_date`) 
		VALUES (CURRENT_TIMESTAMP, CURRENT_TIMESTAMP);
		set @new_a_id = LAST_INSERT_ID();

		INSERT INTO `platforms` (`s_id`, `p_type`, `a_id`, `token`, `refresh_token`) 
		VALUES (in_s_id, in_p_type, @new_a_id, in_token, in_refresh_token);
		-- 신규생성 관련해서 한번에 생성해 준다.

		INSERT INTO `profiles` (`a_id`, `main_hero_id`, `main_frame_id`, `greeting_ment`) 
		VALUE (@new_a_id, in_def_main_hero_id, in_def_main_frame_id, in_def_greeting_ment);

		INSERT INTO `summaries` (`a_id`) 
		VALUES (@new_a_id);
	ELSE
		SELECT `a_id` FROM `platforms` 
		WHERE `s_id` = in_s_id AND `p_type` = in_p_type INTO @new_a_id ;
		UPDATE `platforms` SET `token` = in_token, `refresh_token` = in_refresh_token
		WHERE `a_id` = @new_a_id;
	END IF;
	
	SELECT @is_exist as is_old_user;
	
	SELECT `p_id`, `s_id`, `p_type`, `a_id`, `token`, `refresh_token`, `c_date`, `m_date` 
	FROM `platforms` WHERE `a_id` = @new_a_id;
	
	SELECT `a_id`, `c_date`, `m_date`
	FROM `accounts` WHERE `a_id` = @new_a_id;
	
	SELECT `s_id`, `a_id`, `c_date`, `m_date` 
	FROM `summaries` WHERE `a_id` = @new_a_id;

	SELECT `p_id`, `a_id`, `main_hero_id`, `main_frame_id`, `greeting_ment`, `c_date`, `m_date`
	FROM `profiles` WHERE `a_id` = @new_a_id;
	
END$$

DELIMITER ;