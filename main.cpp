#include "Calculator.h"
#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>

using namespace std;

int main()

{
	Calculator tempCalc; //object created to be used in program
	char tempChar;
	do
	{
		cout<<"Expression? ";
		cin >> ws;
		tempChar = cin.peek();
		cin >> tempCalc;
	}while( tempChar != '.');
	cout << "Done! \n";
	cout <<endl;
}

