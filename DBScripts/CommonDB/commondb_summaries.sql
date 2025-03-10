USE CommonDB;

drop table `summaries`;

create table `summaries` (
	`s_id` bigint not null default 0 COMMENT 'summary id'
	, `a_id` bigint not null default 0
	, c_date TIMESTAMP NOT NULL DEFAULT (NOW())
	, m_date TIMESTAMP NOT NULL DEFAULT (NOW()) ON UPDATE CURRENT_TIMESTAMP 
	, PRIMARY KEY (`s_id`)
	, KEY idx_a_id(`a_id`)
)engine=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;