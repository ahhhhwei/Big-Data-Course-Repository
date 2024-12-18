#include"Stack.h"
#include<string>
#include<vector>
#include<cassert>
void testStack()
{
	Stack<int> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	st.push(6);
	st.push(7);
	st.push(8);
	st.pop();
	st.display(cout);
	cout << endl;
	cout << "栈顶:" << st.top();
	cout << endl;
	Stack<int> ts;
	ts = st;
	ts.display(cout);
	cout << endl;
}
int eval(vector<string>& arr) {
	Stack<int> s;
	for (size_t i = 0; i < arr.size(); ++i)
	{
		string& str = arr[i];
		// str为数字
		if (!("+" == str || "-" == str || "*" == str || "/" == str))
		{
			s.push(atoi(str.c_str()));
		}
		else
		{
			// str为操作符
			int right = s.top();
			s.pop();
			int left = s.top();
			s.pop();
			switch (str[0])
			{
			case '+':
				s.push(left + right);
				break;
			case '-':
				s.push(left - right);
				break;
			case '*':
				s.push(left * right);
				break;
			case '/':
				s.push(left / right);
				break;
			}
		}
	}
	return s.top();
}
string postfix(string exp)
{
	char token, topToken;
	Stack<char> opStack;
	string postfixExp;
	const string BLANK = " ";
	for (int i = 0; i < exp.length(); i++)
	{
		token = exp[i];
		switch (token)
		{
		case ' ':
			break;
		case '(':
			opStack.push(token);
			break;
		case ')':
			for (;;)
			{
				assert(!opStack.empty());
				topToken = opStack.top();
				opStack.pop();
				if (topToken == '(')
					break;
				postfixExp.append(BLANK + topToken);
			}
			break;
		case '+': 
		case '-': 
		case '*': 
		case '/': 
		case '%':
			for (;;)
			{
				if (opStack.empty()||opStack.top()=='('||
					(token=='*'||token=='/' || token == '%')&&
					(opStack.top()=='+'||opStack.top()=='-'))
				{
					opStack.push(token);
						break;
				}
				else
				{
					topToken = opStack.top();
					opStack.pop();
					postfixExp.append(BLANK + topToken);
				}
			}
			break;
		default:
			postfixExp.append(BLANK + token);
			for (;;)
			{
				if (!isalnum(exp[i + 1]))
					break;
				i++;
				token = exp[i];
				postfixExp.append(1, token);
			}
		}
	}
	for (;;)
	{
		if (opStack.empty())
			break;
		topToken = opStack.top();
		opStack.pop();
		if (topToken != '(')
		{
			postfixExp.append(BLANK + topToken);
		}
		else
		{
			cout << "***Error in infix expression***" << endl;
			break;
		}
	}
	return postfixExp;
}
string fun(const string& str)
{
	string temp;
	for (size_t i = 0; i < str.size() - 1; ++i)
	{
		if (str[i] == '(' && str[i + 1] == '-')
		{
			temp += "(0";
		}
		else
		{
			temp.push_back(str[i]);
		}
	}
	temp.push_back(str.back());
	if (temp[0] == '-')
	{
		temp.insert(temp.begin(), '0');
	}
	return temp;
}
vector<string> f(string& ret)
{
	ret += ' ';
	vector<string> arr;
	vector<int> pos;
	for (size_t i = 0; i < ret.size(); ++i)
	{
		if (ret[i] == ' ')
		{
			pos.push_back(i);
		}

	}
	for (size_t i = 0; i < pos.size() - 1; ++i)
	{
		string temp = ret.substr(pos[i] + 1, pos[i + 1] - pos[i] - 1);
		arr.push_back(temp);
	}
	return arr;
}
int main()
{
	//栈的测试
	//testStack();
	string str;
	cout << "请输入中缀表达式: ";
	getline(cin, str);
	//处理负数
	str = fun(str);
	//中缀转后缀
	string ret = postfix(str);
	cout << "后缀表达式为: ";
	cout << ret << endl;
	//以字符串形式存入数组中
	vector<string> vs = f(ret);
	//计算求值
	cout << "表达式计算结果为: " << eval(vs) << endl;
	return 0;
}