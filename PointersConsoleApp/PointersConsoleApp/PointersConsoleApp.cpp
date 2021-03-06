// PointersConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int val = 1;
int val2 = 2;
int* valPtr = &val;
int& valRef = val;

void PrintVals() {
	std::cout << "Values:" << std::endl;
	std::cout << "val: " << val << " val2: " << val2 << " valPtr: " << *valPtr << " valRef: " << val << std::endl;
	std::cout << "Addresses:" << std::endl;
	std::cout << "val: " << &val << " val2: " << &val2 << " valPtr: " << valPtr << " valRef: " << &val << std::endl;

}

int main()
{
	PrintVals();
	
	std::cout << "valPtr will now point to val2..." << std::endl;
	valPtr = &val2;

	PrintVals();

	std::cout << "valPtr will now have a  value of 3..." << std::endl;
	*valPtr = 3;

	PrintVals();

	std::cout << "valRef will now have a value of 4" << std::endl;
	valRef = 4;

	PrintVals();

    return 0;
}

