#include <iostream>
#include <unordered_map>
#include "FishBread.h"
#include "Coffee.h"
#include "Seller.h"

int main() {
	FishBread patFishBread("�Ϻؾ", 1000, 5, 0);
	FishBread creamFishBread("��ũ���ؾ", 1200, 5, 1);
	Coffee americano("�Ƹ޸�ī��", 2500, 5, true, 50, 0);
	Coffee iceAmericano("���̽��Ƹ޸�ī��", 2500, 5, false, 50, 0);

	std::unordered_map<std::string, Food*> um;

	um["�Ϻؾ"] = &patFishBread;
	um["��ũ���ؾ"] = &creamFishBread;
	um["�Ƹ޸�ī��"] = &americano;
	um["���̽��Ƹ޸�ī��"] = &iceAmericano;

	Seller seller;

	while (true) {
		std::string foodName;
		std::cout << "[�ֹ�] ";
		std::cin >> foodName;

		if (foodName == "q") {
			break;
		}
		else if (foodName == "��Ȳ") {
			seller.getInfo(um);
			std::cout << "\n";
			continue;
		}

		auto iter = um.find(foodName);

		if (iter == um.end()) {
			std::cout << "�׷� �޴� �����ϴ�\n\n";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}

		int needCnt;
		std::cin >> needCnt;

		if (std::cin.fail()) {
			std::cout << "������ ���ڸ� �Է��ϼ���.\n\n";
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
