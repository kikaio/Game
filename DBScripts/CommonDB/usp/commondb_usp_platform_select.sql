
DELIMITER $$
USE CommonDB$$
DROP PROCEDURE IF EXISTS `usp_platform_select`$$

create procedure `usp_platform_select`(
	IN in_s_id varchar(50)
	, IN in_p_type int
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
	END IF;
	
	SELECT `p_id`, `s_id`, `p_type`, `a_id`, `c_date`, `m_date` FROM `platforms` WHERE `s_id` = in_s_id AND `p_type` = in_p_type;
END$$

DELIMITER ;