USE CommonDB;

drop table `accounts`;

create table `accounts` (
	`a_id` bigint not null default 0
	, `c_date` TIMESTAMP not null default (NOW())
	, `m_date` TIMESTAMP not null default (NOW()) ON UPDATE CURRENT_TIMESTAMP
	, PRIMARY KEY(`a_id`)
)engine=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;