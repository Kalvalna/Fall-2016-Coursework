#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

struct node
{
	string person;
	string subject;
	string body;
	node * link;
	node * prev;
};
class linkedList
{
private:
	node * head;
public:
	linkedList();
	void add(node *);
	void addNode(node *, node *);
	void deleteBySub(node *, string, string);
	void deleteMatch(node *, string, string, string);
	void deleteReserv();
	void deleteByReserv(node *);
	void deleteDupe();
	void deleteByDupe(node *);
	void deletePurch();
	void deleteByPurch(node *);
	void combine();
	void combineNot(node *, node *);
	int count(node *);
	void sizeArray(int[], linkedList[], int numOfLists);
	void mergeLists(linkedList[], int);
	void merge(linkedList[], int, int, int);
	void printRecursive(node *);
	void print();
};
vector<string> split(string s, char delim, vector<string> &vect)
{
	stringstream ss;
	ss.str(s);
	string tokens;
	getline(ss, tokens, delim);
	vect.at(0) = tokens;
	getline(ss, tokens, delim);
	vect.at(1) = tokens;
	getline(ss, tokens, delim);
	vect.at(2) = tokens;
	return vect;
}
bool fileExists(string filename)
{
	fstream file(filename);
	return (bool)file;
}
int indexOfLongest(int arr[], int size, int index, int count)
{
	if (size == 1)
	{
		return 0;
	}
	else
	{
		if (count < size)
		{
			if (arr[index] <= arr[count])
			{
				index = count;
				return indexOfLongest(arr, size, index, ++count);
			}
			else
			{
				return indexOfLongest(arr, size, index, ++count);
			}
		}
	}
	return index;
}
int counting(string filename, int count)
{
	if (fileExists(filename + to_string(count + 1) + ".txt"))
	{
		++count;
		return 1 + counting(filename, count);
	}
	return 0;
}
void addNodes(linkedList lists[], ifstream& file, int index)
{
	string line;
	if (getline(file, line))
	{
		if (line[0] == '#' || line == "")
		{
			addNodes(lists, file, index);
		}
		else
		{
			vector<string> vect(3);
			split(line, '\t', vect);
			node * temp = new node;
			temp->person = vect[0];
			temp->subject = vect[1];
			temp->body = vect[2];
			lists[index].add(temp);
			vect.clear();
			temp = NULL;
			delete temp;
			addNodes(lists, file, index);
		}
	}
}
void listsOfLists(linkedList lists[], string filename, int count, int start)
{
	ifstream file;
	string name = filename + to_string(start + 1) + ".txt";
	file.open(name.c_str());
	if (start < count)
	{
		addNodes(lists, file, start);
		lists[start].deleteDupe();
		lists[start].deleteReserv();
		lists[start].deletePurch();
		lists[start].combine();
		file.close();
		listsOfLists(lists, filename, count, ++start);
	}
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
	size_t pos = filename.find("1.txt");
	filename = filename.substr(0, pos);

	int count = counting(filename, 0);
	linkedList * lists = new linkedList[count];
	listsOfLists(lists, filename, count, 0);

	linkedList global;
	global.mergeLists(lists, count);
	global.deleteDupe();
	global.combine();
	global.print();

	return 0;
}
linkedList::linkedList()
{
	head = NULL;
}
void linkedList::add(node * newNode)
{
	addNode(head, newNode);
}
void linkedList::addNode(node * start, node * newNode)
{
	if (start == NULL)
	{
		node * temp = new node;
		temp->person = newNode->person;
		temp->subject = newNode->subject;
		temp->body = newNode->body;
		temp->link = NULL;
		temp->prev = NULL;
		head = temp;
		temp = NULL;
		delete temp;
	}
	else if (start->link == NULL)
	{
		node * temp = new node;
		temp->person = newNode->person;
		temp->subject = newNode->subject;
		temp->body = newNode->body;
		temp->link = NULL;
		start->link = temp;
		start->link->prev = start;
		temp = NULL;
		delete temp;
	}
	else
	{
		addNode(start->link, newNode);
	}
}
void linkedList::deleteBySub(node * start, string s1, string s2)
{
	if (start)
	{
		if (head->subject == s1 && head->body == s2)
		{
			node * temp = head;
			if (head->link)
			{
				head->link->prev = NULL;
				head = head->link;
				start = head;
			}
			else
			{
				head = NULL;
				start = head;
			}
			temp = NULL;
			delete temp;
			if (start)
			{
				deleteBySub(start, s1, s2);
			}
		}
		else if (start->subject == s1 && start->body == s2)
		{
			if (start->link)
			{
				node * temp = start;
				start->prev->link = start->link;
				start->link->prev = start->prev;
				start = start->link;
				temp = NULL;
				delete temp;
				deleteBySub(start, s1, s2);
			}
			else
			{
				start->prev->link = NULL;
				start = NULL;
				delete start;
			}
		}
		else
		{
			if (start->link)
			{
				deleteBySub(start->link, s1, s2);
			}
		}
	}
}
void linkedList::deleteMatch(node * start, string s1, string s2, string s3)
{
	if (start)
	{
		if (start->person == s1, start->subject == s2 && start->body == s3)
		{
			if (start->link)
			{
				node * temp = start;
				start->prev->link = start->link;
				start->link->prev = start->prev;
				start = start->link;
				temp = NULL;
				delete temp;
				deleteMatch(start, s1, s2, s3);
			}
			else
			{
				start->prev->link = NULL;
				start = NULL;
				delete start;
			}
		}
		else
		{
			if (start->link)
			{
				deleteMatch(start->link, s1, s2, s3);
			}
		}
	}
}
void linkedList::deleteReserv()
{
	deleteByReserv(head);
}
void linkedList::deleteByReserv(node * start)
{
	if (start)
	{
		if (start->subject == "Approve-reservation(Cancelled)")
		{
			deleteBySub(head, "Approve-reservation", start->body);
			deleteBySub(head, "Approve-reservation(Cancelled)", start->body);
			if (start->link)
			{
				deleteByReserv(start->link);
			}
		}
		else
		{
			if (start->link)
			{
				deleteByReserv(start->link);
			}
		}
	}
}
void linkedList::deleteByDupe(node * start)
{
	if (start)
	{
		node * temp = start;
		deleteMatch(temp->link, start->person, start->subject, start->body);
		temp = NULL;
		delete temp;
		if (start->link)
		{
			deleteByDupe(start->link);
		}
	}
}
void linkedList::deleteDupe()
{
	deleteByDupe(head);
}
void linkedList::deletePurch()
{
	deleteByPurch(head);
}
void linkedList::deleteByPurch(node * start)
{
	if (start)
	{
		if (start->subject == "Purchase-order-cancellation")
		{
			deleteBySub(head, "Approve-purchase-order", start->body);
			deleteBySub(head, "Purchase-order-revise", start->body);
			if (start->link)
			{
				deleteByPurch(start->link);
			}
		}
		else if (start->subject == "Purchase-order-revise")
		{
			deleteBySub(head, "Approve-purchase-order", start->body);
			if (start->link)
			{
				deleteByPurch(start->link);
			}
		}
		else
		{
			if (start->link)
			{
				deleteByPurch(start->link);
			}
		}
	}
}
void linkedList::combine()
{
	combineNot(head, head);
}
void linkedList::combineNot(node * start, node * current)
{
	if (start)
	{
		if (current->link)
		{
			if (current->link->person == start->person && current->link->subject == start->subject && current->link->body != start->body)
			{
				if (current->link)
				{
					start->body = start->body + ", " + current->link->body;
					node * temp = current->link;
					current->link = current->link->link;
					if (current->link)
					{
						current->link->prev = current;
						current = current->link;
					}
					temp = NULL;
					delete temp;
					combineNot(start, current);
				}
			}
			else
			{
				combineNot(start, current->link);
			}
		}
		else
		{
			if (start->link)
			{
				combineNot(start->link, start);
			}
		}
	}
}
int linkedList::count(node * start)
{
	if (start)
	{
		if (start->link)
		{
			return 1 + count(start->link);
		}
		else
		{
			return 1;
		}
	}
}
void linkedList::sizeArray(int size[], linkedList lists[], int numOfLists)
{
	if (numOfLists != 0)
	{
		size[numOfLists - 1] = lists[numOfLists - 1].count(lists[numOfLists - 1].head);
		sizeArray(size, lists, numOfLists - 1);
	}
}
void linkedList::mergeLists(linkedList lists[], int numOfLists)
{
	int longest;
	int * sizes = new int[numOfLists];
	sizeArray(sizes, lists, numOfLists);
	longest = indexOfLongest(sizes, numOfLists, 0, 0);
	int count = 0;
	merge(lists, longest, count, numOfLists);
	sizes = NULL;
	delete sizes;
}
void linkedList::merge(linkedList lists[], int indexOfLongest, int count, int numOfLists)
{
	if (lists[indexOfLongest].head)
	{
		if (lists[count % numOfLists].head)
		{
			addNode(head, lists[count % numOfLists].head);
			lists[count % numOfLists].head = lists[count % numOfLists].head->link;
			merge(lists, indexOfLongest, ++count, numOfLists);
		}
		else
		{
			merge(lists, indexOfLongest, ++count, numOfLists);
		}
	}
}
void linkedList::print()
{
	printRecursive(head);
}
void linkedList::printRecursive(node * start)
{
	if (start)
	{
		cout << start->person << "\t" << start->subject << "\t" << start->body << endl;
		if (start->link)
		{
			printRecursive(start->link);
		}
	}
}
