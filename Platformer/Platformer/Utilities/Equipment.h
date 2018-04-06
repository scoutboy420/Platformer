#pragma once
#include "../Entities/Item.h"
#include <vector>

class Equipment
{
private:
	std::vector<Item> items_;
public:
	void addItem(Item& item);
	Item& removeItem(int index);
};