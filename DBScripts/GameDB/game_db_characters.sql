USE gameDB;

DROP TABLE IF EXISTS `characters`;

CREATE TABLE `characters` (
	`id` BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY
	, `gameuser_id` BIGINT NOT NULL DEFAULT 0
	, `basis_id` BIGINT NOT NULL DEFAULT 0 COMMENT "basis id about this character"
	, `c_date` TIMESTAMP NOT NULL DEFAULT (NOW())
	, `m_date` TIMESTAMP NOT NULL DEFAULT (NOW()) ON UPDATE CURRENT_TIMESTAMP
	, UNIQUE KEY idx_gameuser_id_basis_id(`gameuser_id`, `basis_id`)
)engine=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;