#pragma once

enum class ERR_CATEGORY {
	NONE
	, DB
};

enum class DB_ERR_DETAIL {
	CONN_FAILED
	, CONN_TIMEOUT
	, INVALID_PARAM
};

