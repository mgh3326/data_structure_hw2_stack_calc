#include <cctype>     // Provides isdigit
#include <iostream>   // Provides cout, cin, peek, ignore
#include <stack>      // Provides the stack template class
#include <vector>
#include <string>
#include <math.h>
using namespace std;
vector<string> v;//postfix�� ���� �Ǹ�, ��� �Լ����� ���Ǳ⿡ ���� ������ �����Ͽ����ϴ�.
int infixPostfix(istream& ins);//infix�� postfix�� �ٲ��ִ� �Լ��Դϴ�.
int caclpostfixexpr();//postfix�� ����ϴ� �Լ��Դϴ�.
int precedence(char op) {//�������� �켱������ ��ȯ���ִ� �Լ��Դϴ�.
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

	while (true) {//���� ����
		v.clear();
		std::cout << "Input : ";
		if(infixPostfix(cin))//infix�� postfix�� �ٲ��ݴϴ�. ��°��� -1�� ���(����)�϶� ���ǹ� ���
		{
			std::cout << "Output : Error!" << endl;
			cin.ignore();//���� ���� �ޱ� ���ؼ� cin���� ����ݴϴ�. 
			continue;
		}
		std::cout << "Output : ";
			if (caclpostfixexpr())//���� �ϰ�쿡 -1�� ����ϵ��� �Ͽ����ϴ�. ���� 0���� ��µɶ���, �Լ� ���ο��� ���� ����ϵ��� �Ͽ����ϴ�.
			{
				std::cout << "Error!" << endl;
				cin.ignore();//���� ���� �ޱ� ���ؼ� cin���� ����ݴϴ�. 
				continue;
			}
			cin.ignore();//���� ���� �ޱ� ���ؼ� cin���� ����ݴϴ�. 
	}
	return 0;
}

int infixPostfix(istream& ins)
{
	stack<char> st;//�����ڰ� ���� stack �Դϴ�.
	int number;//vecot<string>�� ��� istream�� ���� char�����μ� 1���ھ� �ޱ⿡ number��� int�� ������ ���� ��� vecotr<string>�� �Ѱ��ֵ��� �Ͽ����ϴ�.
	char symbol;//stack<int>�� ���� ���� 
	char op;//vector<string>�� ����ϱ⿡ �������� �켱������ Ȯ���ϱ� ���� char������ ���� �ޱ� ���� ���Ǵ� �����Դϴ�.

	vector<int> v_int;
	if (ins.peek() == '0')//ù ��¥�� 0�϶� �����մϴ�.
	{
		exit(0);
	}

	while (ins && ins.peek() != '\n')//������ ���������� �ݺ��մϴ�.
	{
		if (isdigit(ins.peek()))//������ ���
		{
			ins >> number;//���ڸ� �ѹ��� �ޱ� ���� int���� number�� �־����ϴ�.
			v.push_back(to_string(number));//int���� string���� �ٲ��� ����� ���� ���Ϳ� �־����ϴ�.

		}
		else if (ins.peek() == '(')// ���� ��ȣ
		{
			ins >> symbol;
			st.push(symbol);
		}
		else if (strchr("+-*/%^", ins.peek()) != NULL)//�����ڰ� ������ ���
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
		else if (ins.peek() == ')')//������ ��ȣ�� ������ ���
		{
			ins >> symbol;
			while(true){
				if (st.empty())//���� ��ȣ�� ������ �ùٸ� ��ȣ�� �ƴϱ� ������ return -1�� ���ؼ� �Լ��� �����մϴ�.
				{
					return -1;
				}
				op = st.top();//���� �ǳ�?
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
	while (!st.empty())//������ ��� ���ϴ�.
	{
		op = st.top();
		if (op == '(')// ���ÿ� ( ���� ��ȣ�� ���� �ִٸ� ��ȣ ������ return -1�� �Ͽ����ϴ�.
		{
			return -1;
		}
		v.push_back(to_string(op));
		st.pop();
	}
	return 0;//�Լ� ���� ����
}

int caclpostfixexpr()
{
	string c;
	stack<int> num_stack;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		c = v.at(i);
		if (c == "+" || c == "-" || c == "*" || c == "/" || c == "%" || c == "^")//�������� ���
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
			case '^':num_stack.push((int)pow(val1, val2)); break;//���� pow math.h
			}
		}
		else 
			num_stack.push(stoi(v.at(i)));//�����ڰ� �ƴ� ���(������ ���)���� num_stack ���ÿ� �ֽ��ϴ�.
		
	}
	if (num_stack.empty())//Ȥ�ó� ������ ���� pop ���ϸ� �ȵǹǷ� �Լ��� ���� �����ŵ�ϴ�.
	{
		cout << endl;
		return 0;
	}
	std::cout << num_stack.top() << endl;//cout�� ��ȣ�մϴ� >> std::cout
	num_stack.pop();
	return 0;
}
