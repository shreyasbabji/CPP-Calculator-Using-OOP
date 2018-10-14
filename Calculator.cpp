#include<iostream>
#include "Calculator.h"
#include<cstdlib>
#include<string>
#include<cmath>


using namespace std;

// Constructors
Calculator::Calculator()
{
	operand_one = 0;
	operand_two = 0;
	resVal = 0;

}
//destructor
Calculator::~Calculator()
{

}
//overlaod >> operator
istream& operator >>(istream& instr, Calculator& cal){
	cal.expression(cal);
	return instr;
}
//compute expression
void Calculator::expression(Calculator& inputCalc) {
	char peekedChar;
	double temp;
	string tempStr;
	string str;

	cin >> ws;												//skip whitesapce
	peekedChar = cin.peek(); 								//peek at the next value on the stream


	while(peekedChar =='.')
	{														//if it is . then exit as per the program
		return;
	}

	try 															//try block starts here
	{
		cin >> ws;
		peekedChar = cin.peek(); 									//same value peeked as before

		while(peekedChar == '(') 									//if the first value peeked is a bracket
		{
			resVal = inputCalc.term(inputCalc); 						//go to this function and return the value to vaALue.
			break;
		}
		if(isdigit(peekedChar))
		{
			cin >> temp; 											//read the whole term and put it to operand_one
			inputCalc.operand_one = temp;
			cin >> ws;												//skip whitespace
			peekedChar = cin.peek();  								// peek what is next

			//***for case 42 = ****8
			while(peekedChar == '=')
			{
				getline(cin,str,'=');  						//get the input upto =
				tempStr = str;
				throw inputCalc.operand_one;;  						//throw exception if theres any error. here we are throwing double value.
			}

			cin>>inputCalc.symbol; 		 						//take symbol to symbol bcz if theres no equal sign, it ll be an operator +/-*

			temp = inputCalc.term(inputCalc); 				 			//send to get term and put in operand_two

			inputCalc.operand_two = temp;

			while(temp == 0)									//when second operator is 0 for division
			{
				if(inputCalc.symbol == '/')
				{
					string s;
					getline(cin,s); 	//division error
					throw string("***** Division by zero\n"); //throw error
				}
				break;
			}
			inputCalc.result(inputCalc);										//perform operation and return value in variable "resval"
		}

		cin >> ws; //skip space
		peekedChar = cin.peek();
		cin>>peekedChar;

		while(peekedChar == '=')											//if last character in the input expression is = then print result value
		{
			cout<<inputCalc.resVal<<"\n";
			break;
		}
		cout << endl;
		cout << endl;
	}
	catch(char wrongVal) 											//catch from operand_one and operand_two if theres any other character then print error. I
	{
		cout<<"***** Unexpected error\n"<< wrongVal <<endl;
		cout<<endl;
		cout << endl;
	}



	catch(double finalAns){ //catch final result
		cout<<finalAns<<endl<< endl;
	}
	catch(string str) //catch errors
	{
		cout << str << endl;
	}
}



double Calculator::term(Calculator& cal) throw(string, double){
	double temp;
	char peekedChar;
	char tempChar;
	string t;
	int bracesCount=0;
	char tempone;
	char temptwo;
	Calculator tempCal;
	Calculator tempOne,tempTwo;								//two objects if there are multiple terms like in the denominator
	cin>>ws; 											//skipe space
	peekedChar = cin.peek();
	if(peekedChar =='(') 								//if bracket
	{
		cin >> tempChar; 								//put it in q
		peekedChar = (cin>>ws).peek();
		 										///peek again
		if(peekedChar =='(')
		{ 														//if multiple bracket send to out function.

			do{
				cin >> ws;
				tempone = cin.peek();
				while(tempone=='(')
				{
					cin>>temptwo;
					++bracesCount;
					break;
				}
				while(tempone ==')')
				{
					cin>>temptwo;
					--bracesCount;
					break;
				}
				while(isdigit(tempone))
				{
					cin>>tempCal.operand_one;
					cal.operand_one = tempCal.operand_one;
					break;
				}
				cin>>temptwo;
			}while(bracesCount!=0);

			getline(cin,t,'=');
			throw cal.operand_one; //throw double value

		}
		cin>>tempOne.operand_one; 									//no multiple brackets -> set operand_one of object
		cin >> ws;

		if(cin.peek() ==')')
		{
			cin.get(peekedChar);												//if closing bracket is present, it means only ONE term is present
		}
		cin >> ws;
		peekedChar = cin.peek();
		if((peekedChar == '%')||(peekedChar == '*')||(peekedChar == '-')||(peekedChar == '/')||(peekedChar == '+')) //if peeked symbol are these
		{
			cin>>tempOne.symbol; //store the symbol
		}
		else
		{
			string s;
			getline(cin,s);
			cout<<tempOne.operand_one<<"\n";						//anytthing other than +/-* symbol after ) is an error.
																//if no error move on and check next term. print operand bcz of case (5)) + 2  which shud print 5 and then display error
			throw string("***** Unexpected ) \n");
		}

		peekedChar = (cin>>ws).peek();
		if(peekedChar == '(')											//( means beginning of second term in denomintor
		{
			tempOne.operand_two = tempOne.factor(tempOne);					//call function factor to get second term which is inside first term
			cin >> ws;
			peekedChar = cin.peek();

			while(peekedChar != ')')
			{
				string s;
				getline(cin,s);
				throw string("***** Missing ) \n"); //throw error when one bracket is missing
				break;
			}

			cin>>peekedChar;												//take ) after peeking
			temp = tempOne.result(tempOne);							//obtain sol

			return temp;
		}
		else
			cin >> tempTwo.operand_one;

		tempOne.operand_two = tempTwo.operand_one;
		cin >> ws;
		peekedChar = cin.peek();
		if(peekedChar == '*' ) //if char is * then stor symbol and operand 2

		{
			cin >> tempTwo.symbol;
			cin >> tempTwo.operand_two;
		}

		cin >> ws;

		if(cin.peek()==')')
		{

			cin.get(tempChar);
		}


		if((tempOne.symbol=='-') && (tempTwo.symbol=='*'))							//for case 5/(6 - 2*3) =
		{
			tempTwo.operand_two = tempTwo.result(tempTwo);

		}

		temp = tempOne.result(tempOne);											//for case 2*(42 - 42e-1) where thr is only one symbol that is minus -      //***(42E-1 is not -. So only 1 minus)
	}
	else
	{
		cin >> tempOne.operand_two;
		temp = tempOne.operand_two;
	}
	return temp;
}

//functoin to evaluate factor
double Calculator::factor(Calculator& cal){
	char tempChar;
	Calculator tempOne; // create temporary object
	istream& is =  cin>>ws;
	if(is.peek()=='(')
	{
		cin>>tempChar;
		tempOne.resVal=tempOne.factor(tempOne); //recursive funtion to find value
		cin>>ws;
		cin>>tempChar;
	}
	else
	{
		//else take all the remaining values and symbols to compute the value of factor
		cin>>tempOne.operand_one;
		cin>>tempOne.symbol;
		cin>>tempOne.operand_two;
		tempOne.resVal=tempOne.result(tempOne);
		cal.operand_two = tempOne.resVal;
	}
	return tempOne.resVal;
}

//calculate final result of various operations
double Calculator::result(Calculator& cal) throw(string){
//calculate as per the operators
	string s;
	if(symbol=='+'){
		cal.resVal=cal.operand_one+cal.operand_two;
	}
	else if(symbol=='-'){
		cal.resVal=cal.operand_one-cal.operand_two;
	}
	else if(symbol=='*'){
		cal.resVal=cal.operand_one*cal.operand_two;
	}
	else if(symbol=='/'){
		cal.resVal=cal.operand_one/cal.operand_two;
	}
	else {
		getline(cin,s,'=');
		throw string("***** Unexpected %\n");
	}
	return cal.resVal;
}

