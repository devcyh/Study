#pragma once

#include <string>

class Food {
private:
	std::string name;
	int price;
	int cnt;

public:
	Food(const std::string& name, int price, int cnt);

	std::string getName() const;
	int getPrice() const;
	int getCnt() const;

	void setName(const std::string& name);
	void setPrice(int price);
	void setCnt(int cnt);
};
