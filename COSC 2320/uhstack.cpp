#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

struct node
{
	string name;
	string op;
	string value;
	node * link;
};
class stack
{
private:
	node * top;
public:
	stack();
	void initializeStack();
	void push(node *);
	void pop();
	string getTop();
	void priceCheck(stack);
	void reverse();
	void print();
	string performOps();
};
bool isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
			return false;
		}
	}
	return true;
}
vector<string> split(string s, char delim, vector<string> &vect)
{
	stringstream ss;
	ss.str(s);
	string tokens;
	int i = 0;
	while (getline(ss, tokens, delim))
	{
		vect.at(i) = tokens;
		i++;
	}
	return vect;
}
int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Error. Parameter not correctly specified." << endl;
		return 0;
	}
	
	string parameter(argv[1]);
	string filename = parameter.substr(6);
	ifstream file;
	file.open(filename);

	int count = 0;
	string people[10] = { "", "", "", "", "", "", "", "", "", ""};
	stack prices;
	stack * stacks = new stack[10];
	string line;
	while (getline(file, line))
	{
		if (line[0] == '#' || line == "")
		{
			continue;
		}
		vector<string> vect(3);
		split(line, '\t', vect);
		node * temp = new node;
		if (vect[0] == "price")
		{
			temp->name = vect[0];
			temp->op = vect[1];
			temp->value = vect[2];
			prices.push(temp);
			vect.clear();
			temp = NULL;
			delete temp;
		}
		else
		{
			int person = 0;
			for (int i = 0; i < 10; i++)
			{
				if (vect[0] == people[i])
				{
					person = i;
					break;
				}
				else if (people[i] == "")
				{
					people[i] = vect[0];
					person = i;
					break;
				}
			}
			if (vect[1] == "total")
			{
				stacks[person].priceCheck(prices);
				stacks[person].print();
			}
			else
			{
				temp->name = vect[0];
				temp->op = vect[1];
				temp->value = vect[2];
				stacks[person].push(temp);
				vect.clear();
				temp = NULL;
				delete temp;
			}
		}	
	}

	return 0;
}

stack::stack()
{
	top = NULL;
}
void stack::initializeStack()
{
	while (top != NULL)
	{
		node * temp;
		temp = top;
		top = top->link;
		delete temp;
		temp = NULL;
	}
}
void stack::push(node * newTop)
{
	node * temp = new node;
	temp->name = newTop->name;
	temp->op = newTop->op;
	temp->value = newTop->value;
	temp->link = NULL;
	if (top == NULL)
	{
		top = temp;
	}
	else
	{
		temp->link = top;
		top = temp;
	}
}
void stack::pop()
{
	node * temp;
	if (top != NULL)
	{
		temp = top;
		top = top->link;
		delete temp;
		temp = NULL;
	}
}
string stack::getTop()
{
	return top->value;
}
void stack::priceCheck(stack prices)
{
	node * current = top;
	while (current != NULL)
	{
		if (!isNumber(current->value))
		{
			node * checkPrice = prices.top;
			while (checkPrice != NULL)
			{
				if (current->value == checkPrice->op)
				{
					current->value = checkPrice->value;
					checkPrice = checkPrice->link;
				}
				else
				{
					checkPrice = checkPrice->link;
				}
			}
		}
		current = current->link;
	}
}
void stack::reverse()
{
	stack newStack;
	node * current = top;
	while (current != NULL)
	{
		newStack.push(current);
		current = current->link;
	}
	delete current;
	current = NULL;
	initializeStack();

	node * temp = new node;
	temp->name = newStack.top->name;
	temp->op = newStack.top->op;
	temp->value = newStack.top->value;
	temp->link = NULL;
	top = temp;

	node * current2 = newStack.top->link;
	node * current3 = top;
	while (current2 != NULL)
	{
		node * newNode = new node;
		newNode->name = current2->name;
		newNode->op = current2->op;
		newNode->value = current2->value;
		newNode->link = NULL;
		current3->link = newNode;
		current3 = newNode;
		current2 = current2->link;
	}
	
}
void stack::print()
{
	string total = performOps();
	cout << total << endl;
}
string stack::performOps()
{
	reverse();
	node * current = top;
	stack values;
	node * start = new node;
	start->name = current->name;
	start->op = "add";
	start->value = "0";
	values.push(start);
	delete start;
	start = NULL;
	while (current)
	{
		if (current->op == "open" && current->value == "bag")
		{
			int bagOpen = 1;
			int add = 0;
			current = current->link;
			while (bagOpen != 0)
			{
				if (current->op == "open" && current->value == "bag")
				{
					bagOpen++;
				}
				else if (current->op == "close" && current->value == "bag")
				{
					while (add != 0)
					{
						string num1 = values.getTop();
						values.pop();
						string num2 = values.getTop();
						values.pop();
						node * temp = new node;
						temp->name = current->name;
						temp->op = "add";
						temp->value = to_string(stoi(num1) + stoi(num2));
						values.push(temp);
						delete temp;
						temp = NULL;
						add--;
					}
					bagOpen--;
				}
				else if (current->op == "times")
				{
					node * temp = new node;
					temp->name = current->name;
					temp->op = "add";
					temp->value = to_string(stoi(values.getTop()) * stoi(current->value));
					values.pop();
					values.push(temp);
					delete temp;
					temp = NULL;
				}
				else if (current->op == "discount%")
				{
					node * temp = new node;
					temp->name = current->name;
					temp->op = "add";
					temp->value = to_string((stoi(values.getTop()) * (100 - stoi(current->value)) / 100));
					values.pop();
					values.push(temp);
					delete temp;
					temp = NULL;
				}
				else
				{
					node * temp = new node;
					temp->name = current->name;
					temp->op = "add";
					temp->value = current->value;
					values.push(temp);
					delete temp;
					temp = NULL;
					add++;
				}
				current = current->link;
			}
		}
		else
		{
			if (current->op == "times")
			{
				node * temp = new node;
				temp->name = current->name;
				temp->op = "times";
				temp->value = to_string(stoi(values.getTop()) * stoi(current->value));
				values.pop();
				values.push(temp);
				delete temp;
				temp = NULL;
			}
			else if (current->op == "discount%")
			{
				node * temp = new node;
				temp->name = current->name;
				temp->op = "discount";
				temp->value = to_string((stoi(values.getTop()) * (100 - stoi(current->value)))/100);
				values.pop();
				values.push(temp);
				delete temp;
				temp = NULL;
			}
			else
			{
				node * temp = new node;
				temp->name = current->name;
				temp->op = "add";
				temp->value = current->value;
				values.push(temp);
			}
			current = current->link;
		}
	}
	while (values.top->link != NULL)
	{
		string num1 = values.getTop();
		values.pop();
		string num2 = values.getTop();
		values.pop();
		node * temp = new node;
		temp->name = "";
		temp->op = "";
		temp->value = (to_string(stoi(num1) + stoi(num2)));
		values.push(temp);
		delete temp;
		temp = NULL;
	}
	return values.top->value;
}