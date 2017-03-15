#pragma once
#include "iostream"
#include "Graph.h"
#include "HTable.h"
#include <Windows.h>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "DTSTimer.h"
#include "BST.h"
#include <conio.h>

#define NUMBUCKETS 1033

using namespace std;

struct PlayerInfo
{
	char name[32];
	int score;
};
class Boggle
{
private:
	char alphabets;
	Graph<char>obj;
	HTable<string>*object;
	string userInput;
	char nameOfThePlayer[32];
	int scores = 0;
	int frame = 0;
	
	BST<string> containor;

public:
	//char grid[4][4];
	Boggle();
	bool Boggle::userFindMatch(string str);
	int getScore() const { return scores; }
	void setScore(int _scores) { scores = _scores; }
	const char* const GetName() const{ return nameOfThePlayer; }
	//void SetName(const char* const _name) { nameOfThePlayer = _name; }
	int factorialScore();
	bool Boggle::RecurFunc(string str, int inG, int inStr);
	void SetHashFunc(HTable<string>*hashFunc) { object = hashFunc; }

	void Play();
	void Render();
	void HighScores();
	void MainMenu();
};



Boggle::Boggle()
{
	char defaultGrid[16] = { 'a', 'r', 'l', 'w', 'i', 't', 'o', 's', 'e', 'n', 's', 't', 'w', 'p', 'k', 'j' };
	char vowels[5] = { 'a', 'e', 'i', 'o', 'u' };
	int count = 0;

	/*do
	{
		count = 0;
		for (int i = 0; i < 16; i++)
		{
			alphabets = rand() % 25 + 97;
			obj.addVertex(alphabets);

			for (int i = 0; i < 5; i++)
			{
				if (alphabets == vowels[i])
				{
					count += 1;
				}
			}

		}
	} while (count < 4);*/
	
	for (int i = 0; i < 16; i++)
	{
		obj.addVertex(defaultGrid[i]);
	}

	obj[0].addEdge(1);
	obj[0].addEdge(4);
	obj[0].addEdge(5);

	
	obj[1].addEdge(0);
	obj[1].addEdge(4);
	obj[1].addEdge(5);
	obj[1].addEdge(6);
	obj[1].addEdge(2);

	
	obj[2].addEdge(1);
	obj[2].addEdge(5);
	obj[2].addEdge(6);
	obj[2].addEdge(7);
	obj[2].addEdge(3);

	
	obj[3].addEdge(2);
	obj[3].addEdge(6);
	obj[3].addEdge(7);

	
	obj[4].addEdge(0);
	obj[4].addEdge(1);
	obj[4].addEdge(5);
	obj[4].addEdge(9);
	obj[4].addEdge(8);

	
	obj[5].addEdge(0);
	obj[5].addEdge(1);
	obj[5].addEdge(2);
	obj[5].addEdge(4);
	obj[5].addEdge(6);
	obj[5].addEdge(8);
	obj[5].addEdge(9);
	obj[5].addEdge(10);
	
	
	obj[6].addEdge(1);
	obj[6].addEdge(2);
	obj[6].addEdge(3);
	obj[6].addEdge(5);
	obj[6].addEdge(7);
	obj[6].addEdge(9);
	obj[6].addEdge(10);
	obj[6].addEdge(11);

	
	obj[7].addEdge(2);
	obj[7].addEdge(3);
	obj[7].addEdge(6);
	obj[7].addEdge(10);
	obj[7].addEdge(11);

	
	obj[8].addEdge(4);
	obj[8].addEdge(5);
	obj[8].addEdge(9);
	obj[8].addEdge(12);
	obj[8].addEdge(13);

	
	obj[9].addEdge(4);
	obj[9].addEdge(5);
	obj[9].addEdge(6);
	obj[9].addEdge(8);
	obj[9].addEdge(10);
	obj[9].addEdge(12);
	obj[9].addEdge(13);
	obj[9].addEdge(14);

	
	obj[10].addEdge(5);
	obj[10].addEdge(6);
	obj[10].addEdge(7);
	obj[10].addEdge(9);
	obj[10].addEdge(11);
	obj[10].addEdge(13);
	obj[10].addEdge(14);
	obj[10].addEdge(15);

	
	obj[11].addEdge(6);
	obj[11].addEdge(7);
	obj[11].addEdge(10);
	obj[11].addEdge(14);
	obj[11].addEdge(15);

	
	obj[12].addEdge(8);
	obj[12].addEdge(9);
	obj[12].addEdge(13);

	
	obj[13].addEdge(8);
	obj[13].addEdge(9);
	obj[13].addEdge(10);
	obj[13].addEdge(12);
	obj[13].addEdge(14);

	
	obj[14].addEdge(9);
	obj[14].addEdge(10);
	obj[14].addEdge(11);
	obj[14].addEdge(13);
	obj[14].addEdge(15);

	
	obj[15].addEdge(10);
	obj[15].addEdge(11);
	obj[15].addEdge(14);
}

void Boggle::Render()
{
	for (int i = 0; i < 16; i++)
	{
		if (i % 4 == 0)
		{
			cout << endl;
		}
		cout << obj[i].element << ' ';
	}

}




bool Boggle::userFindMatch(string str)
{
	
	// twice word make bst serch or find function.
	if (containor.find(str))
	{
		return false;
	}
	unsigned int i;
	if (object->find(str) != -1)
	{
		for (i = 0; i < obj.size(); i++)
		{
			if (obj[i].element == str[0])
			{
				RecurFunc(str,i,1);
				
				containor.insert(str);

				if (RecurFunc(str, i, 1))
				{
					factorialScore();
					return true;
				}
			}
			
		}
		return true;
	}
	return false;
}

bool Boggle::RecurFunc(string str, int inG, int inStr)
{
	//inG = points in the grid, inStr = points in the user's word
	SLLIter<Graph<char>::Edge>iter(obj[inG].edges);
	for (iter.begin(); !iter.end(); ++iter)
	{
		if (obj[iter.current().toVertex].element == str[inStr])
		{
			return RecurFunc(str, iter.current().toVertex, inStr + 1);
		}
	}
}

int Boggle::factorialScore()
{
	int wordlen = userInput.size();
	int factorial = 1;
	for (int i = wordlen; i > 1; i--)
	{
		factorial *= i;
	}
	setScore(getScore() + factorial);
	return factorial;
}


void Boggle::Play()
{
	DTSTimer bob;
	bool check = false;

	MainMenu();
	system("cls");

	bob.reset();

	while (bob.getElapsedTime() < 60000)
	{
		//LockWindowUpdate(GetConsoleWindow());
		system("cls");
		cout << "Stop Watch: " << 60 - bob.getElapsedTime() / 1000;
		cout << "\t\t\tPlayer: " << GetName();
		cout << "\t\t\t     Scores: " << getScore();
		cout << "\n\nBOGGLE GAME\n";
		Render();
		cout << endl << endl;
		cout << "Enter the words you think can be made out of the grid above: \n";
		cout << userInput;
		
		if (check == true)
		{
			cout << "\n\nYou guessed in a correct word, you get a big thumbsUp!\n";
		}

		//LockWindowUpdate(NULL);
		// 1 - get user input
		if (_kbhit())
		{
			char ch = _getch();

			if (-32 == ch)
				_getch();

			// did the user press a-z?
			else if (isalpha(ch))
			{
				userInput += tolower(ch);
			}

			if (ch == 13)
			{
				check = userFindMatch(userInput);
				system("cls");
				userInput = "";
			}

			if (ch == 8)
			{
				userInput.pop_back();
			}
			if (ch == 27)
			{
				return;
			}
		}
	}	
	HighScores();
}

void Boggle::MainMenu()
{
	cout << "WELCOME TO\n";
	char ascii_art[5][40] = { { " ____   __    ___   ___  __    ____" },
							  { "(  _ \\ /  \\  / __) / __)(  )  (  __)" },
							  { " ) _ ((  O )( (_ \\( (_ \\/ (_/\\) _) " },
							  { "(____/ \\__/  \\___/ \\___/\\____/(____)" },};
	
	
	for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				cout << ascii_art[i][j];
				
			}
			cout << endl;
		}
	for (;;)
	{
		cout << "Please enter in your name: ";
			if (cin.get(nameOfThePlayer, 32) && strlen(nameOfThePlayer) > 3)
			{
				cin.sync();
				break;
			}
			else if (strlen(nameOfThePlayer) <= 3)
			{
				strcpy_s(nameOfThePlayer, 32, "Player");
				cin.clear();
				cin.sync();
				break;
			}
	}
}


void Boggle::HighScores()
{
	system("cls");
	unsigned int i = 0;
	PlayerInfo pl_info;
	vector<PlayerInfo> gamedata;

#pragma region Saving out in Binary File
#if 1
	//Actual Player
	pl_info.score = getScore();
	strcpy_s(pl_info.name, 32, GetName());
	gamedata.push_back(pl_info);

	fstream fout;
	fout.open("Scores.txt",ios_base::out);
	if (fout.is_open())
	{
		for (; i < gamedata.size(); i++){
			fout << "Player" << gamedata[i].name << " scored" << gamedata[i].score;
		}
			fout.close();
	}
#endif
}
	
