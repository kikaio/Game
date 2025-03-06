#include "pch.h"
#include "Random.h"

Random::Random()
	: engine(randomDevice()), dis(0, 10000)
{
}

int Random::GetRand(int _ltMax)
{
	if (_ltMax == 0) {
		return dis(engine);
	}
	else {
		std::uniform_int_distribution<int> _dis(0, _ltMax);
		return _dis(engine);
	}
}

int Random::GetRand(int _gteMin, int _lteMax)
{
	ASSERT_CRASH(_gteMin <= _lteMax);
	std::uniform_int_distribution<int> _dis(_gteMin, _lteMax);
	return _dis(engine);
}

int Random::SeedGen()
{
	return(((seed = seed * 214013L + 2531011L) >> 16) & 0x7FFF);
}

int Random::SimpleSeedGen()
{
	return(((seed = seed + 2531011L) >> 3) & 0x7FFF);
}

int Random::ComplexSeedGen()
{
	unsigned int next = seed;
	int  result;

	next *= 1103515245;
	next += 12345;
	result = (unsigned int)(next / 65536) % 2048;

	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int)(next / 65536) % 1024;

	next *= 1103515245;
	next += 12345;
	result <<= 10;
	result ^= (unsigned int)(next / 65536) % 1024;

	seed = next;
	return result;
}
