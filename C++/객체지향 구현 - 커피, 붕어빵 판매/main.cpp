#include <iostream>
#include <unordered_map>
#include "FishBread.h"
#include "Coffee.h"
#include "Seller.h"

int main() {
	FishBread patFishBread("팥붕어빵", 1000, 5, 0);
	FishBread creamFishBread("슈크림붕어빵", 1200, 5, 1);
	Coffee americano("아메리카노", 2500, 5, true, 50, 0);
	Coffee iceAmericano("아이스아메리카노", 2500, 5, false, 50, 0);

	std::unordered_map<std::string, Food*> um;

	um["팥붕어빵"] = &patFishBread;
	um["슈크림붕어빵"] = &creamFishBread;
	um["아메리카노"] = &americano;
	um["아이스아메리카노"] = &iceAmericano;

	Seller seller;

	while (true) {
		std::string foodName;
		std::cout << "[주문] ";
		std::cin >> foodName;

		if (foodName == "q") {
			break;
		}
		else if (foodName == "현황") {
			seller.getInfo(um);
			std::cout << "\n";
			continue;
		}

		auto iter = um.find(foodName);

		if (iter == um.end()) {
			std::cout << "그런 메뉴 없습니다\n\n";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}

		int needCnt;
		std::cin >> needCnt;

		if (std::cin.fail()) {
			std::cout << "개수로 숫자를 입력하세요.\n\n";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}

		Food* food = iter->second;
		seller.sellItem(*food, needCnt);

		std::cout << "\n";
	}

	return 0;
}
