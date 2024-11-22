#pragma once


enum class DBNameType : uint8_t {
	NONE
	, CommonDB
	, GameDB
};

enum class RWType : uint8_t {

	NONE = 0
	, READ = 1 << 0
	, WRITE = 1 << 1
	, READ_WRITE = READ | WRITE
};