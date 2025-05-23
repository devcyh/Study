#include "Seller.h"

Seller::Seller()
	: income(0) {
}

void Seller::makeFood(Food& food, int addCnt) const {
	int foodCnt = food.getCnt();
	std::cout << food.getName() << "을 " << addCnt << "개 제조중..\n";
	int totCnt = foodCnt + addCnt;
	food.setCnt(totCnt);
	std::cout << "제조 후 " << food.getName() << "의 총 개수: " << totCnt << "\n";
}

bool Seller::sellItem(Food& food, int sellCnt) {
	int price = food.getPrice();
	int foodCnt = food.getCnt();

	if (foodCnt <= sellCnt) {
		makeFood(food, sellCnt - foodCnt + SPEAR_CNT);
		foodCnt = food.getCnt();
	}

	food.setCnt(foodCnt - sellCnt);
	int totIncome = price * sellCnt;
	income += totIncome;

	std::cout << food.getName() << "을 " << sellCnt << "개 판매\n총 수입: " << income << "\n";
	return true;
}

void Seller::getInfo(const std::unordered_map<std::string, Food*>& um) const {
	for (auto iter : um) {
		Food* food = iter.second;
		std::cout << "" << food->getName() << ") 재고: " << food->getCnt() << "\n";
	}
	std::cout << "총 수입: " << income << "\n";
}
