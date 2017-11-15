#include "stack.h"
#include "arithmetic.h"
#include "includes.h"



//int DStoS(string str1, string str2, string &str3, int pos)
//{
//	int j = 0;
//
//	j = Searh(str1, ".", pos);
//
//	while (!Is_Elem(str1, str2, j))
//		j--;
//
//	j++;
//
//	while (!Is_Elem(str1, str2, j))
//		str3 += str1[j++];
//
//
//	return j;
//}

int Searh(string str1, string str2, int i1 = 0, int j1 = 0)
{
	for (int i = i1; i < str1.length(); i++)
		for (int j = j1; j < str2.length(); j++)
			if (str1[i] == str2[j])
				return i;
	return -1;
}
bool Is_Elem(string str1, string str2, int pos)
{
	if ((str1[pos] == '\0'))
		return true;

	for (int j = 0; j < str2.length(); j++)
		if (str1[pos] == str2[j])
			return true;

	return false;
}
int EXtoML(string str1, string *(&str2))
{
	string tmp(str1), Op = "()+-*/";
	int j = 0, i = 0;

	for (int i = 0; i < tmp.length(); i++)
		if (tmp[i] == ' ')
			tmp.erase(i, 1);

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
			if (!Is_Elem(tmp, "(", j)) i++;
			str2[i] += tmp[j];
			if (!Is_Elem(tmp, ")", j)) i++;
			j++;
		}
	}

	return i + 1;
}
void Check_Correct_Characters(string str1)
{
	int pos = 0;
	string Trash = "!@#$%&_<>,?\|;:{}'~`";

	for (int i = 0; i < str1.length(); i++)
	{
		if (Is_Elem(str1, Trash, i))
		{
			cout << "Unacceptable character:	" << str1[i] << endl;
			pos = str1.find(str1[i], pos);
			cout << "On " << pos << " position" << endl;
		}
	}
	//cout << endl;

}
void Check_Correct_Operators(string str1)
{
	string tmp(str1);
	int *Pos = new int[tmp.length()];

	for (int i = 0; i < tmp.length(); i++)
	{
		if (tmp[i] == ' ')
		{
			tmp.erase(i, 1);
			i = 0;
		}
		Pos[i] = 0;
	}

	Pos[0] = Searh(str1, tmp);
	for (int i = 1; i < tmp.length(); i++)
		Pos[i] = Searh(str1, tmp, Pos[i - 1] + 1, i);

	for (int i = 0; i < tmp.length(); i++)
	{
		if (Is_Elem(tmp, "+-*/", i) && Is_Elem(tmp, "+-*/", i + 1))
		{
			cout << "Two operators in a row:	" << tmp[i] << " and " << tmp[i + 1] << endl;
			cout << "On " << Pos[i] << " position" << endl;
		}
	}
}
void Check_Correct_Brackets(string str1)
{
	char b;
	string tmp(str1), l_brackets = "[(", r_brackets = ")]";
	Stack<char> brackets(tmp.length());

	for (int i = 0; i < tmp.length(); i++)
	{
		if (Is_Elem(tmp, l_brackets, i))
			brackets.Push(tmp[i]);

		if (Is_Elem(tmp, r_brackets, i))
		{
			b = brackets.Pop();

			if ((Is_Elem(tmp, ")", i) && ((b != '(') && (b != '\x1'))))
			{
				cout << "Opening and closing brackets of different types" << endl;
				break;
			}
		}
	}
	//cout << endl;

	brackets.Cleaning();
	for (int i = 0; i < tmp.length(); i++)
	{
		if (Is_Elem(tmp, l_brackets, i))
			brackets.Push(tmp[i]);

		if (Is_Elem(tmp, r_brackets, i))
		{
			if (brackets.Peek() == '\x1')
			{
				cout << "Closing brackets more" << endl;
				break;
			}
			brackets.Pop();
		}
	}
	if (!brackets.Empty())
		cout << "Opening brackets more" << endl;
	//cout << endl;
}
void Check(string str1)
{
	Check_Correct_Brackets(str1);
	Check_Correct_Characters(str1);
	Check_Correct_Operators(str1);
}



void main()
{
	string Ex, *ML;
	Stack<string> st;
	int l;


	//cout << "Enter the expression" << endl;
	//cin >> Ex;

	Ex = "(1++1[)]]%";
	cout << Ex << endl << endl;

	Check(Ex);

	//l = EXtoML(Ex, ML);
	//for (int i = 0; i < l; i++)
	//	cout << ML[i] << endl;
	//cout << endl;
}