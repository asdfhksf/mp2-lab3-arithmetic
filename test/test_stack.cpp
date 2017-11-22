#include "stack.h"
#include <gtest.h>

TEST(Stack, can_create_stack_with_positive_size)
{
	ASSERT_NO_THROW(Stack<int> st(5));
}

TEST(Stack, cant_create_stack_with_negative_size)
{
	ASSERT_ANY_THROW(Stack<int> st(-5));
}

TEST(Stack, can_create_copied_stack)
{
	Stack<int> st(5);

	for (int i = 0; i < 5; i++)
		st.Push(i);

	Stack<int> st2(st);

	ASSERT_NO_THROW(Stack<int> st1(st));
	EXPECT_EQ(true, st == st2);

	st2.Pop();
	st2.Push(1);

	EXPECT_EQ(false, st == st2);
}

TEST(Stack, can_push_pop)
{
	Stack<int> st(1);

	st.Push(5);

	EXPECT_EQ(5, st.Pop());
	EXPECT_EQ(0, st.Amount_Elemnts());
}

TEST(Stack, can_peek)
{
	Stack<int> st(1);
	int a, b;

	st.Push(5);

	a = st.Peek();
	b = st.Amount_Elemnts();

	EXPECT_EQ(5, a);
	EXPECT_EQ(b, 1);
}

TEST(Stack, can_return_empty)
{
	Stack<int> st(5);

	EXPECT_EQ(true, st.Empty());
}

TEST(Stack, can_return_full)
{
	Stack<int> st(5);

	for (int i = 0; i < 5; i++)
		st.Push(i);

	EXPECT_EQ(true, st.Full());
}

TEST(Stack, can_return_amount_elements)
{
	Stack<int> st(5);

	for (int i = 0; i < 3; i++)
		st.Push(i);

	EXPECT_EQ(3, st.Amount_Elemnts());
}

TEST(Stack, can_cleaning)
{
	Stack<int> st(5);

	for (int i = 0; i < 3; i++)
		st.Push(i);

	st.Cleaning();

	EXPECT_EQ(0, st.Amount_Elemnts());
}

TEST(Stack, can_compare_of_eq_size_true)
{
	Stack<int> st(5), st1(5);

	for (int i = 0; i < 3; i++)
	{
		st.Push(i); st1.Push(i);
	}

	EXPECT_EQ(true, st == st1);
}

TEST(Stack, can_compare_of_dif_size_false)
{
	Stack<int> st(5), st1(6);

	EXPECT_EQ(true, st != st1);
}