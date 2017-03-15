#pragma once
#include "SLList.h"
#include "Item.h"
class Inventory
{
	SLList <Item> items;
	int coins, weight, maxWeight;

public:
	Inventory();
	bool AddItem(Item x);
	bool RemoveItem(Item x);
	void Display();

	int GetWeight() { return weight; }
	int GetMaxWeight() { return maxWeight; }
	int GetCoins() { return coins; }
	void SetCoins(int m_coins) { coins = m_coins; }
	void SetWeight(int m_weight) { weight = m_weight; }
};

