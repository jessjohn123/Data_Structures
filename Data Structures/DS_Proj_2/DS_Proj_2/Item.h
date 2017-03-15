#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
using namespace std;

#define WIDTH 60
#define HEIGHT 50

struct Item
{
	char type[16];
	char name[16];
	unsigned int cost;
	unsigned int weight;
	bool operator==(const Item& rhs);
};
