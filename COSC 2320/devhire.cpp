#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

struct candidate {
	string name;
	string GPA;
	string CST;
	string gender;
	string un;
	int score;
};
class interviewSelect {
private:
	candidate * cands[999];
	int first;
	int last;
	int numOfMales;
	int numOfFem;
	int numOfOther;
public:
	interviewSelect();
	void heapsort();
	void buildHeap();
	void heapify(int, int);
	void addCand(string, string, string, string, string);
	void setInstr(int, int, int);
	int UNcheck(candidate*);
	void calcScores(int);
	bool nameCheck(string);
	void choose();
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
	if (i < 5)
	{
		while (i < 5)
		{
			vect.at(i) = "";
			i++;
		}
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
	interviewSelect choose;

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
			choose.setInstr(stoi(vect[1]), stoi(vect[2]), stoi(vect[3]));
			vect.clear();
		}
		else
		{
			choose.addCand(vect[0], vect[1], vect[2], vect[3], vect[4]);
			vect.clear();
		}
	}
	choose.choose();
	file.close();

	return 0;
}

interviewSelect::interviewSelect()
{
	first = -1;
	last = -1;
}
void interviewSelect::addCand(string a, string b, string c, string d, string e)
{
	if (first == -1)
	{
		first = 0;
		last = 0;
		candidate * temp = new candidate;
		temp->name = a;
		temp->GPA = b;
		temp->CST = c;
		temp->gender = d;
		temp->un = e;
		cands[last] = temp;
		temp = NULL;
		delete temp;
	}
	else
	{
		last++;
		candidate * temp = new candidate;
		temp->name = a;
		temp->GPA = b;
		temp->CST = c;
		temp->gender = d;
		temp->un = e;
		cands[last] = temp;
		temp = NULL;
		delete temp;
	}
}
void interviewSelect::heapsort()
{
	buildHeap();
	for (int i = last; i >= 0; i--)
	{
		candidate * temp = new candidate;
		temp = cands[i];
		cands[i] = cands[0];
		cands[0] = temp;
		heapify(0, i - 1);
		temp = NULL;
		delete temp;
	}
}
void interviewSelect::buildHeap()
{
	for (int i = (last + 1) / 2 - 1; i >= 0; i--)
	{
		heapify(i, last);
	}
}
void interviewSelect::heapify(int low, int high)
{
	int large;
	candidate * temp = cands[low];
	large = 2 * low + 1;
	while (large <= high)
	{
		if (large < high)
		{
			if (cands[large]->score < cands[large + 1]->score)
			{
				large = large + 1;
			}
		}
		if (temp->score > cands[large]->score)
		{
			break;
		}
		else
		{
			cands[low] = cands[large];
			low = large;
			large = 2 * low + 1;
		}
	}
	cands[low] = temp;
}
void interviewSelect::setInstr(int a, int b, int c)
{
	numOfFem = a;
	numOfMales = b;
	numOfOther = c;
}
int interviewSelect::UNcheck(candidate * a)
{
	if (a->un == "")
	{
		return 0;
	}
	else
	{
		return 10;
	}
}
void interviewSelect::calcScores(int x)
{
	int current = 0;
	while (current <= last)
	{
		cands[current]->score = stof(cands[current]->GPA) * 10 * (20 - x) + stoi(cands[current]->CST) - x * 2 + UNcheck(cands[current]);
		current++;
	}
}
bool interviewSelect::nameCheck(string a)
{
	if (first == -1)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < last + 1; i++)
		{
			if (cands[i]->name == a)
			{
				return false;
			}
		}
	}
}
void interviewSelect::choose()
{
	int x = 0;
	interviewSelect selected;
	while (x <= 20)
	{
		if (selected.last != last)
		{
			calcScores(x);
			heapsort();
			int femRemain = numOfFem;
			int maleRemain = numOfMales;
			int otherRemain = numOfOther;
			for (int i = last; i >= 0; i--)
			{
				if (cands[i]->gender == "female" && femRemain > 0 && selected.nameCheck(cands[i]->name))
				{
					cout << cands[i]->name << endl;
					selected.addCand(cands[i]->name, cands[i]->GPA, cands[i]->CST, cands[i]->gender, cands[i]->un);
					femRemain--;
				}
				else if (femRemain == 0)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			for (int i = last; i >= 0; i--)
			{
				if (cands[i]->gender == "male" && maleRemain > 0 && selected.nameCheck(cands[i]->name))
				{
					cout << cands[i]->name << endl;
					selected.addCand(cands[i]->name, cands[i]->GPA, cands[i]->CST, cands[i]->gender, cands[i]->un);
					maleRemain--;
				}
				else if (maleRemain == 0)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			for (int i = last; i >= 0; i--)
			{
				if (!(cands[i]->gender == "female" || cands[i]->gender == "male") && otherRemain > 0 && selected.nameCheck(cands[i]->name))
				{
					cout << cands[i]->name << endl;
					selected.addCand(cands[i]->name, cands[i]->GPA, cands[i]->CST, cands[i]->gender, cands[i]->un);
					otherRemain--;
				}
				else if (otherRemain == 0)
				{
					break;
				}
				else
				{
					continue;
				}
			}
			x += 3;
		}
		else
		{
			break;
		}
	}
}