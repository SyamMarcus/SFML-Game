#include "Random.h"



Random::Random(int _firstNum, int _maxNum)
{

	firstNum = _firstNum;
	maxNum = _maxNum;
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(firstNum, maxNum); // distribution in range [1, 6]
	//std::cout << dist(rng) << std::endl;
	randomNum = dist(rng);
}


Random::~Random()
{
}

int Random::GetRandNum()
{
	return randomNum;
}

