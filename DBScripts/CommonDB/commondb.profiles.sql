USE CommonDB;

drop table `profiles`;

create table `profiles` (
	`p_id` bigint not null default 0 COMMENT 'summary id'
	, `a_id` bigint not null default 0 COMMENT 'id for account'
	, `main_hero_id` bigint NOT NULL DEFAULT 0
	, `main_frame_id` int NOT NULL DEFAULT 0
	, `greeting_ment` varchar(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL DEFAULT "hello" 
	, `c_date` TIMESTAMP NOT NULL DEFAULT (NOW())
	, `m_date` TIMESTAMP NOT NULL DEFAULT (NOW()) ON UPDATE CURRENT_TIMESTAMP 
	, PRIMARY KEY (`p_id`)
	, KEY idx_a_id(`a_id`)
)engine=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;