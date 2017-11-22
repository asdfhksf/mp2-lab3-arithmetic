#include "arithmetic.h"

bool C;

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
int EXtoML(string str1, string *(&str2))
{
	string tmp(str1), Op = "()+-*/^!";
	unsigned int j = 0, i = 0;

	for (unsigned int i = 0; i < tmp.length(); i++)
		if (tmp[i] == ' ')
			tmp.erase(i--, 1);

	while (j < tmp.length())
	{
		while (!Is_Elem(str1, Op, j))
			j++;
		if (j < str1.length())
		{
			if (!Is_Elem(str1, "(", j)) i++;
			if (!Is_Elem(str1, ")", j)) i++;
			j++;
		}
	}
	str2 = new string[i + 10];

	i = j = 0;
	while (j < tmp.length())
	{
		while (!Is_Elem(tmp, Op, j))
		{
			str2[i] += tmp[j++];
		}
		if (j < tmp.length())
		{
			if ((!Is_Elem(tmp, "(", j))) i++;
			str2[i] += tmp[j];
			if ((!Is_Elem(tmp, ")!", j))) i++;
			j++;
		}
	}

	return i + 1;
}
void Check_Correct_Characters(string str1)
{
	int pos = 0;
	string Trash = "@#$%&_<>,?|;:{}'~`";

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

}
void Check_Correct_Operators(string str1)
{
	string tmp(str1);
	int *Pos = new int[str1.length()];

	for (unsigned int i = 0; i < tmp.length(); i++)
	{
		if (tmp[i] == ' ')
			tmp.erase(i--, 1);
		Pos[i] = 0;
	}

	Pos[0] = str1.find(tmp[0]);
	for (unsigned int i = 1; i < tmp.length(); i++)
		Pos[i] = str1.find(tmp[i], Pos[i - 1] + 1);

	if (Is_Elem(tmp, "+*/.^!"))
	{
		cout << "Operator at the beginning of the line" << endl;
		C = true;
	}

	for (unsigned int i = 0; i < tmp.length(); i++)
	{
		if (Is_Elem(tmp, "+-*/.^", i) && Is_Elem(tmp, "+-*/.^", i + 1))
		{
			cout << "Two operators in a row:	" << tmp[i] << " and " << tmp[i + 1] << endl;
			cout << "On " << Pos[i] << " position" << endl;
			C = true;
		}
	}

	delete[] Pos;
}
void Check_Correct_Brackets(string str1)
{
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
}
void Check_Correct_Operands(string str1)
{
	bool n = false, first = true;
	int a;
	for (unsigned int i = 0; i < str1.length(); i++)
	{
		if ((!Is_Elem(str1, "+-*/^!()[] ", i)) && (first))
		{
			first = false;
			n = true;
			a = i;
		}

		if (Is_Elem(str1, "+-*/^()[]", i))
		{
			n = false;
			first = true;
		}

		if ((!Is_Elem(str1, "+-*/^!()[] ", i)) && (n))
		{
			if ((i != 0) && (!Is_Elem(str1, "0123456789", i - 1)) && (a != i))
			{
				cout << "Two operands in a row:	" << str1[a] << " and " << str1[i] << endl;
				cout << "On " << a << " position" << endl;
				C = true;
			}
		}
	}

}
void Check(string str1)
{
	Check_Correct_Brackets(str1);
	Check_Correct_Characters(str1);
	Check_Correct_Operators(str1);
	Check_Correct_Operands(str1);

	if (C)
		cout << endl << "Enter the correct expression" << endl;
	cout << endl;
}
int Prior(string str1)
{
	if ((str1 == "+") || (str1 == "-"))
		return 2;

	if ((str1 == "*") || (str1 == "/"))
		return 3;

	if (str1 == "^")
		return 4;

	if (str1 == "!")
		return 5;
}
Stack<string> To_Postfix_Not(string *(&str1), int l)
{
	Stack<string> st1(l);
	Stack<string> Op(l);

	for (int i = 0; i < l; i++)
	{
		if (!Is_Elem(str1[i], "+-*/()^!"))
			st1.Push(str1[i]);

		if (Is_Elem(str1[i], "("))
			Op.Push(str1[i]);

		if (Is_Elem(str1[i], ")"))
		{
			while (Op.Peek() != "(")
				st1.Push(Op.Pop());
			Op.Pop();
		}

		if (Is_Elem(str1[i], "+-*/^!"))
		{
			while (!Op.Empty() && (Op.Peek() != "(") && (Prior(str1[i]) <= Prior(Op.Peek())))
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
}
double Stack_Machine(Stack<string> st1, int l)
{
	Stack<double> st2;
	string *str1 = new string[l];
	double l_op, r_op, var;

	for (int i = l - 1; i >= 0; i--)
		str1[i] = st1.Pop();

	for (int i = 0; i < l; i++)
	{
		if (Is_Elem(str1[i], "+-*/!^"))
		{
			if (str1[i] == "!")
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
				cout << "Enter " << str1[i] << endl;
				cin >> var;
				st2.Push(var);
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