USE GameDB;

DROP TABLE IF EXISTS `gameusers`;

CREATE TABLE `gameusers` (
	`gameuser_id` BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY
	, `account_id` BIGINT NOT NULL DEFAULT 0 COMMENT "id about account in common db"
	, `c_date` TIMESTAMP NOT NULL DEFAULT (NOW())
	, `m_date` TIMESTAMP NOT NULL DEFAULT (NOW()) on UPDATE CURRENT_TIMESTAMP
	, UNIQUE KEY idx_account_id_gameuser_id(`gameuser_id`, `account_id`)
)engine=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;