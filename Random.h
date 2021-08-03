#pragma once
#include <iostream>
#include <random>

class Random
{
public:
	Random(int _firstNum, int _maxNum);
	~Random();

	int GetRandNum();


private:
	int firstNum;
	int maxNum;
	int randomNum;

};

