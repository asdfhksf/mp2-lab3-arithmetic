#include "arithmetic.h"

extern bool C;

void main()
{
	string Ex, *ML;
	Stack<string> st_OS;
	double Res;

	//string str1 = "hello, dolly", str2 = "dolly";
	//int k = str1.find(str2.c_str() + 2, 1, 2);
	//int k2 = str1.find(str2.substr(2, 2), 1);

	do
	{
		C = false;

		//cout << "Enter the expression" << endl;
		//getline(cin, Ex);

		Ex = "-(((2^3)! - 10^2/234) * 3!)^(-1/10) + a";
		cout << Ex << endl;

		Check(Ex);

	} while (C == true);

	st_OS = To_Postfix_Not(ML, EXtoML(Unary_Minus(Ex), ML));
	cout << "Postfix notation" << endl << st_OS << endl << endl;

	Res = Stack_Machine(st_OS, st_OS.Amount_Elemnts());
	cout << endl << Res;

	cout << endl;
}