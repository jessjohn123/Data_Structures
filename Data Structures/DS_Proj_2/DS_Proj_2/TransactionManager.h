#pragma once
#include "Store.h"
#include "Inventory.h"
class TransactionManager
{
	struct Transaction
	{
		Item theItem;
		bool bought;
	};
	Store theStore;
	Inventory theInventory;
	SLList<Transaction> theHistory;

public:
	TransactionManager()
	{
		theStore.Load("items.shp");
	}
	void Buy();
	void Sell();
	void Undo();
	Inventory& GetInventory() { return theInventory; }
	
};
