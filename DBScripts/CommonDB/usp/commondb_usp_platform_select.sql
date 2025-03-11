
DELIMITER $$
USE CommonDB$$
DROP PROCEDURE IF EXISTS `usp_platform_select`$$

create procedure `usp_platform_select`(
	IN in_s_id varchar(50)
	, IN in_p_type int
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
		INSERT INTO `accounts` (`c_date`, `m_date`) VALUES (CURRENT_TIMESTAMP, CURRENT_TIMESTAMP);
		set @new_a_id = LAST_INSERT_ID();
		INSERT INTO `platforms` (`s_id`, `p_type`, `a_id`) VALUES (in_s_id, in_p_type, @new_a_id);
		-- 신규생성 관련해서 한번에 생성해 준다.
		INSERT INTO `profiles` (`a_id`, `main_hero_id`, `main_frame_id`, `greeting_ment`) VALUE (@new_a_id, in_def_main_hero_id, in_def_main_frame_id, in_def_greeting_ment);
		INSERT INTO `summaries` (`a_id`) VALUES (@new_a_id);
	END IF;
	
	SELECT @is_exist as is_old_user
	, t1.`p_id`, t1.`s_id`, t1.`p_type`, t1.`a_id`, t1.`c_date`, t1.`m_date` 
	, t2.`a_id`, t2.`c_date`, t2.`m_date`
	, t3.`s_id`, t3.`a_id`, t3.`c_date`, t3.`m_date`
	, t4.`p_id`, t4.`a_id`, t4.`main_hero_id`, t4.`main_frame_id`, t4.`greeting_ment`, t4.`c_date`, t4.`m_date`
	FROM `platforms` as t1
		INNER JOIN `accounts` as t2 on t1.`a_id` = t2.`a_id`
		INNER JOIN `summaries` as t3 on t1.`a_id` = t3.`a_id`
		INNER JOIN `profiles` as t4 on t1.`a_id` = t4.`a_id`
	WHERE t1.`s_id` = in_s_id AND t1.`p_type` = in_p_type;
END$$

DELIMITER ;