USE CommonDB;

drop table if exists `accounts`;

create table `accounts` (
	`a_id` bigint not null auto_increment PRIMARY KEY
	, `c_date` TIMESTAMP not null default (NOW())
	, `m_date` TIMESTAMP not null default (NOW()) ON UPDATE CURRENT_TIMESTAMP
)engine=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE utf8mb4_unicode_ci;