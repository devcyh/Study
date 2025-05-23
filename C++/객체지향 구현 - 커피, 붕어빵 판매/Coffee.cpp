#include "Coffee.h"

Coffee::Coffee(const std::string& name, int price, int cnt, bool isHot, int coffDens, int sugar) : Food(name, price, cnt), isHot(isHot), coffDens(coffDens), sugar(sugar) {}
