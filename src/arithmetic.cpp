#include "arithmetic.h"

int fact(int n)
{
	int res = 1;

	if (n > 0)
	{
		for (int i = 1; i < n + 1; i++)
			res *= i;
		return res;
	}
	if (n == 0)
		return 1;
	else
		throw - 1;
}

bool Is_Elem(string str1, string str2, int pos)
{
	if ((str1[pos] == '\0'))
		return true;

	for (unsigned int j = 0; j < str2.length(); j++)
		if (str1[pos] == str2[j])
			return true;

	return false;
}
string Delete_Spaces(string str1)
{
	for (unsigned int i = 0; i < str1.length(); i++)
		if (str1[i] == ' ')
			str1.erase(i--, 1);

	return str1;
}
int* Positions(int *(&Pos), string str1, string str2)
{
	Pos = new int[str1.length()];

	Pos[0] = str1.find(str2[0]);
	for (unsigned int i = 1; i < str2.length(); i++)
		Pos[i] = str1.find(str2[i], Pos[i - 1] + 1);

	return Pos;
}

int EXtoML(string str1, string *(&str2))
{
	string tmp(str1), Op = "()+-*/^!\\%";
	unsigned int j = 0, i = 0;

	tmp = Delete_Spaces(tmp);

	str2 = new string[tmp.length()];

	j = 0;
	i = -1;
	while (j < tmp.length())
	{
		i++;
		while (!Is_Elem(tmp, Op, j))
		{
			str2[i] += tmp[j++];
		}
		if (j < tmp.length())
		{
			if (j != 0)
			{
				if (!Is_Elem(tmp, Op, j - 1)) i++;
				str2[i] += tmp[j++];
			}
			else
				str2[i] += tmp[j++];
		}
	}

	return i + 1;
}

bool Check_Correct_Characters(string str1)
{
	bool C = false;
	int pos = 0;
	string Trash = "@#$&_<>,?|;:{}'~`";

	for (unsigned int i = 0; i < str1.length(); i++)
	{
		if (Is_Elem(str1, Trash, i))
		{
			cout << "Unacceptable character:	" << str1[i] << endl;
			pos = str1.find(str1[i], pos);
			cout << "On " << pos << " position" << endl;
			C = true;
		}
	}
	//cout << endl;

	return C;
}
bool Check_Correct_Operators(string str1)
{
	bool C = false;
	string tmp(str1), Op = "+*/.^\\%";
	int *Pos = new int[str1.length()];

	tmp = Delete_Spaces(tmp);
	Pos = Positions(Pos, str1, tmp);

	if (Is_Elem(tmp, Op + "!"))
	{
		cout << "Operator at the beginning of the line" << endl;
		C = true;
	}

	for (unsigned int i = 0; i < tmp.length(); i++)
	{
		if (Is_Elem(tmp, Op + "-", i) && Is_Elem(tmp, Op + ")-", i + 1))
		{
			cout << "Two operators in a row:	" << tmp[i] << " and " << tmp[i + 1] << endl;
			cout << "On " << Pos[i] << " position" << endl;
			C = true;
		}
	}

	delete[] Pos;

	return C;
}
bool Check_Correct_Brackets(string str1)
{
	bool C = false;
	char b;
	string tmp(str1), l_brackets = "[(", r_brackets = ")]";
	Stack<char> brackets(tmp.length());

	for (unsigned int i = 0; i < tmp.length(); i++)
	{
		if (Is_Elem(tmp, l_brackets, i))
			brackets.Push(tmp[i]);

		if (Is_Elem(tmp, r_brackets, i))
		{
			try
			{
				b = brackets.Pop();
			}
			catch (int)
			{
				cout << "Closing brackets more" << endl;
				cout << "On " << i << " position" << endl;
				C = true;
				break;
			}
			if (((Is_Elem(tmp, ")", i) && ((b != '(')))) || ((Is_Elem(tmp, "]", i) && ((b != '[')))))
			{
				cout << "Opening and closing brackets of different types" << endl;
				cout << "On " << i << " position" << endl;
				C = true;
				break;
			}
		}
	}
	//cout << endl;

	if (!brackets.Empty())
	{
		cout << "Opening brackets more" << endl;
		C = true;
	}
	//cout << endl;

	return C;
}
bool Check_Correct_Operands(string str1)
{
	bool C = false;
	bool n = false, first = true;
	int a;
	string Op = "+-*/^!()[]\\%sincostanatansinhcoshtanhatanhasinacosasinhacoshln";
	
	for (unsigned int i = 0; i < str1.length(); i++)
	{
		if ((!Is_Elem(str1, Op + " ", i)) && (first))
		{
			first = false;
			n = true;
			a = i;
		}

		if (Is_Elem(str1, Op + ".", i))
		{
			n = false;
			first = true;
		}

		if ((!Is_Elem(str1, Op + " ", i)) && (n))
		{
			if ((i != 0) && (!Is_Elem(str1, "0123456789)", i - 1)) && (a != i))
			{
				cout << "Two operands in a row:	" << str1[a] << " and " << str1[i] << endl;
				cout << "On " << a << " position" << endl;
				C = true;
			}
		}
	}

	return C;
}
bool Check(string str1)
{
	bool C1, C2, C3, C4;

	C1 = Check_Correct_Brackets(str1);
	C2 = Check_Correct_Characters(str1);
	C3 = Check_Correct_Operators(str1);
	C4 = Check_Correct_Operands(str1);

	if (C1 || C2 || C3 || C4)
	{
		cout << endl << "Enter the correct expression" << endl << endl;
		return true;
	}
	else
	{
		cout << endl;
		return false;
	}
}

int Prior(string str1)
{
	if (str1 == "(")
		return 1;

	if ((str1 == "+") || (str1 == "-"))
		return 2;

	if (((str1 == "*") || (str1 == "/")) || ((str1 == "\\") || (str1 == "%")))
		return 3;

	if (str1 == "^")
		return 4;

	if (str1 == "!")
		return 5;

	if ((str1 == "sin") || (str1 == "cos") || (str1 == "tan") || (str1 == "atan") || (str1 == "sinh") || (str1 == "cosh") || (str1 == "tanh") || (str1 == "atanh") || (str1 == "asin") || (str1 == "acos") || (str1 == "asinh") || (str1 == "acosh") || (str1 == "ln"))
		return 6;
}
Stack<string> To_Postfix_Not(string *(&str1), int l)
{
	Stack<string> st1(l);
	Stack<string> Op(l);
	string OP = "+-*/^!\\%sincostanatansinhcoshtanhatanhasinacosasinhacoshln";
	
	for (int i = 0; i < l; i++)
	{
		if (!Is_Elem(str1[i], OP + "()"))
			st1.Push(str1[i]);

		if (Is_Elem(str1[i], "("))
			Op.Push(str1[i]);

		if (Is_Elem(str1[i], ")"))
		{
			while (Op.Peek() != "(")
				st1.Push(Op.Pop());
			Op.Pop();
		}

		if (Is_Elem(str1[i], OP))
		{
			while (!Op.Empty() && (Prior(str1[i]) <= Prior(Op.Peek())))
				st1.Push(Op.Pop());
			Op.Push(str1[i]);
		}
	}
	while (!Op.Empty())
		st1.Push(Op.Pop());

	return st1;
}
double Operator(string str1, double op1, double op2)
{
	if (str1 == "+")
		return op1 + op2;

	if (str1 == "-")
		return op1 - op2;

	if (str1 == "*")
		return op1 * op2;

	if (str1 == "/")
		return op1 / op2;

	if (str1 == "^")
		return pow(op1, op2);

	if (str1 == "!")
		return fact(op1);

	if (str1 == "\\")
		return ((int)(op1 / op2));

	if (str1 == "%")
		return (int)op1 % (int)op2;

	if (str1 == "sin")
		return sin(op1);

	if (str1 == "cos")
		return cos(op1);

	if (str1 == "tan")
		return tan(op1);

	if (str1 == "atan")
		return atan(op1);

	if (str1 == "sinh")
		return sinh(op1);

	if (str1 == "cosh")
		return cosh(op1);

	if (str1 == "tanh")
		return tanh(op1);

	if (str1 == "atanh")
		return atanh(op1);

	if (str1 == "asinh")
		return asinh(op1);

	if (str1 == "acosh")
		return acosh(op1);

	if (str1 == "asin")
		return asin(op1);

	if (str1 == "acos")
		return acos(op1);

	if (str1 == "ln")
		return log(op1);
}
double Stack_Machine(Stack<string> st1, int l)
{
	Stack<double> st2;
	string *str1 = new string[l], Op = "+-*/!^\\%";
	double l_op, r_op, var;

	for (int i = l - 1; i >= 0; i--)
		str1[i] = st1.Pop();

	for (int i = 0; i < l; i++)
	{
		if (Is_Elem(str1[i], Op) || (str1[i] == "sin") || (str1[i] == "cos") || (str1[i] == "tan") || (str1[i] == "atan") || (str1[i] == "sinh") || (str1[i] == "cosh") || (str1[i] == "tanh") || (str1[i] == "atanh") || (str1[i] == "asinh") || (str1[i] == "acosh") || (str1[i] == "asin") || (str1[i] == "acos") || (str1[i] == "ln"))
		{
			if ((str1[i] == "!") || (str1[i] == "sin") || (str1[i] == "cos") || (str1[i] == "tan") || (str1[i] == "atan") || (str1[i] == "sinh") || (str1[i] == "cosh") || (str1[i] == "tanh") || (str1[i] == "atanh") || (str1[i] == "asinh") || (str1[i] == "acosh") || (str1[i] == "asin") || (str1[i] == "acos") || (str1[i] == "ln"))
			{
				l_op = st2.Pop();
				st2.Push(Operator(str1[i], l_op, 0));
			}
			else
			{
				r_op = st2.Pop(); l_op = st2.Pop();
				st2.Push(Operator(str1[i], l_op, r_op));
			}
		}
		else
		{
			if (Is_Elem(str1[i], "0123456789"))
			{
				st2.Push(stod(str1[i]));
			}
			else
			{
				if ((str1[i] != "pi") && (str1[i] != "e"))
				{
					cout << "Enter " << str1[i] << endl;
					cin >> var;
					st2.Push(var);
				}
				else
				{
					if (str1[i] == "pi")
						var = M_PI;
					else
						var = M_E;
					st2.Push(var);
				}
			}
		}
	}

	return st2.Pop();
}
string Unary_Minus(string str1)
{
	string tmp(str1); string e;
	int *Pos = new int[tmp.length()];

	for (unsigned int i = 0; i < tmp.length(); i++)
	{
		if (tmp[i] == ' ')
			tmp.erase(i--, 1);
	}

	Pos[0] = str1.find(tmp[0]);
	for (unsigned int i = 1; i < tmp.length(); i++)
		Pos[i] = str1.find(tmp[i], Pos[i - 1] + 1);

	for (unsigned int i = 0; i < tmp.length(); i++)
	{
		if ((Is_Elem(tmp, "(", i) && Is_Elem(tmp, "-", i + 1)))
		{
			e = tmp[tmp.length() - 1];
			for (unsigned int j = tmp.length(); j > i + 1; j--)
				tmp[j] = tmp[j - 1];
			tmp[i + 1] = '0'; tmp += e;
		}
		if ((i == 0) && Is_Elem(tmp, "-", i))
		{
			e = tmp[tmp.length() - 1];
			for (unsigned int j = tmp.length(); j > 0; j--)
				tmp[j] = tmp[j - 1];
			tmp[i] = '0'; tmp += e;
		}
	}

	return tmp;
}

double Result(string str1)
{
	string *ML;
	Stack<string> st1;

	st1 = To_Postfix_Not(ML, EXtoML(Unary_Minus(str1), ML));

	return Stack_Machine(st1, st1.Amount_Elemnts());
}