#include "Food.h"

Food::Food(const std::string& name, int price, int cnt)
	: name(name), price(price), cnt(cnt) {
}

std::string Food::getName() const {
	return name;
}

int Food::getPrice() const {
	return price;
}

int Food::getCnt() const {
	return cnt;
}

void Food::setName(const std::string& name) {
	this->name = name;
}

void Food::setPrice(int price) {
	this->price = price;
}

void Food::setCnt(int cnt) {
	this->cnt = cnt;
}
