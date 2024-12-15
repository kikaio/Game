#pragma once

class Random {
public:
	Random();
private:
	std::random_device randomDevice;
	std::mt19937 gen;
	std::uniform_int_distribution<int> dis;
	int disMax;
	unsigned int seed;
public:
	int GetRand(int _ltMax=0);
	int GetRand(int _gteMin, int _lteMax);
public:
	int SeedGen();
	int SimpleSeedGen();
	int ComplexSeedGen();
};