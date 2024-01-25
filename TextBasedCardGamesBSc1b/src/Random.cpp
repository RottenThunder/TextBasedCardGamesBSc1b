#include "Random.h"

uint64_t Random::Generate64()
{
	return s_UniformDistribution(s_Engine);
}

uint64_t Random::GenerateRange64(uint64_t exclusiveMax)
{
	return s_UniformDistribution(s_Engine) % exclusiveMax;
}

uint64_t Random::GenerateRange64(uint64_t min, uint64_t max)
{
	uint64_t range = (max - min) + 1;
	uint64_t value = s_UniformDistribution(s_Engine) % range;
	return value + min;
}

bool Random::GeneratePercentageChance(uint64_t percentChanceToWin)
{
	uint64_t value = Random::GenerateRange64(100);
	return value < percentChanceToWin;
}