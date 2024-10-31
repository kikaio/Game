#pragma once


enum RWType : uint8_t {
	NONE = 0
	, READ = 1
	, WRITE = 2
	, READ_WRITE = READ | WRITE
};