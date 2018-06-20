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
};
class linkedList
{
private:
	node * head;
public:
	linkedList();
	void addNode(node*);
	void deleteReserv();
	void deleteDupe();
	void deletePurch();
	void combine();
	int count();
	void mergeLists(linkedList[], int);
	void print();
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
bool fileExists(string filename)
{
	fstream file(filename);
	return (bool)file;
}
int indexOfLongest(int arr[], int size)
{
	int index = 0;
	for (int i = index; i < size; i++)
	{
		if (arr[index] < arr[i])
		{
			index = i;
		}
	}
	return index;
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
	ifstream file;

	int count = 0;
	while (fileExists(filename + to_string(count + 1) + ".txt"))
	{
		count++;
	}

	linkedList * lists = new linkedList[count];
	for (int i = 0; i < count; i++)
	{
		string name = filename + to_string(i + 1) + ".txt";
		file.open(name.c_str());
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
			temp->person = vect[0];
			temp->subject = vect[1];
			temp->body = vect[2];
			lists[i].addNode(temp);
			vect.clear();
			temp = NULL;
			delete temp;
		}
		lists[i].deleteDupe();
		lists[i].deleteReserv();
		lists[i].deletePurch();
		lists[i].combine();
		file.close();
	}

	linkedList global;
	global.mergeLists(lists, count);
	global.combine();
	global.deleteDupe();
	global.print();

	return 0;
}
linkedList::linkedList()
{
	head = NULL;
}
void linkedList::addNode(node* temp)
{
	node * newNode = new node;
	newNode->person = temp->person;
	newNode->subject = temp->subject;
	newNode->body = temp->body;
	newNode->link = NULL;
	if (head == NULL)
	{
		head = newNode;
	}
	else
	{
		node * last = head;
		while (last->link != NULL)
		{
			last = last->link;
		}
		last->link = newNode;
	}
	newNode = NULL;
	delete newNode;
}
void linkedList::deleteReserv()
{
	if (head)
	{
		node * cancel = head;
		while (cancel->link)
		{
			if (cancel->link->subject == "Approve-reservation(Cancelled)")
			{
				if (head->body == cancel->link->body && head->person == cancel->link->person && head->subject == "Approve-reservation")
				{
					node * temp1 = cancel->link;
					cancel->link = cancel->link->link;
					node * temp = head;
					head = head->link;
					delete temp;
					temp = NULL;
					delete temp1;
					temp = NULL;
					cancel = head;
					if (head == NULL) { break; }
				}
				else
				{
					node * approve = head;
					while (approve)
					{
						if (approve->link)
						{
							if (approve->link->body == cancel->link->body && approve->link->person == cancel->link->person && approve->link->subject == "Approve-reservation")
							{
								node * temp = approve->link;
								approve->link = approve->link->link;
								delete temp;
								temp = NULL;
								break;
							}
							else
							{
								approve = approve->link;
							}
						}
						else
						{
							approve = NULL;
							delete approve;
						}
					}
					node * temp = cancel->link;
					cancel->link = cancel->link->link;
					delete temp;
					temp = NULL;
				}
			}
			else
			{
				cancel = cancel->link;
			}
		}
		cancel = NULL;
		delete cancel;
	}
}
void linkedList::deleteDupe()
{
	node * base = head;
	while (base != NULL && base->link != NULL)
	{
		node * current = base;
		while (current)
		{
			if (current->link)
			{
				if (current->link->body == base->body && current->link->person == base->person && current->link->subject == base->subject)
				{
					node * temp = current->link;
					current->link = current->link->link;
					delete temp;
				}
				else
				{
					current = current->link;
				}
			}
			else
			{
				current = NULL;
				delete current;
			}
		}
		base = base->link;
	}
	base = NULL;
	delete base;
}
void linkedList::deletePurch()
{
	if (head)
	{
		node * message = head;
		while (message)
		{
			if (message->subject == "Purchase-order-cancellation")
			{
				node * approve = head;
				while (approve->body == message->body && (approve->subject == "Approve-purchase-order" || approve->subject == "Purchase-order-revise"))
				{
					node * temp = head;
					head = approve->link;
					approve = approve->link;
					delete temp;
				}
				while (approve)
				{
					if (approve->link)
					{
						if (approve->link->body == message->body && (approve->link->subject == "Approve-purchase-order" || approve->link->subject == "Purchase-order-revise"))
						{
							node * temp = approve->link;
							approve->link = approve->link->link;
							delete temp;
						}
						else
						{
							approve = approve->link;
						}
					}
					else
					{
						approve = NULL;
						delete approve;
					}
				}
				message = message->link;
			}
			else
			{
				message = message->link;
			}
		}
		message = NULL;
		delete message;
	}
}
void linkedList::combine()
{
	if (head)
	{
		node * base = head;
		while (base)
		{
			node * current = head;
			while (current)
			{
				if (current->link)
				{
					if (current->link->subject == base->subject && current->link->person == base->person && current->link->body != base->body)
					{
						base->body = base->body + ", " + current->link->body;
						node * temp = current->link;
						current->link = current->link->link;
						current = current->link;
						delete temp;
					}
					else
					{
						current = current->link;
					}
				}
				else
				{
					current = NULL;
					delete current;
				}
			}
			base = base->link;
		}
		base = NULL;
		delete base;
	}
}
int linkedList::count()
{
	node * temp = head;
	int length = 0;
	while (temp)
	{
		length++;
		temp = temp->link;
	}
	temp = NULL;
	delete temp;
	return length;
}
void linkedList::mergeLists(linkedList lists[], int numOfLists)
{
	int longest;
	int * sizes = new int[numOfLists];
	for (int i = 0; i < numOfLists; i++)
	{
		sizes[i] = lists[i].count();
	}
	longest = indexOfLongest(sizes, numOfLists);
	while (lists[longest].head != NULL)
	{
		for (int i = 0; i < numOfLists; i++)
		{
			if (lists[i].head == NULL)
			{
				continue;
			}
			else
			{
				addNode(lists[i].head);
				lists[i].head = lists[i].head->link;
			}
		}
	}
	sizes = NULL;
	delete sizes;
}
void linkedList::print()
{
	node * temp = head;
	while (temp != NULL)
	{
		cout << temp->person << "\t" << temp->subject << "\t" << temp->body << endl;
		temp = temp->link;
	}
	temp = NULL;
	delete temp;
}
