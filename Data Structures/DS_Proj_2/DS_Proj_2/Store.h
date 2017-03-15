#pragma once
#include "DynArray.h"
#include "Item.h"
class Store
{
	DynArray<Item> contents;
private:
	void drawStuff(int begin = 0, int num = 0);
public:
	void Load(const char * path);
	void SortByType();
	void SortByName();
	void SortByPrice();
	void SortByWeight();
	void Display();
	bool Search(const char * name, Item & objects);
};

