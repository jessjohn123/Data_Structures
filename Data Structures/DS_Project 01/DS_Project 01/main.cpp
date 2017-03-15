////////////////////////////////////////////////////////////////////////////////////////////////
// File :			main.cpp
// Author :			Rodney Stoeffler
// Created :		03.24.08
// Last Modified :	10.29.09
// Purpose :		The main driver for the memory game
// Notes :			Property of Full Sail University, Data Structures Course.
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>				// needed for drawing the screen
#include <conio.h>				// needed for _kbhit and _getch.
#include "MemoryFunctions.h"	// interface for drawing the screen and delay function
#include "DynArray.h"
#include <ctime>
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	main
// Parameters : argc - the number of command line arguments
//				argv - the array of command line arguments
// return :		int - 0 for success
////////////////////////////////////////////////////////////////////////////////////////////////

DynArray <char> obj;
char ch;

void countdown(int seconds)
{
	clock_t endcountdown;
	endcountdown = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endcountdown){}
}

void asciiArt()
{
	char titleScreen[50][18] = {
			{ "   .oOOOOOOo.    " },
			{ "  oOOOOOOOOOOo.  " },
			{ " OOOO'    'OOOO " },
			{ "OOOO'      'OOOO" },
			{ "OOOO       .OOOO" },
			{ "         .OOOO'" },
			{ "        .OOOO'" },
			{ "      .OOOO'" },
			{ "     .OOOO'" },
			{ "     OOOO'" },
			{ "     OOOO" },
			{ "     GGGG" },
			{ "        " },
			{ "        " },
			{ "    .OO." },
			{ "    OOOO" },
			{ "    'OO'" },
	};
	for (size_t i = 0; i < 50; i++)
	{
		for (size_t j = 0; j < 18; j++)
		{
			cout << titleScreen[i][j];
		}
			cout << endl;
			delay(100);
	}



}

void computerMove()
{

	char keypressed;
	
	//for (int i = 0; i < 5; i++)
	{
		int randvalue = rand() % 4;

		switch (randvalue)
		{
		case 0:
		{
			keypressed = 'W';
			obj.append(keypressed);
			break;
		}
		case 1:
		{
			keypressed = 'A';
			obj.append(keypressed);
			break;
		}
		case 2:
		{
			keypressed = 'S';
			obj.append(keypressed);
			break;
		}
		case 3:
		{
			keypressed = 'D';
			obj.append(keypressed);
			break;
		}
	
		}
	}
	
	for (unsigned int i = 0; i < obj.size(); i++)
	{

		switch (obj[i])
		{

		case 'W':
			drawUp();
			delay(100);
			empty();
			break;
		case 'S':
			drawDown();
			delay(100);
			empty();
			break;
		case 'A':
			drawLeft();
			delay(100);
			empty();
			break;
		case 'D':
			drawRight();
			delay(100);
			empty();
			break;
		}
	}
}


bool pl_choice = true;
void Replay()
{
	char userInput;
	for (;;)
	{
		cout << "Do you want to play again ?";
		if (cin >> userInput && userInput == 'Y' || userInput == 'y')
		{
			pl_choice = true;
			break;
			obj.clear();
		}
		else if (userInput == 'N' || userInput == 'n')
		{
			pl_choice = false;
			break;
		}
	}

}


void userMove()
{
	int counter = 0;
	int score = 0;
	bool IsScore = true;
	
	while (true)
	{
		//empty();
		if (IsScore == true)
		{

			system("cls");
			cout << '\n';
			cout << score;

			IsScore = false;
		}
		

		if (counter == obj.size())
			break;
		if (_kbhit())
		{
			ch = _getch();
			switch (toupper(ch))
			{
				// show stuff for each specific move
			case 'W':
			{
				if (obj[counter] == 'W')
				{ 
					counter++;
					drawUp();
					score += 50;
					IsScore = true;
					delay(150);
					empty();
					//break;
				}
				else
				{
					cout << "Game Over!" << endl;
					Replay();
				}
			}
				break;
			case 'S':
			{
				if (obj[counter] == 'S')
				{
					counter++;
					drawDown();
					score += 50;
					IsScore = true;
					delay(150);
					empty();
					//break;
				}
				else
				{
					cout << "Game Over!" << endl;
					Replay();
				}
			}
				break;
			case 'A':
			{
				if (obj[counter] == 'A')
				{
					counter++;
					drawLeft();
					score += 50;
					IsScore = true;
					delay(150);
					empty();
					//break;
				}
				else
				{
					cout << "Game over!" << endl;
					Replay();
				}
			}
				break;
			case 'D':
			{
				if (obj[counter] == 'D')
				{
					counter++;
					drawRight();
					score += 50;
					IsScore = true;
					delay(150);
					empty();
					//break;
				}
				else
				{
					cout << "Game over!" << endl;
					Replay();
				}
			}
				break;
			}

			if (pl_choice == true)
			{

				break;
			}
			// exiting test on the 'q' key
			if (ch == 'Q')
				break;
		}
	}
}



int main(int argc, char ** argv)
{


	int n;
	cout << "COUNT DOWN BEGINS\n";
	for (n = 10; n > 0; n--)
	{
		system("cls");
		cout << n << endl;
		countdown(1);

	}
	//cout << "Get Ready! \n";

	system("cls");
	asciiArt();

	//system("pause");

	   while(pl_choice)
	   {
		   
		   empty();
		   computerMove();
		   userMove();
	   }  

	   system("pause");
   // complete.
   return 0;

}

