DELIMITER $$

USE commondb$$

DROP PROCEDURE IF EXISTS `usp_profile_select`$$

CREATE PROCEDURE `usp_profile_select`(
	IN `in_account_id` bigint  
)
BEGIN

SELECT `p_id`, `a_id`, `nick_name`, `main_hero_id`, `main_frame_id`, `greeting_ment`, `c_date`, `m_date`
FROM profiles WHERE `a_id` = `in_account_id`;

END$$

DELIMITER ;