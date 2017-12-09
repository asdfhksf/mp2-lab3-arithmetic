#include "arithmetic.h"
#include <gtest.h>

struct Composition
{
	bool tf;
	string s;

	Composition(string s1 = "", bool a = false) { s = s1; tf = a; }
};

class CheckingTest : public ::testing::TestWithParam<Composition>
{
protected:
	Composition ob;
public:
	CheckingTest() { ob = GetParam(); }
	~CheckingTest() {}
};


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
	EXPECT_EQ("-(((2^3)!-10^2/234)*3!)^(-1/10)+a", Delete_Spaces(" -( ( (2 ^  3)!- 10 ^ 2 / 234) * 3!) ^ (-1 / 10) + a "));
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
	EXPECT_EQ(true, Check_Correct_Characters(" 1 + &2 - 3^6 "));
}

TEST(Arithmetic, can_check_correct_characters_false)
{
	EXPECT_EQ(false, Check_Correct_Characters(" 1 + 2 - 3^6 "));
}

INSTANTIATE_TEST_CASE_P(Instantiation_1,
	CheckingTest,
	::testing::Values(Composition("1 + 1", false), Composition("1 + 1#", true)));

TEST_P(CheckingTest, param_check_correct_characters)
{
	EXPECT_EQ(ob.tf, Check_Correct_Characters(ob.s));
}

TEST(Arithmetic, can_check_correct_operators_true)
{
	EXPECT_EQ(true, Check_Correct_Operators("1 ++ 2 - 3^6 "));
}

TEST(Arithmetic, can_check_correct_operators_false)
{
	EXPECT_EQ(false, Check_Correct_Operators("1 + 2 - 3^6 "));
}

INSTANTIATE_TEST_CASE_P(Instantiation_2,
	CheckingTest,
	::testing::Values(Composition("1 + 1", false), Composition("1 ++ 1", true)));

TEST_P(CheckingTest, param_check_correct_operators)
{
	EXPECT_EQ(ob.tf, Check_Correct_Operators(ob.s));
}


TEST(Arithmetic, can_check_correct_brackets_opening_brackets_more)
{
	EXPECT_EQ(true, Check_Correct_Brackets(" ((1 + 2 - 3^6) "));
}

TEST(Arithmetic, can_check_correct_brackets_closing_brackets_more)
{
	EXPECT_EQ(true, Check_Correct_Brackets(" ((1 + 2 - 3^6))) "));
}

TEST(Arithmetic, can_check_correct_brackets_different_types)
{
	EXPECT_EQ(true, Check_Correct_Brackets(" ((1 + 2 - 3^6]) "));
}

TEST(Arithmetic, can_check_correct_operands_true)
{
	EXPECT_EQ(true, Check_Correct_Operands("1 + 2 2 - 3^6 "));
}

TEST(Arithmetic, can_check_correct_operands_false)
{
	EXPECT_EQ(false, Check_Correct_Operands("1 + 12345.987 - 9463.987654321^6 "));
}


TEST(Arithmetic, can_juxtapose_indices_of_exp_with_spaces_and_without_spaces)
{
	string str1 = " -1 + 2  * 5 ", tmp = "-1+2*5";
	int *Pos;

	Pos = Positions(Pos, str1, tmp);

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

TEST(Arithmetic, can_calculate_the_result_1)
{
	Stack<string> st1;

	st1.Push("1"); st1.Push("2"); st1.Push("+"); st1.Push("3"); st1.Push("6"); st1.Push("^"); st1.Push("-");

	EXPECT_EQ(-726, Stack_Machine(st1, 7));
}

TEST(Arithmetic, unary_minus)
{
	EXPECT_EQ("0-1+2-3^6", Unary_Minus(" -1 + 2 - 3^6 "));
}

TEST(Arithmetic, can_calculate_the_result_2)
{
	EXPECT_EQ(-726, Result("1 + 2 - 3^6"));
}