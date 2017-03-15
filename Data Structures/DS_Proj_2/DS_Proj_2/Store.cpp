#include "Store.h"

void Store::drawStuff(int _begin, int num)
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
	cout << "| Type\t\t Name\t\t Price\t\t Weight";
	//cout << "\n| Weight: " << << "\t\t\t" << " Coins: " << this->coins << "\t\t" << "  |";
	curpos.X = WIDTH - 2;
	SetConsoleCursorPosition(out, curpos);
	cout << '|';

	curpos.X = 0;
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
	for (unsigned int i = _begin; i < _begin + (num?num:contents.size()); i++)
	{
		curpos.X = 0;
		curpos.Y++;
		SetConsoleCursorPosition(out, curpos);
		cout << '|';
		cout << contents[i].type;
		curpos.X += 18;
		SetConsoleCursorPosition(out, curpos);
		cout << contents[i].name;
		curpos.X += 15;
		SetConsoleCursorPosition(out, curpos);
		cout << contents[i].cost;
		curpos.X += 17;
		SetConsoleCursorPosition(out, curpos);
		cout << contents[i].weight; 
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
void Store::Display()
{
	drawStuff();
}

void Store::Load(const char * path)
{
	fstream fin;
	fin.open(path, ios_base::in);
	if (fin)
	{
		int count;
		fin >> count; // items in the store
		contents.reserve(count);
		Item temp;  //containor to keep track of the items in file
		for (int i = 0; i < count; i++)
		{
			fin.ignore(INT_MAX, '\n');
			fin >> temp.type >> temp.name >> temp.cost >> temp.weight;
			contents.append(temp);
		}
	}

}


void Store::SortByName()
{
	int j;
	for (unsigned int i = 0; i < contents.size(); i++)
	{
		j = i;
		while ( j > 0 && strcmp(contents[j].name, contents[j -1].name) < 0)
		{
			swap(contents[j], contents[j - 1]);
			j--;
		}
	}
}

void Store::SortByType()
{
	int j;
	for (unsigned int i = 0; i < contents.size(); i++)
	{
		j = i;
		while (j > 0 && strcmp(contents[j].type, contents[j - 1].type) < 0)
		{
			swap(contents[j], contents[j - 1]);
			j--;
		}
	}
}

void Store::SortByPrice()
{
	int j;
	for (unsigned int i = 1; i < contents.size(); i++)
	{
		j = i;

		while (j > 0 && contents[j].cost < contents[j - 1].cost)
		{
			swap(contents[j], contents[j - 1]);
			j--;
		}
	}
}

void Store::SortByWeight()
{
	int j; 
	for (unsigned int i = 0; i < contents.size(); i++)
	{
		j = i; 
		while (j > 0 && contents[j].weight < contents[j - 1].weight)
		{
			swap(contents[j], contents[j - 1]);
			j--;
		}
	}
}



bool Store::Search(const char * name, Item &objects)
{

	//cout << "What would you like to search for?\n";
	//cin.getline(userInput, 32);

	//string user = userInput;
	for (unsigned int i = 0; i < contents.size(); i++)
	{
		if (_strcmpi(name, contents[i].name) == 0)
		{
			system("cls");
			drawStuff(i,1);
			objects = contents[i];
			return true;
		}
		
	}
	return false;
}