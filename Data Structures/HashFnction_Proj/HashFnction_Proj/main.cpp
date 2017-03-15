#include <iostream>
#include <ctime>
#include <string>
#include <conio.h>
#include "HTable.h"
#include <fstream>
#include "DTSTimer.h"
#include "Boggle.h"
#include <stdlib.h>

using namespace std;

unsigned int hashFunc(const string& v);
void loadingFile(HTable<string>*& word_table);



int main(int argc, char ** argv)
{
	srand((unsigned int)time(NULL));

	HTable<string>* dictionary;
	loadingFile(dictionary);

	Boggle game;
	game.SetHashFunc(dictionary);
	game.Play();

	system("pause");
	return 0;
}
unsigned int hashFunc(const string& v)
{
	unsigned int h = 0;
	const int len = v.length();
	for (int i = 0; i < len; i++)
	{
		h = h * i + v[i];
	}
	return h % NUMBUCKETS;

}
void loadingFile(HTable<string>*& word_table)
{
	word_table = new HTable<string>(NUMBUCKETS, hashFunc);
	string letters;
	fstream fin;
	fin.open("engldict.txt", ios_base::in);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> letters;
			if (letters.length() >= 3 && letters.length() <= 16)
			{
				if (strchr(letters.c_str(), '\''))
				{
					fin.ignore(INT_MAX, '\n');
				}
				else
				{
					word_table->insert(letters);
				}
			}
		}
		fin.close();
	}
	word_table->printSomeStuff();
}
