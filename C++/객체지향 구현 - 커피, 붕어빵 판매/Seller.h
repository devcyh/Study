#pragma once

#include <iostream>
#include <unordered_map>
#include "Food.h"

class Seller {
private:
	const int SPEAR_CNT = 5;
	int income;
	void makeFood(Food& food, int addCnt) const;

public:
	Seller();
	bool sellItem(Food& food, int sellCnt);
	void getInfo(const std::unordered_map<std::string, Food*>& um) const;
};
