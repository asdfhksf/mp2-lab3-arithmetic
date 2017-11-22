#include "includes.h"

using namespace std;

template< typename T >
class Stack
{
	T *Elements;
	int Size;
	int Count_Elements;

public:
	Stack(int s = 5);
	Stack(const Stack &st);
	~Stack();

	void Push(T elem);
	T Pop();
	T Peek();
	bool Empty();
	bool Full();
	int Amount_Elemnts();
	void Cleaning();

	bool operator==(const Stack &st);
	bool operator!=(const Stack &st);

	Stack<T>& operator=(const Stack &st);

	friend ostream& operator<<(ostream &os, const Stack<T> &st)
	{
		cout << fixed;
		cout.precision(15);

		int s = st.Count_Elements;	
		Stack<T> tmp(st);
		T *E = new T[s];

		for (int i = s - 1; i >= 0; i--)
			E[i] = tmp.Pop();

		os << "|";
		for (int i = 0; i < s; i++)
			os << E[i] << "|";

		delete[]E;
		return os;
	}
};



template< typename T >
Stack<T>::Stack(int s)
{
	if (s > 0)
	{
		Size = s;
		Count_Elements = 0;

		Elements = new T[Size];
	}
	else
		throw "Negative size";
}

template< typename T >
Stack<T>::Stack(const Stack &st)
{
	Size = st.Size;
	Count_Elements = st.Count_Elements;

	Elements = new T[Size];

	for (int i = 0; i < Size; i++)
		Elements[i] = st.Elements[i];
}

template< typename T >
Stack<T>::~Stack()
{
	delete[] Elements;
}


template< typename T >
void Stack<T>::Push(T elem)
{
	if (!Full())
	{
		Elements[Count_Elements] = elem;

		Count_Elements++;
	}
	else
	{
		T *tmp;

		tmp = new T[Size];

		for (int i = 0; i < Size; i++)
			tmp[i] = Elements[i];

		delete[] Elements;

		Elements = new T[Size + 10];
		for (int i = 0; i < Size; i++)
			Elements[i] = tmp[i];

		delete[] tmp;

		Elements[Count_Elements] = elem;

		Size++;
		Count_Elements++;
	}
}

template< typename T >
T Stack<T>::Pop()
{
	if (!Empty())
		return Elements[--Count_Elements];
	else
		throw - 1;
}

template< typename T >
T Stack<T>::Peek()
{
	if (!Empty())
	{
		return Elements[Count_Elements - 1];
	}
	else
		throw - 1;
}

template< typename T >
bool Stack<T>::Empty()
{
	if (Count_Elements == 0) return true;
	else return false;
}

template< typename T >
bool Stack<T>::Full()
{
	if (Count_Elements == Size) return true;
	else return false;
}

template< typename T >
int Stack<T>::Amount_Elemnts()
{
	return Count_Elements;
}

template< typename T >
void Stack<T>::Cleaning()
{
	Count_Elements = 0;

	for (int i = 0; i < Size; i++)
		Elements[i] = 0;
}


template< typename T >
bool Stack<T>::operator==(const Stack &st)
{
	int ii = 0;

	if (Size == st.Size)
	{
		for (int i = 0; i < Size; i++)
			if (Elements[i] == st.Elements[i]) ii++;
		if (ii == Size) return true;
	}
	return false;
}

template< typename T >
bool Stack<T>::operator!=(const Stack &st)
{
	return !(*this == st);
}

template< typename T >
Stack<T>& Stack<T>::operator=(const Stack &st)
{
	if (this != &st)
	{
		Size = st.Size;
		Count_Elements = st.Count_Elements;

		delete[]Elements;
		Elements = new T[Size];

		for (int i = 0; i < Size; i++)
			Elements[i] = st.Elements[i];
	}
	return *this;
}