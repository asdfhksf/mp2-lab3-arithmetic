#include "arithmetic.h"

void main()
{
	string Ex, *ML;
	Stack<string> st_OS;
	double Res;
	bool C;

	cout << "Supported operators: + - * / ^ ! \\ %" << endl; 
	cout << "Supported functions:" << endl;
	cout << "sin() cos() tan() atan() sinh() cosh() tanh() atanh() asin() acos() asinh() acosh() ln()";
	cout << endl << endl << endl;

	do
	{
		C = false;

		//cout << "Enter the expression" << endl;
		//getline(cin, Ex); 

		Ex = "(-(((2^3)! - 10^2/234) * 3!)^(-1/10) + a) % (b \\ 2)";
		//Ex = "tan(pi) + sin(pi) + cos(pi) + atan(pi) + sinh(pi) + cosh(pi) + tanh(pi) + atanh(1/2) + acos(1/2) + asin(1/2) + acosh(pi) + asinh(pi) + ln(e)";

		cout << Ex << endl;

		C = Check(Ex);

	} while (C == true);

	st_OS = To_Postfix_Not(ML, EXtoML(Unary_Minus(Ex), ML));
	cout << "Postfix notation" << endl << st_OS << endl << endl;

	Res = Stack_Machine(st_OS, st_OS.Amount_Elemnts());
	cout << endl << Res;

	cout << endl;
}