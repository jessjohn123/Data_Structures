////////////////////////////////////////////////////////////////////////////////////////////////
// File :			Lab 1 Test.cpp
// Author :			Rodney Stoeffler
//					RStoeffler@fullsail.com
// Created :		07.22.12
// Last Modified :	07.31.12
// Purpose :		Test Program for DTS Lab 1 - DynArray class
// Notes :			Property of Full Sail University, Data Structures(GDD 250).
//					DON'T CHANGE THIS FILE. change your code if something is not working
//					Program Output should match the Lab Document.
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
#include <string>
using namespace std;
#include "DynArray.h"		// Include the DynArray header.

////////////////////////////////////////////////////////////////////////////////////////////////
// MACROS
////////////////////////////////////////////////////////////////////////////////////////////////
#define CHALLENGE_ACCEPTED 0

////////////////////////////////////////////////////////////////////////////////////////////////
// the Data Structures data structure, data stored in a c++ structure
////////////////////////////////////////////////////////////////////////////////////////////////
class DTS
{
	string theString;
	int theInt;
	double theDouble;

public:
	DTS(const string s = "bad", const int i = 0xBADF00D, const double d = 38.00) : theString(s), theInt(i), theDouble(d){}
	friend ostream& operator<< (ostream& out, const DTS& v);
};

ostream& operator<< (ostream& out, const DTS& v)
{
	//out << v.theString << ' ' << v.theInt << ' ' << v.theDouble << '\n';
	// for this little test, let's just print out the double
	out << v.theDouble;
	return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	printDynArray
// Parameters : array - the array to print
// Return :		void
////////////////////////////////////////////////////////////////////////////////////////////////
template <typename Type>
void printDynArray(const DynArray<Type>& array)
{
	cout << "{ ";
	for (unsigned int i = 0; i < array.size(); ++i)
		cout << array[i] << ' ';
	cout << "} ";
	cout << "Size " << array.size ();
	cout << " Capacity " << array.capacity() << '\n';
}


////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	main
// Parameters : argc - the number of command line arguments
//				argv - the array of command line arguments
// return :		int - 0 for success
////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
// this function call will set a breakpoint at the location of a leaked block
// set the parameter to the identifier for a leaked block
	//_CrtSetBreakAlloc(495);

////////////////////////////////////////////////////////////////////////////////////////////////
// LAB 1
////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "**********************************************************************\n";
	cout << "**                              LAB 1:                              **\n";
	cout << "**********************************************************************\n\n";

	////////////////////////////////////////////////////////////////////////////////////////////
	// Declarations
	////////////////////////////////////////////////////////////////////////////////////////////
	DynArray<DTS> bob;
	DynArray<DTS> bobjr;
	DynArray<int> testArray;
	DynArray<int>* testPointer;
	DynArray<int> testCopy;
	DynArray<string> stringArray;
	string vals[] = {"0","4","8","12","16","20","24"};
	int i;

	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 1 - test the append function
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "*** TEST 1 ***\n";
	testArray.clear();
	printDynArray(testArray);
	for(i = 0; i < 28; i+=4)
	{
		testArray.append(i);
		printDynArray(testArray);
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 2 - test the reserve function - default behavior & attempt to make it smaller
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 2 ***\n";
	testArray.reserve();
	printDynArray(testArray);
	testArray.reserve(2);
	printDynArray(testArray);
	stringArray.reserve(4);
	printDynArray(stringArray);
	for(i = 0; i < 7; ++i)
	{
		stringArray.append(vals[i].c_str());
		printDynArray(stringArray);
	}
	

	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 3 - test the reserve function
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 3 ***\n";
	testArray.clear();
	testArray.clear();
	testArray.reserve(10);
	printDynArray(testArray);
	testArray.clear();

	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 4 - test overwrite behavior
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 4 ***\n";
	testArray.clear();
	testArray.append(1);
	testArray.append(2);
	testArray.append(3);
	testArray[3] = 4;
	testArray.append(5);
	printDynArray(testArray);

	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 5 - test the trilogy
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 5 ***\n";
	testPointer = new DynArray<int>;
	for(i = 0; i < 28; i+=4)
		testPointer->append(i);
	testCopy = *testPointer;
	delete testPointer;
	printDynArray(testCopy);
	testCopy.clear();
	printDynArray(testCopy);

	testPointer = new DynArray<int>;
	for(i = 0; i < 28; i+=4)
		testPointer->append(i);
	DynArray<int> testCpyCtr(*testPointer);
	delete testPointer;
	printDynArray(testCpyCtr);
	testCpyCtr.clear();
	printDynArray(testCpyCtr);

	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 6 - test default reserve behavior starting with an empty array
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 6 ***\n";
	testArray.clear();
	for(i = 0; i < 3; ++i)
	{
		printDynArray(testArray);
		testArray.reserve();
	}
	printDynArray(testArray);
	testArray.append(0);
	testArray.append(1);
	printDynArray(testArray);

	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 7 - test reserve behavior - append, reserve, then call append to add items
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 7 ***\n";
	testArray.clear();
	testArray.append(0);
	testArray.append(1);
	testArray.reserve();
	testArray.append(2);
	testArray.append(3);
	printDynArray(testArray);

	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 8 - more assignment love
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 8 ***\n";
	testCopy.clear();
	testArray.clear();
	for(i = 0; i < 28; i+=4)
		testArray.append(i);
	testCopy.append(i);
	printDynArray(testArray);
	printDynArray(testCopy);
	testArray = testCopy;
	printDynArray(testArray);

	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 9 - test for weirdness
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 9 ***\n";
	bob.append(DTS("one", 1, 1.1));
	bob.append(DTS("two", 2, 2.2));
	bob.append(DTS("three", 3, 3.3));
	bob.append(DTS("four", 4, 4.4));
	bob.append(DTS("five", 5, 5.5));
	bobjr = bob;
	printDynArray(bobjr);
	bob.clear();
	printDynArray(DynArray<DTS>(bobjr));

	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 10 - self-Assignment
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 10 ***\n";
	testArray.clear();
	for(i = 0; i < 28; i+=4)
		testArray.append(i);
	testPointer = &testArray;
	*testPointer = testArray;
	printDynArray(testArray);

////////////////////////////////////////////////////////////////////////////////////////////////
// CHALLENGE TESTS
////////////////////////////////////////////////////////////////////////////////////////////////
#if CHALLENGE_ACCEPTED

	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 11 - test insert behavior
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 11 ***\n";
	int x[3] = {1,2,3};
	testArray.clear();
	testArray.insert(5,1);
	testArray.insert(x, 3, 12);
	printDynArray(testArray);
	testArray.insert(99,0);
	printDynArray(testArray);
	for(int i = 28; i >= 0; i-=4)
	{
		testArray.insert(i, 0);
		printDynArray(testArray);
	}
	
	testArray.insert(x, 3, 1);
	printDynArray(testArray);

	////////////////////////////////////////////////////////////////////////////////////////////
	// Test 12 - test remove behavior
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n\n*** TEST 12 ***\n";
	testArray.remove(3,3);
	printDynArray(testArray);
	while(testArray.size() > 0)
	{
		testArray.remove(0);
		printDynArray(testArray);
	}
	testArray.remove(0);
	testArray.remove(0,5);

#endif

	////////////////////////////////////////////////////////////////////////////////////////////
	// Complete
	////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}