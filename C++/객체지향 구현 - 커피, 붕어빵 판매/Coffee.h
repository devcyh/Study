#pragma once

#include "Food.h"

class Coffee : public Food {
private:
	bool isHot;
	int coffDens; // %
	int sugar; // g

public:
	Coffee(const std::string& name, int price, int cnt, bool isHot, int coffDens, int sugar);
};
