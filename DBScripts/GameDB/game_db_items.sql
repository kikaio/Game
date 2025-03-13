USE GameDB;

DROP TABLE IF EXISTS `items`;

CREATE TABLE `items` (
	`id` BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY
	, `gameuser_id` BIGINT NOT NULL DEFAULT 0
	, `basis_id` BIGINT NOT NULL DEFAULT 0 COMMENT "basis id about this item"
	, `item_cnt` BIGINT NOT NULL DEFAULT 0
	, `item_cnt_prev` BIGINT NOT NULL DEFAULT 0 COMMENT "item cnt about pre update"
	, `c_date` TIMESTAMP NOT NULL DEFAULT (NOW())
	, `m_date` TIMESTAMP NOT NULL DEFAULT (NOW()) on UPDATE CURRENT_TIMESTAMP
	, UNIQUE KEY idx_gameuser_id_basis_id(`gameuser_id`, `basis_id`)
)engine=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;