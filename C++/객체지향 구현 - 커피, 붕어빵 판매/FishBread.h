#pragma once

#include "Food.h"

class FishBread : public Food {
private:
	int paste;

public:
	FishBread(const std::string& name, int price, int cnt, int paste);
};
