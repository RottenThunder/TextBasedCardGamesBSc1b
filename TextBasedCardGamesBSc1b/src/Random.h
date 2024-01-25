#pragma once
#include <random>

static std::random_device s_RandomDevice;
static std::mt19937_64 s_Engine(s_RandomDevice());
static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

//Source of Generating Random Numbers
class Random
{
public:
	//Generates a random 64-bit number
	static uint64_t Generate64();
	//Generates a random 64-bit number in the interval [0...exclusiveMax-1] with equal probabilities
	static uint64_t GenerateRange64(uint64_t exclusiveMax);
	//Generates a random 64-bit number in the interval [min...max] with equal probabilities
	static uint64_t GenerateRange64(uint64_t min, uint64_t max);
	//Generates a bool based on percentChanceToWin
	static bool GeneratePercentageChance(uint64_t percentChanceToWin);
};