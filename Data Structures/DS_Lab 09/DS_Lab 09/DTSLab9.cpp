////////////////////////////////////////////////////////////////////////////////////////////////
// File :			Lab 9 Test.cpp
// Author :			Rodney Stoeffler
// Last Modified :	06.09.09
// Purpose :		Driver Program for the Huffman Utilities.
// Notes :			Property of Full Sail University, Data Structures Course.
//					DON'T CHANGE THIS FILE. change your code if something is not working
//					Program Output should match the Lab Document
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// LEAK DETECTION
////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
using namespace std;
#include "HuffmanDef.h"			// Include for provided HuffmanDef header.
#include "HuffmanUtils.h"		// Include for provided HuffmanUtils header.

////////////////////////////////////////////////////////////////////////////////////////////////
// REDUNDANT INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////
#include "HuffmanDef.h"			// Include for provided HuffmanDef header.
#include "HuffmanUtils.h"		// Include for provided HuffmanUtils header.

////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTANTS
////////////////////////////////////////////////////////////////////////////////////////////////
#define INPUTFILE "L9input.txt"
#define OUTPUTFILE "L9output.bin"

////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	main
// Parameters : argc - the number of command line arguments
//				argv - the array of command line arguments
// Return :		int - 0 for success
////////////////////////////////////////////////////////////////////////////////////////////////
int main (int argc, char ** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
// this function call will set a breakpoint at the location of a leaked block
// set the parameter to the identifier for a leaked block
	//_CrtSetBreakAlloc(1028);

////////////////////////////////////////////////////////////////////////////////////////////////
// LAB 9
////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "**********************************************************************\n";
	cout << "**                              LAB 9:                              **\n";
	cout << "**********************************************************************\n\n";

	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 1 - GenerateFrequencyTable function test
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "*** TEST 1 ***\n";
	cout << "Get a Frequency Table from the Huffman Utility for l8input.txt...\n";
	unsigned int *freqTable = generateFrequencyTable (INPUTFILE);
	showFrequencyTable (freqTable);
	cout << '\n';
	
	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 2 - generateLeafList and generateHuffmanTree function tests
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "*** TEST 2a ***\n";
	cout << "Create the list of starting Huffman Nodes (eventual Leaf Nodes)...\n";
	vector<HuffNode *> leafList = generateLeafList (freqTable);
	cout << "*** TEST 2b ***\n";
	cout << "Now create a Huffman Tree from the Huffman Utility...\n";
	HuffNode *huffTree = generateHuffmanTree (leafList);
	showHuffmanTree (huffTree);
	cout << '\n';
	
	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 3 - generateEncodingTable function test
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "*** TEST 3 ***\n";
	cout << "Next, make an Encoding Table from the Huffman Utility...\n";
	vector<int> *encodingTable = generateEncodingTable (leafList);
	showEncodingTable (encodingTable);
	cout << '\n';
	
	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 4 - writeHuffmanFile test
	/////////////////////////////////////////////////////////////////////////////////////////////
	cout << "*** TEST 4 ***\n";
	cout << "Finally, write a complete Huffman File...\n";
	writeHuffmanFile (INPUTFILE, OUTPUTFILE, freqTable, encodingTable);
	showHuffmanFileStream (OUTPUTFILE);

	// Shutdown
	cleanup (freqTable, huffTree, encodingTable);
	
	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 5 - Decode
	/////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 5 ***\n";
	cout << "decode a Huffman File...\n";
	decodeHuffmanFile("encoded.bin", "decoded.txt");

	ifstream decoded("decoded.txt");

	while(true)
	{
		char buffer;
		decoded.read(&buffer, 1);

		if(decoded.eof())
			break;
		cout << buffer;
	}

	decoded.close();
	cout << '\n';
	
	////////////////////////////////////////////////////////////////////////////////////////////
	// Complete
	////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}