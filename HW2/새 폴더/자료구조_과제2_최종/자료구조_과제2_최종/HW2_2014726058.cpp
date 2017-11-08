#include <cctype>     // Provides isdigit
#include <iostream>   // Provides cout, cin, peek, ignore
#include <stack>      // Provides the stack template class
#include <vector>
#include <string>
#include <math.h>
using namespace std;
vector<string> v;//postfix가 저장 되며, 모든 함수에서 사용되기에 전역 변수로 선언하였습니다.
int infixPostfix(istream& ins);//infix를 postfix로 바꿔주는 함수입니다.
int caclpostfixexpr();//postfix를 계산하는 함수입니다.
int precedence(char op) {//연산자의 우선순위를 반환해주는 함수입니다.
	switch (op) {
	case'(':case')':return 0;
	case'+':case'-':return 1;
	case'*':case'/':case'%':return 2;
	case'^':return 3;
	}
	return -1;
}
string to_string(char c) {
	string s(1,c); 
	return s;
}
int main()
{

	while (true) {//무한 루프
		v.clear();
		std::cout << "Input : ";
		if(infixPostfix(cin))//infix를 postfix로 바꿔줍니다. 출력값이 -1일 경우(에러)일때 조건문 통과
		{
			std::cout << "Output : Error!" << endl;
			cin.ignore();//다음 값을 받기 위해서 cin값도 비워줍니다. 
			continue;
		}
		std::cout << "Output : ";
			if (caclpostfixexpr())//에러 일경우에 -1을 출력하도록 하였습니다. 또한 0으로 출력될때는, 함수 내부에서 값을 출력하도록 하였습니다.
			{
				std::cout << "Error!" << endl;
				cin.ignore();//다음 값을 받기 위해서 cin값도 비워줍니다. 
				continue;
			}
			cin.ignore();//다음 값을 받기 위해서 cin값도 비워줍니다. 
	}
	return 0;
}

int infixPostfix(istream& ins)
{
	stack<char> st;//연산자가 담기는 stack 입니다.
	int number;//vecot<string>에 경우 istream의 값을 char형으로서 1글자씩 받기에 number라는 int형 변수에 먼저 담고 vecotr<string>에 넘겨주도록 하였습니다.
	char symbol;//stack<int>에 들어가기 전에 
	char op;//vector<string>을 사용하기에 연산자의 우선순위를 확인하기 위해 char형으로 먼저 받기 위해 사용되는 변수입니다.

	vector<int> v_int;
	if (ins.peek() == '0')//첫 글짜가 0일때 종료합니다.
	{
		exit(0);
	}

	while (ins && ins.peek() != '\n')//문장이 끝날때까지 반복합니다.
	{
		if (isdigit(ins.peek()))//숫자인 경우
		{
			ins >> number;//숫자를 한번에 받기 위해 int형인 number에 넣었습니다.
			v.push_back(to_string(number));//int형을 string으로 바꾼후 출력을 위한 벡터에 넣었습니다.

		}
		else if (ins.peek() == '(')// 왼쪽 괄호
		{
			ins >> symbol;
			st.push(symbol);
		}
		else if (strchr("+-*/%^", ins.peek()) != NULL)//연산자가 나오는 경우
		{
			ins >> symbol;
			while (!st.empty()) {
				op = st.top();
				if (precedence(symbol) <= precedence(op))
				{
					v.push_back(to_string(op));
					st.pop();
				}
				else break;
			}
			st.push(symbol);
		}
		else if (ins.peek() == ')')//오른쪽 괄호가 나오는 경우
		{
			ins >> symbol;
			while(true){
				if (st.empty())//왼쪽 괄호가 없으면 올바른 괄호가 아니기 때문에 return -1을 통해서 함수를 종료합니다.
				{
					return -1;
				}
				op = st.top();//리턴 되나?
				st.pop();
				if (op == '(')
					break;
				else
					v.push_back(to_string(op));
			}
			
		}
		else
			ins.ignore();
	}
	while (!st.empty())//스택을 모두 비웁니다.
	{
		op = st.top();
		if (op == '(')// 스택에 ( 왼쪽 괄호가 남아 있다면 괄호 오류라서 return -1을 하였습니다.
		{
			return -1;
		}
		v.push_back(to_string(op));
		st.pop();
	}
	return 0;//함수 정상 종료
}

int caclpostfixexpr()
{
	string c;
	stack<int> num_stack;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		c = v.at(i);
		if (c == "+" || c == "-" || c == "*" || c == "/" || c == "%" || c == "^")//연산자인 경우
		{
			int val2 = num_stack.top();
			num_stack.pop();
			int val1 = num_stack.top();
			num_stack.pop();
			switch (c.at(0))
			{
			case '+':num_stack.push(val1 + val2); break;
			case '-':num_stack.push(val1 - val2); break;
			case '*':num_stack.push(val1 * val2); break;
			case '/':
				if (val2 == 0)
				return -1;
				else
					 num_stack.push(val1 / val2); break;
			case '%':
				if (val2 == 0)
					return -1;
				else
				num_stack.push(val1 % val2); break;
			case '^':num_stack.push((int)pow(val1, val2)); break;//제곱 pow math.h
			}
		}
		else 
			num_stack.push(stoi(v.at(i)));//연산자가 아닌 경우(숫자인 경우)에는 num_stack 스택에 넣습니다.
		
	}
	if (num_stack.empty())//혹시나 공백이 들어가면 pop 을하면 안되므로 함수를 먼저 종료시킵니다.
	{
		cout << endl;
		return 0;
	}
	std::cout << num_stack.top() << endl;//cout이 모호합니다 >> std::cout
	num_stack.pop();
	return 0;
}
