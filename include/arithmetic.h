#include "stack.h"

int fact(int n);

bool Is_Elem(string str1, string str2, int pos = 0);
string Delete_Spaces(string str1);
int* Positions(int *(&Pos), string str1, string str2);

int EXtoML(string str1, string *(&str2));

bool Check_Correct_Characters(string str1);
bool Check_Correct_Operators(string str1);
bool Check_Correct_Brackets(string str1);
bool Check_Correct_Operands(string str1);
bool Check(string str1);

int Prior(string str1);
Stack<string> To_Postfix_Not(string *(&str1), int l);
double Operator(string str1, double op1, double op2);
double Stack_Machine(Stack<string> st1);
string Unary_Minus(string str1);

double Result(string str1);