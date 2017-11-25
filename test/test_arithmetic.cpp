#include "arithmetic.h"
#include <gtest.h>

TEST(Arithmetic, can_is_elem_true)
{
	EXPECT_EQ(true, Is_Elem("iuhdasfguihiu-7#&^%$(^%%*&h23465123409", "-", 13));
}

TEST(Arithmetic, can_is_elem_false)
{
	EXPECT_EQ(false, Is_Elem("iuhdasfguihiu7#&^%$(^%%*&h23465123409", "-", 13));
}

TEST(Arithmetic, can_delete_spaces)
{
	string str1 = " -( ( (2 ^  3)!- 10 ^ 2 / 234) * 3!) ^ (-1 / 10) + a ";

	for (unsigned int i = 0; i < str1.length(); i++)
	{
		if (str1[i] == ' ')
			str1.erase(i--, 1);
	}

	EXPECT_EQ("-(((2^3)!-10^2/234)*3!)^(-1/10)+a", str1);
}

TEST(Arithmetic, can_break_into_lexems)
{
	string str1 = " 1 + 2 - 3^6 ", *str2;

	EXtoML(str1, str2);

	EXPECT_EQ("1", str2[0]);
	EXPECT_EQ("+", str2[1]);
	EXPECT_EQ("2", str2[2]);
	EXPECT_EQ("-", str2[3]);
	EXPECT_EQ("3", str2[4]);
	EXPECT_EQ("^", str2[5]);
	EXPECT_EQ("6", str2[6]);
}

TEST(Arithmetic, can_check_correct_characters_true)
{
	bool C = false;
	int pos = 0;
	string Trash = "@#$%&_<>,?|;:{}'~`", str1 = " 1 + &2 - 3^6 ";

	for (unsigned int i = 0; i < str1.length(); i++)
	{
		if (Is_Elem(str1, Trash, i))
		{
			pos = str1.find(str1[i], pos);
			C = true;
		}
	}

	EXPECT_EQ(true, C);
	EXPECT_EQ(5, pos);
	EXPECT_EQ('&', str1[pos]);
}

TEST(Arithmetic, can_check_correct_characters_false)
{
	bool C = false;
	int pos = 0;
	string Trash = "@#$%&_<>,?|;:{}'~`", str1 = " 1 + 2 - 3^6 ";

	for (unsigned int i = 0; i < str1.length(); i++)
	{
		if (Is_Elem(str1, Trash, i))
		{
			pos = str1.find(str1[i], pos);
			C = true;
		}
	}

	EXPECT_EQ(false, C);
	EXPECT_EQ(0, pos);
}

TEST(Arithmetic, can_check_correct_operators_true)
{
	bool C = false;
	string str1 = "1 ++ 2 - 3^6 ", tmp(str1);
	int *Pos = new int[tmp.length()], a;

	for (unsigned int i = 0; i < tmp.length(); i++)
	{
		if (tmp[i] == ' ')
			tmp.erase(i--, 1);
		Pos[i] = 0;
	}

	Pos[0] = str1.find(tmp[0]);
	for (unsigned int i = 1; i < tmp.length(); i++)
		Pos[i] = str1.find(tmp[i], Pos[i - 1] + 1);

	if (Is_Elem(tmp, "+*/.!"))
	{
		C = true;
	}

	for (unsigned int i = 0; i < tmp.length(); i++)
	{
		if (Is_Elem(tmp, "+-*/.^", i) && Is_Elem(tmp, "+-*/.^", i + 1))
		{
			a = Pos[i];
			C = true;
		}
	}

	EXPECT_EQ(true, C);
	EXPECT_EQ(2, a);
	EXPECT_EQ('+', str1[a]);

	delete[] Pos;
}

TEST(Arithmetic, can_check_correct_operators_false)
{
	bool C = false;
	string str1 = "1 + 2 - 3^6 ", tmp(str1);
	int *Pos = new int[tmp.length()], a;

	for (unsigned int i = 0; i < tmp.length(); i++)
	{
		if (tmp[i] == ' ')
			tmp.erase(i--, 1);
		Pos[i] = 0;
	}

	Pos[0] = str1.find(tmp[0]);
	for (unsigned int i = 1; i < tmp.length(); i++)
		Pos[i] = str1.find(tmp[i], Pos[i - 1] + 1);

	if (Is_Elem(tmp, "+*/.!"))
	{
		C = true;
	}

	for (unsigned int i = 0; i < tmp.length(); i++)
	{
		if (Is_Elem(tmp, "+-*/.^", i) && Is_Elem(tmp, "+-*/.^", i + 1))
		{
			a = Pos[i];
			C = true;
		}
	}

	EXPECT_EQ(false, C);
	EXPECT_EQ(-858993460, a);

	delete[] Pos;
}

TEST(Arithmetic, can_check_correct_brackets_opening_brackets_more)
{
	char b;
	bool C = false;
	string str1 = " ((1 + 2 - 3^6) ", tmp(str1), l_brackets = "[(", r_brackets = ")]";
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
			}
		}
	}

	if (!brackets.Empty())
	{
		C = true;
	}

	EXPECT_EQ(true, C);
}

TEST(Arithmetic, can_check_correct_brackets_closing_brackets_more)
{
	int a;
	char b;
	bool C = false;
	string str1 = " ((1 + 2 - 3^6))) ", tmp(str1), l_brackets = "[(", r_brackets = ")]";
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
				a = i;
				C = true;
				break;
			}
		}
	}


	EXPECT_EQ(true, C);
	EXPECT_EQ(16, a);
}

TEST(Arithmetic, can_check_correct_brackets_different_types)
{
	int a;
	char b;
	bool C = false;
	string str1 = " ((1 + 2 - 3^6]) ", tmp(str1), l_brackets = "[(", r_brackets = ")]";
	Stack<char> brackets(tmp.length());

	for (unsigned int i = 0; i < tmp.length(); i++)
	{
		if (Is_Elem(tmp, l_brackets, i))
			brackets.Push(tmp[i]);

		if (Is_Elem(tmp, r_brackets, i))
		{
			b = brackets.Pop();
			if (((Is_Elem(tmp, ")", i) && ((b != '(')))) || ((Is_Elem(tmp, "]", i) && ((b != '[')))))
			{
				a = i;
				C = true;
				break;
			}
		}
	}

	EXPECT_EQ(true, C);
	EXPECT_EQ(14, a);
}

TEST(Arithmetic, can_check_correct_operands_true)
{
	string str1 = "1 + 2 2 - 3^6 ";

	bool C = false;
	bool n = false, first = true;
	int a, b;
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
				b = a;
				C = true;
			}
		}
	}

	EXPECT_EQ(true, C);
	EXPECT_EQ(4, b);
}

TEST(Arithmetic, can_check_correct_operands_false)
{
	string str1 = "234.432";

	bool C = false;
	bool n = false, first = true;
	int a, b;

	for (unsigned int i = 0; i < str1.length(); i++)
	{
		if ((!Is_Elem(str1, "+-*/^!()[] ", i)) && (first))
		{
			first = false;
			n = true;
			a = i;
		}

		if (Is_Elem(str1, "+-*/^()[].", i))
		{
			n = false;
			first = true;
		}

		if ((!Is_Elem(str1, "+-*/^!()[] ", i)) && (n))
		{
			if ((i != 0) && (!Is_Elem(str1, "0123456789", i - 1)) && (a != i))
			{
				b = a;
				C = true;
			}
		}
	}

	EXPECT_EQ(false, C);
	EXPECT_EQ(-858993460, b);
}

TEST(Arithmetic, can_juxtapose_indices_of_exp_with_spaces_and_without_spaces)
{
	string str = " -1 + 2  * 5 ", tmp = "-1+2*5";
	int *Pos = new int[tmp.length()];

	Pos[0] = str.find(tmp[0]);
	for (unsigned int i = 1; i < tmp.length(); i++)
		Pos[i] = str.find(tmp[i], Pos[i - 1] + 1);

	EXPECT_EQ(1, Pos[0]);
	EXPECT_EQ(2, Pos[1]);
	EXPECT_EQ(4, Pos[2]);
	EXPECT_EQ(6, Pos[3]);
	EXPECT_EQ(9, Pos[4]);
	EXPECT_EQ(11, Pos[5]);

	delete[]Pos;
}

TEST(Arithmetic, can_to_postfix_not)
{
	int l = 7, a;
	string *m = new string[l];
	Stack<string> st1(l);

	m[0] = '1'; m[1] = '+'; m[2] = '2'; m[3] = '-'; m[4] = '3'; m[5] = '^'; m[6] = '6';
	st1.Push("1"); st1.Push("2"); st1.Push("+"); st1.Push("3"); st1.Push("6"); st1.Push("^"); st1.Push("-");


	if (st1 == To_Postfix_Not(m, l))
		a = 1;
	else
		a = 0;

	EXPECT_EQ(1, a);
}

TEST(Arithmetic, can_calculate_the_result)
{
	Stack<string> st1;

	st1.Push("1"); st1.Push("2"); st1.Push("+"); st1.Push("3"); st1.Push("6"); st1.Push("^"); st1.Push("-");

	EXPECT_EQ(-726, Stack_Machine(st1, 7));
}

TEST(Arithmetic, unary_minus)
{
	EXPECT_EQ("0-1+2-3^6", Unary_Minus(" -1 + 2 - 3^6 "));
}