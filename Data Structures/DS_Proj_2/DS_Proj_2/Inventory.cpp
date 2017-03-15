#include "Inventory.h"
#include "SLList.h"

Inventory::Inventory()
{
	coins = 5000;
	weight = 0;
	maxWeight = 50;
}

bool Inventory::AddItem(Item x)
{
	//this->coins = 5000;
	//this->maxWeight = 50;
	//TODO::check the cost if it is in the budget(x.cost < || == coins) then go ahead add the item and add the weught
	if ((int)x.cost <= this->coins && (int)(x.weight + this->weight) <= this->maxWeight)
	{
		this->coins = this->coins - x.cost;
		this->weight = this->weight + x.weight;
		items.addHead(x);

		
		cout << "Total coins left with you: " << coins << "\n";
		cout << "Total weight : " << weight << "\n";
	
		return true;
	}

	else
	{
		cout << "No more leftout pennies in piggy bank and i think you shall gain little more weight to carry out.\n";
		return false;
	}
	
}

bool Inventory::RemoveItem(Item x)
{ 
	SLLIter <Item> iter(items); 
	for (iter.begin(); !iter.end(); iter.operator++())
	{
		if (iter.current() == x)
		{
			items.remove(iter);
			this->coins = this->coins + x.cost;
			this->weight = this->weight - x.weight;
			

			return true;
		}
	
	}

		return false;
	
}

void Inventory::Display()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD curpos = { 0, 0 };
	cout << '+';
	for (int i = 0; i < WIDTH - 3; i++)
	{
		cout << '-';
	}
	cout << '+';
	for (int i = 0; i < 1; i++)
	{
		curpos.X = 0;
		curpos.Y++;
		SetConsoleCursorPosition(out, curpos);
		cout << '|';
		curpos.X = WIDTH - 2;
		SetConsoleCursorPosition(out, curpos);
		cout << '|';
	}
	curpos.X = 0;
	curpos.Y++;
	SetConsoleCursorPosition(out, curpos);
	cout << "| Name\t\t Price\t\t Weight";
	cout << "\n| Weight: " << this->weight << "\t\t\t"<< " Coins: "<< this->coins << "\t\t" << "  |";
	curpos.X = WIDTH - 2;
	SetConsoleCursorPosition(out, curpos);
	cout << '|';

	curpos.X = 0;
	curpos.Y++;
	curpos.Y++;
	SetConsoleCursorPosition(out, curpos);
	cout << '+';
	for (int i = 0; i < WIDTH - 3; i++)
	{
		cout << '-';
	}
	cout << '+';

	for (int i = 0; i < 2; i++)
	{
		curpos.X = 0;
		curpos.Y++;
		SetConsoleCursorPosition(out, curpos);
		cout << '|';
		curpos.X = WIDTH - 2;
		SetConsoleCursorPosition(out, curpos);
		cout << '|';
	}
	//TODO: Come back later
	
	SLLIter<Item> iter(items);
	for (iter.begin(); !iter.end(); iter.operator++())
	{
		curpos.X = 0;
		curpos.Y++;
		SetConsoleCursorPosition(out, curpos);
		cout << '|';
		/*curpos.X += 10;
		cout << this->weight;
		curpos.X += 15;*/
		cout << " " <<iter.current().name;
		curpos.X += 17;
		SetConsoleCursorPosition(out, curpos);
		cout << iter.current().cost;
		curpos.X += 16;
		SetConsoleCursorPosition(out, curpos);
		cout << iter.current().weight;
		curpos.X += 17;
		/*SetConsoleCursorPosition(out, curpos);
		cout << contents[i].weight;*/
		curpos.X = WIDTH - 2;
		SetConsoleCursorPosition(out, curpos);
		cout << '|';
	}

	curpos.X = 0;
	curpos.Y++;
	SetConsoleCursorPosition(out, curpos);
	cout << '+';
	for (int i = 0; i < WIDTH - 3; i++)
	{
		cout << '-';
	}
	cout << '+';
}