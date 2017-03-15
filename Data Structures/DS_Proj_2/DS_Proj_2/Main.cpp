#include <iostream>
#include "TransactionManager.h"
#include <Windows.h>

int menu()
{
	int menuSelection = 0;
	cout << "\n";
	cout << "*****************************************" << endl;
	cout << "        INVENTORY OPTIONS                " << endl;
	cout << "*****************************************" << endl;
	cout << "1 - Sort the store                       " << endl;
	cout << "2 - Search for an item in the store      " << endl;
	cout << "3 - Buy an item                          " << endl;
	cout << "4 - Sell an item                         " << endl;
	cout << "5 - Undo the last transaction            " << endl;
	cout << "6 - Exit the store                       " << endl;

	cin.clear();
	fflush(stdin);
	cin >> menuSelection;

	return menuSelection;
}



int main(int argc, char ** argv)
{
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL){ MoveWindow(hwnd, 260, 150, 880, 750, TRUE); }


	Store loadScreen;
	TransactionManager my_bucket;
	Inventory& my_stock = my_bucket.GetInventory();
	//Inventory something;
	if (argc == 2)
	{
		loadScreen.Load(argv[1]);

	}
	else
	{
		loadScreen.Load("items.shp");
	}
	loadScreen.Display();
	cout << "\n Weight: " << my_stock.GetWeight() << "\t\t\t" << " Coins: " << my_stock.GetCoins() << "\n";
	int selection = menu();
	char user_ch;

// Menu defination
	do{
		switch (selection)
		{
		case 1:
		{
			system("cls");
			cout << "How would you like to sort?" << endl;
			cout << "A - Sort by type   " << endl;
			cout << "B - Sort by name   " << endl;
			cout << "C - Sort by price  " << endl;
			cout << "D - Sort by Weight " << endl;
			cout << "R - Return to main menu " << endl;
			cin.clear();
			fflush(stdin);
			cin >> user_ch;

			if (user_ch == 'A' || user_ch == 'a')
			{
				system("cls");
				loadScreen.SortByType();
				loadScreen.Display();
				Sleep(2900);
			}
			else if (user_ch == 'B' || user_ch == 'b')
			{
				system("cls");
				loadScreen.SortByName();
				loadScreen.Display();
				Sleep(2900);
			}
			else if (user_ch == 'C' || user_ch == 'c')
			{
				system("cls");
				loadScreen.SortByPrice();
				loadScreen.Display();
				Sleep(2900);
			}
			else if (user_ch == 'D' || user_ch == 'd')
			{
				system("cls");
				loadScreen.SortByWeight();
				loadScreen.Display();
				Sleep(2900);
			}
			else if (user_ch == 'R' || user_ch == 'r')
			{
				system("cls");
				loadScreen.Display();
				cout << "\n Weight: " << my_stock.GetWeight() << "\t\t\t" << " Coins: " << my_stock.GetCoins() << "\n";
				selection = menu();
			}
		}
			break;

		case 2:
		{
			char user[32];
			Item obj;
			system("cls");
			loadScreen.Display();
			cout << "\nWhat item would you like to search ?\n";
			cin >> user;
			loadScreen.Search(user, obj);
			cout << "The item " << user << " you are looking for is available at our store.\n\n";
			Sleep(100);
			cout << "Would you like to continue your search ?" << endl;
			char ans;
			for (;;)
			{
				if (cin >> ans && ans == 'Y' || ans == 'y')
				{
					system("cls");
					break;
				}
				else if (ans == 'N' || ans == 'n')
				{
					system("cls");
					loadScreen.Display();
					cout << "\n Weight: " << my_stock.GetWeight() << "\t\t\t" << " Coins: " << my_stock.GetCoins() << "\n";
					selection = menu();
				}
			}
		}
			break;
		case 3:
		{
			system("cls");
			loadScreen.Display();
			my_bucket.Buy();
			system("cls");
			my_stock.Display();
			cout << "\n\n\nThe item is added to your inventory.\n\n";
			cout << "Would you like to continue your purchase ?" << endl;
			char ans;
			for (;;)
			{
				if (cin >> ans && ans == 'Y' || ans == 'y')
				{
					system("cls");
					break;
				}
				else if (ans == 'N' || ans == 'n')
				{
					system("cls");
					loadScreen.Display();
					cout << "\n Weight: " << my_stock.GetWeight() << "\t\t\t" << " Coins: " << my_stock.GetCoins() << "\n";
					selection = menu();
					break;
				}
			}
		}
			break;

		case 4:
		{
			system("cls");
			my_stock.Display();
			my_bucket.Sell();
			cout << "\nThe item is removed from your inventory\n\n";
			cout << "Would you like to continue your sell ?" << endl;
			char ans;
			for (;;)
			{
				if (cin >> ans && ans == 'Y' || ans == 'y')
				{
					system("cls");
					break;
				}
				else if (ans == 'N' || ans == 'n')
				{
					system("cls");
					loadScreen.Display();
					cout << "\n Weight: " << my_stock.GetWeight() << "\t\t\t" << " Coins: " << my_stock.GetCoins() << "\n";
					selection = menu();
				}
			}
		}
			break;
		case 5:
		{
			system("cls");
			my_bucket.Undo();
			Sleep(1500);
			system("cls");
			loadScreen.Display();
			selection = menu();
		}
			break;
		case 6:
		{
			cout << "Would you really like to exit" << endl;
			char ans;
			for (;;)
			{
				if (cin >> ans && ans == 'Y' || ans == 'y')
				{
					cout << "Thank You, for shopping with us!" << endl;
					Sleep(1500);
					 return 0;
				}
				else if (ans == 'N' || ans == 'n')
				{
					system("cls");
					loadScreen.Display();
					cout << "\n Weight: " << my_stock.GetWeight() << "\t\t\t" << " Coins: " << my_stock.GetCoins() << "\n";
					selection = menu();
				}
			}
		}

		}
	} while (selection != 0);
	
	system("pause");
	//(console, r.left, r.top, r.right - r.left, r.bottom - r.top, TRUE);
	return 0;
}
