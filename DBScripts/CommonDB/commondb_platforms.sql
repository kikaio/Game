USE CommonDB;

drop table if exists `platforms`;

create table `platforms` (
	`p_id` bigint not null AUTO_INCREMENT
	, `s_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_bin not null default "" COMMENT 'device key or oauth sns id, etc'
	, `p_type` int not null default 0
	, `a_id` bigint not null default 0 COMMENT 'user account id'
	, `token` varchar(300) not null default ""COMMENT 'toke for login auth'
	, `refresh_token` varchar(300) not null default "" COMMENT 'refresh toke for login token refresh'
	, `c_date` TIMESTAMP NOT NULL default (NOW())
	, `m_date` TIMESTAMP NOT NULL default (NOW()) ON UPDATE CURRENT_TIMESTAMP
	, PRIMARY KEY(`p_id`)
	, KEY idx_s_id(`s_id`)
	, KEY idx_p_type(`p_type`)
	, key idx_a_id(`a_id`)
)engine=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;