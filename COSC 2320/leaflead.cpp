#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

struct node {
	string name;
	string GPA;
	string CST;
	string leader;
	int score;
	node * child1;
	node * child2;
	node * child3;
	node * child4;
};
class tree {
private:
	int first;
	int last;
	int count;
	node * unsorted[1298];
	node * root;
	node * printList[1298];
public:
	tree();
	void addNode(string, string, string, string);
	void insertLeaves(node *);
	void establishRoot();
	bool nameCheck(node *, node *);
	void createTree();
	void calcScores();
	void print(string);
	void printLeaves(node *);
	void printLead1(node *);
	void printLead2(node *);
	void heapsort();
	void buildHeap();
	void heapify(int, int);
	void addToPrint(node *);
};
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
	string line;
	tree oak;

	while (getline(file, line))
	{
		if (line[0] == '#' || line == "")
		{
			continue;
		}
		vector<string> vect(5);
		split(line, '\t', vect);
		if (vect[0] == "instructions")
		{
			oak.print(vect[1]);
		}
		else
		{
			oak.addNode(vect[0], vect[1], vect[2], vect[3]);
		}
	}

	file.close();

	return 0;
}

tree::tree()
{
	first = -1;
	last = -1;
	count = 0;
}
void tree::addNode(string a, string b, string c, string d)
{
	if (first == -1)
	{
		first = 0;
		last = 0;
		node * temp = new node;
		temp->name = a;
		temp->GPA = b;
		temp->CST = c;
		temp->leader = d;
		temp->child1 = NULL;
		temp->child2 = NULL;
		temp->child3 = NULL;
		temp->child4 = NULL;
		unsorted[last] = temp;
		temp = NULL;
		delete temp;
	}
	else
	{
		last++;
		node * temp = new node;
		temp->name = a;
		temp->GPA = b;
		temp->CST = c;
		temp->leader = d;
		temp->child1 = NULL;
		temp->child2 = NULL;
		temp->child3 = NULL;
		temp->child4 = NULL;
		unsorted[last] = temp;
		temp = NULL;
		delete temp;
	}
}
void tree::insertLeaves(node * current)
{
	if (current != NULL)
	{
		for (int i = 0;i <= last; i++)
		{
			if (unsorted[i]->leader == current->name && unsorted[i]->leader != unsorted[i]->name)
			{
				if (current->child1 == NULL && !nameCheck(current, unsorted[i]))
				{
					current->child1 = unsorted[i];
				}
				else if (current->child2 == NULL && !nameCheck(current, unsorted[i]))
				{
					current->child2 = unsorted[i];
				}
				else if (current->child3 == NULL && !nameCheck(current, unsorted[i]))
				{
					current->child3 = unsorted[i];
				}
				else if (current->child4 == NULL && !nameCheck(current, unsorted[i]))
				{
					current->child4 = unsorted[i];
				}
			}
		}
		if (current->child1 != NULL)
		{
			insertLeaves(current->child1);
		}
		if (current->child2 != NULL)
		{
			insertLeaves(current->child2);
		}
		if (current->child3 != NULL)
		{
			insertLeaves(current->child3);
		}
		if (current->child4 != NULL)
		{
			insertLeaves(current->child4);
		}
	}
}
void tree::establishRoot()
{
	for (int i = 0; i <= last; i++)
	{
		if (unsorted[i]->name == unsorted[i]->leader)
		{
			root = unsorted[i];
			break;
		}
	}
}
bool tree::nameCheck(node * current, node * check)
{
	if (current->child1 != NULL)
	{
		if (current->child1->name == check->name)
		{
			return true;
		}
	}
	if (current->child2 != NULL)
	{
		if (current->child2->name == check->name)
		{
			return true;
		}
	}
	if (current->child3 != NULL)
	{
		if (current->child3->name == check->name)
		{
			return true;
		}
	}
	if (current->child4 != NULL)
	{
		if (current->child4->name == check->name)
		{
			return true;
		}
	}
	return false;
}
void tree::createTree()
{
	calcScores();
	establishRoot();
	insertLeaves(root);
}
void tree::calcScores()
{
	for (int i = 0; i <= last; i++)
	{
		unsorted[i]->score = stof(unsorted[i]->GPA) * 200 + stoi(unsorted[i]->CST);
	}
}
void tree::print(string instruction)
{
	createTree();
	if (instruction == "leaves")
	{
		printLeaves(root);
	}
	else if (instruction == "lead1")
	{
		printLead1(root);
	}
	else if (instruction == "lead2")
	{
		printLead2(root);
	}
	count = count - 1;
	heapsort();
	if (printList[0] != NULL)
	{
		for (int i = count; i >= 0; i--)
		{
			cout << printList[i]->name << endl;
		}
	}
}
void tree::printLeaves(node * current)
{
	if (current != NULL)
	{
		if (current->child1 == NULL)
		{
			addToPrint(current);
		}
		if (current->child1 != NULL)
		{
			printLeaves(current->child1);
		}
		if (current->child2 != NULL)
		{
			printLeaves(current->child2);
		}
		if (current->child3 != NULL)
		{
			printLeaves(current->child3);
		}
		if (current->child4 != NULL)
		{
			printLeaves(current->child4);
		}
	}
}
void tree::printLead1(node * current)
{
	if (current != NULL)
	{
		if (current->child1 != NULL)
		{
			if (current->child1->child1 == NULL)
			{
				addToPrint(current);
			}
		}
		if (current->child2 != NULL)
		{
			if (current->child2->child1 == NULL)
			{
				addToPrint(current);
			}
		}
		if (current->child3 != NULL)
		{
			if (current->child3->child1 == NULL)
			{
				addToPrint(current);
			}
		}
		if (current->child4 != NULL)
		{
			if (current->child4->child1 == NULL)
			{
				addToPrint(current);
			}
		}
		if (current->child1 != NULL)
		{
			printLead1(current->child1);
		}
		if (current->child2 != NULL)
		{
			printLead1(current->child2);
		}
		if (current->child3 != NULL)
		{
			printLead1(current->child3);
		}
		if (current->child4 != NULL)
		{
			printLead1(current->child4);
		}
	}
}
void tree::printLead2(node * current)
{
	if (current != NULL && current->child1 != NULL)
	{
		if (current->child1 != NULL)
		{
			if (current->child1->child1 != NULL)
			{
				if (current->child1->child1->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child1->child2 != NULL)
			{
				if (current->child1->child2->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child1->child3 != NULL)
			{
				if (current->child1->child3->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child1->child4 != NULL)
			{
				if (current->child1->child1->child4 == NULL)
				{
					addToPrint(current);
				}
			}
		}
		if (current->child2 != NULL)
		{
			if (current->child2->child1 != NULL)
			{
				if (current->child2->child1->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child2->child2 != NULL)
			{
				if (current->child2->child2->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child2->child3 != NULL)
			{
				if (current->child2->child3->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child2->child4 != NULL)
			{
				if (current->child2->child1->child4 == NULL)
				{
					addToPrint(current);
				}
			}
		}
		if (current->child3 != NULL)
		{
			if (current->child3->child1 != NULL)
			{
				if (current->child3->child1->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child3->child2 != NULL)
			{
				if (current->child3->child2->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child3->child3 != NULL)
			{
				if (current->child3->child3->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child3->child4 != NULL)
			{
				if (current->child3->child1->child4 == NULL)
				{
					addToPrint(current);
				}
			}
		}
		if (current->child4 != NULL)
		{
			if (current->child4->child1 != NULL)
			{
				if (current->child4->child1->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child4->child2 != NULL)
			{
				if (current->child4->child2->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child4->child3 != NULL)
			{
				if (current->child4->child3->child1 == NULL)
				{
					addToPrint(current);
				}
			}
			if (current->child4->child4 != NULL)
			{
				if (current->child4->child1->child4 == NULL)
				{
					addToPrint(current);
				}
			}
		}
		if (current->child1 != NULL)
		{
			printLead2(current->child1);
		}
		if (current->child2 != NULL)
		{
			printLead2(current->child2);
		}
		if (current->child3 != NULL)
		{
			printLead2(current->child3);
		}
		if (current->child4 != NULL)
		{
			printLead2(current->child4);
		}
	}
}
void tree::heapsort()
{
	buildHeap();
	for (int i = count; i >= 0; i--)
	{
		node * temp = new node;
		temp = printList[i];
		printList[i] = printList[0];
		printList[0] = temp;
		heapify(0, i - 1);
		temp = NULL;
		delete temp;
	}
}
void tree::buildHeap()
{
	for (int i = (count + 1) / 2 - 1; i >= 0; i--)
	{
		heapify(i, count);
	}
}
void tree::heapify(int low, int high)
{
	int large;
	node * temp = printList[low];
	large = 2 * low + 1;
	while (large <= high)
	{
		if (large < high)
		{
			if (printList[large]->score < printList[large + 1]->score)
			{
				large = large + 1;
			}
		}
		if (temp->score > printList[large]->score)
		{
			break;
		}
		else
		{
			printList[low] = printList[large];
			low = large;
			large = 2 * low + 1;
		}
	}
	printList[low] = temp;
}
void tree::addToPrint(node * n1)
{
	for (int i = 0; i <= count; i++)
	{
		if (printList[i] == n1)
		{
			break;
		}
		else
		{
			if (printList[i] == NULL)
			{
				printList[count] = n1;
				count++;
				break;
			}
		}
	}
}