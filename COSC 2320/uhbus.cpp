#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct family {
	string name;
	string size;
};
class queue {
private:
	family * fam[500];
	queue * bus;
	int busSize;
	int front;
	int rear;
public:
	queue();
	void setBusSize(int);
	void push(string, string);
	void pop();
	void fillBuses();
	int remaining();
	bool isFull();
	bool isEmpty();
	void print(int);
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
	
	queue busQueue;
	string line;
	while (getline(file, line))
	{
		if (line[0] == '#' || line == "")
		{
			continue;
		}
		vector<string> vect(2);
		split(line, '\t', vect);
		if (vect[0] == "bus:")
		{
			busQueue.setBusSize(stoi(vect[1]));
			vect.clear();
		}
		else
		{
			busQueue.push(vect[0], vect[1]);
			vect.clear();
		}
	}
	busQueue.fillBuses();
	file.close();
	return 0;
}

queue::queue()
{
	front = -1;
	rear = -1;
}
void queue::setBusSize(int size)
{
	busSize = size;
}
void queue::push(string fName, string fSize)
{
	if (front == -1)
	{
		front = 0;
		rear = 0;
		family * temp = new family;
		temp->name = fName;
		temp->size = fSize;
		fam[rear] = temp;
		temp = NULL;
		delete temp;
	}
	else
	{
		rear++;
		family * temp = new family;
		temp->name = fName;
		temp->size = fSize;
		fam[rear] = temp;
		temp = NULL;
		delete temp;
	}
}
void queue::pop()
{
	front++;
}
void queue::fillBuses()
{
	if (!isEmpty())
	{
		bus = new queue[100];
		while (front <= rear)
		{
			for (int i = 0; i < 100; i++)
			{
				if (bus[i].isEmpty())
				{
					bus[i].push(fam[front]->name, fam[front]->size);
					pop();
					bus[i].setBusSize(busSize);
					break;
				}
				else if (!bus[i].isFull() && stoi(fam[front]->size) <= bus[i].remaining())
				{
					bus[i].push(fam[front]->name, fam[front]->size);
					pop();
					if (bus[i].isFull())
					{
						bus[i].print(i);
					}
					break;
				}
				else
				{
					continue;
				}
			}
		}
		for (int i = 0; i < 100; i++)
		{
			if (bus[i].isEmpty())
			{
				break;
			}
			else if (!bus[i].isFull() && !bus[i].isEmpty())
			{
				bus[i].print(i);
			}
		}
	}
	bus = NULL;
	delete[] bus;
}
int queue::remaining()
{
	int total = 0;
	int i = front;
	while (i <= rear)
	{
		total += stoi(fam[i]->size);
		i++;
	}
	return busSize - total;
}
bool queue::isFull()
{
	return remaining() == 0;
}
bool queue::isEmpty()
{
	return front == -1;
}
void queue::print(int busNum)
{
	int i = front;
	while (i <= rear)
	{
		cout << "bus" + to_string(busNum + 1) << "\t" << fam[i]->name << endl;
		i++;
	}
}