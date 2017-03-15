#pragma once
#include "HuffmanDef.h"
#include "BitStream.h"
#include <vector>
#include <fstream>

struct compare
{
	bool operator() (const HuffNode * a, const HuffNode * b)
	{
		return (a->freq > b->freq);
	}
};

unsigned int* generateFrequencyTable(const char* filepath)
{
	unsigned int *arr = new unsigned int[257];
	for (int i = 0; i < 257; i++)
	{
		arr[i] = 0;
	}
	char buffer;
	ifstream infile;
	infile.open(filepath);
	if (infile.is_open())
	{
		for (;;)
		{
			infile.read(&buffer, 1);
			if (infile.eof())
			{
				break;
			}
			arr[int(buffer)]++;
			arr[256]++;
		}
	}
	return arr;
}

vector<HuffNode*> generateLeafList(unsigned int* freqTable)
{
	vector<HuffNode*> obj;

	for (int i = 0; i < 256; i++)
	{
		if (freqTable[i] != 0)
		{
			HuffNode* node = new HuffNode();
			node->parent = nullptr;
			node->left = nullptr;
			node->right = nullptr;
			node->freq = freqTable[i];
			node->value = i;
			obj.push_back(node);
		}
	}
	return obj ;
}

HuffNode* generateHuffmanTree(vector<HuffNode*>& leafList)
{
	priority_queue<HuffNode*, vector<HuffNode*>, compare> object;
	for (unsigned int i = 0; i < leafList.size(); i++)
	{
		object.push(leafList[i]);
	}
	while (object.size() > 1)
	{
		HuffNode* parent = new HuffNode();
		HuffNode* top1;
		HuffNode* top2;
		top1 = object.top();
		top1->parent = parent;
		object.pop();
		top2 = object.top();
		top2->parent = parent;
		object.pop();
		parent->left = top1;
		parent->right = top2;
		parent->value = -1;
		parent->freq = top1->freq + top2->freq;
		object.push(parent);
	}
	return object.top();
}

vector<int>* generateEncodingTable(vector<HuffNode*>& leafList)
{
	vector<int>*obj = new vector<int>[256];
	for (unsigned int i = 0; i < leafList.size(); i++)
	{
		HuffNode* curr = leafList[i];
		while (curr->parent != nullptr)
		{
			if (curr->parent->left == curr)
				obj[leafList[i]->value].push_back(0);
			else if (curr->parent->right == curr)
				obj[leafList[i]->value].push_back(1);

			curr = curr->parent;
		}
		reverse(obj[leafList[i]->value].begin(), obj[leafList[i]->value].end());
	}
	return obj;
}

void writeHuffmanFile(const char* inputFilePath, const char* outputFilePath,
	unsigned int* freqTable, vector<int>* encodingTable)
{
	BitOStream file(outputFilePath, (char *)freqTable, 1028);

	fstream fin;
	fin.open(inputFilePath, ios_base::in);
	if (fin.is_open())
	{
		char readchars;
		while (!fin.eof())
		{
			fin.get(readchars) ;
			file << encodingTable[readchars];
		}
	}
	fin.close();
}

void helperFunc(const HuffNode* p)
{
	if (p != nullptr)
	{
		helperFunc(p->left);
		helperFunc(p->right);
		delete p;
	}
}

void cleanup(unsigned int* freqTable, HuffNode* huffTree, vector<int>* encodingTable)
{
	helperFunc(huffTree);
	delete [] encodingTable;
	delete [] freqTable;
	
}

void decodeHuffmanFile(const char* inputFilePath, const char* outputFilePath)
{
	fstream fout;
	fout.open(outputFilePath, ios_base::out);

	if (fout.is_open())
	{
		unsigned int* freqTable = new unsigned int[257];
		BitIStream file(inputFilePath, (char *)freqTable, 1028);
		vector<HuffNode*> newLeafList = generateLeafList(freqTable);
		HuffNode* pointerToRoot = generateHuffmanTree(newLeafList);

		HuffNode* curr = pointerToRoot;
		int readInNum;

		for (unsigned int i = 0; i < freqTable[256];)
		{
			file >> readInNum;
			if (readInNum == 0)
			{
				curr = curr->left;
			}
			else if (readInNum == 1)
			{
				curr = curr->right;
			}
			if (curr->value != -1)
			{
				fout.write((char*)&curr->value, 1);
				curr = pointerToRoot;
				i++;
			}
		}
		cleanup(freqTable, pointerToRoot, NULL);
	}
}