#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Functions that check if character is a number
bool isNum(char x)
{
	return x >= '0' && x <= '9';
}

// Function that checks if a string is an int
bool isInt(string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (!isNum(str[i]))
		{
			return false;
		}
	}
	return true;
}

// Function that converts a string to all lowercase
string lower(string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}
	return str;
}

// Function that replaces all symbols with spaces
string replaceSymbol(string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		switch (str[i]) {
		case ',':
		case '(':
		case ')':
		case ';':
			str[i] = ' ';
			break;
		case '.':
			if (!isNum(str[i - 1]))
			{
				str[i] = ' ';
			}
			break;
		default:
			break;
		}
	}
	return str;
}
// Function that removes extra spaces in order to keep count correct
string removeExtraSpaces(string str)
{
	for (unsigned int i = 1; i < str.length(); i++)
	{
		if (str[i] == ' ')
		{
			if (str[i - 1] == ' ')
			{
				str.erase(str.begin() + i);
			}
			else if (i == str.length() - 1)
			{
				str.erase(str.begin() + i);
			}
		}
	}
	return str;
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cout << "Error. Parameter not correctly specified." << endl;
		return 0;
	}
	string parameter(argv[1]);
	string filename = parameter.substr(6);

	string line;
	int min = 0;
	int hour = 0;
	int day = 0;

	ifstream myFile(filename);				// Opens file for reading

	if (myFile.is_open())					// Checks if file opened without any errors
	{
		while (getline(myFile, line))
		{
			// Checks if line starts with '#' and goes to next iteration
			if (line[0] == '#')
			{
				continue;
			}

			// Replaces symbols with spaces, changes all characters to lowercase, and removes extra spaces
			line = replaceSymbol(line);
			line = lower(line);
			line = removeExtraSpaces(line);

			// Creates a dynamic array that has a size equal to the number of words
			vector<string> tokens;
			int numOfWords = 0;
			stringstream ss;
			ss.str(line);
			string element;
			while (getline(ss, element, ' '))
			{
				tokens.push_back(element);
				++numOfWords;
			}

			// Iterates through each element in the array to check if it is one of the words
			for (int i = 1; i < numOfWords; i++)
			{
				// If one of the words is found, checks if previous element was an int
				if (tokens[i] == "minute" || tokens[i] == "minutes")
				{
					if (isInt(tokens[i - 1]))
					{
						min += stoi(tokens[i - 1]);
					}
				}
				else if (tokens[i] == "hour" || tokens[i] == "hours")
				{
					if (isInt(tokens[i - 1]))
					{
						hour += stoi(tokens[i - 1]);
					}
				}
				else if (tokens[i] == "day" || tokens[i] == "days")
				{
					if (isInt(tokens[i - 1]))
					{
						day += stoi(tokens[i - 1]);
					}
				}
			}
		}
	}
	// Displays message if file fails to open
	else
	{
		cout << "Error. Could not open file." << endl;
	}

	// Outputs total minutes, hours, and days
	cout << "Minutes: " << min << endl;
	cout << "Hours: " << hour << endl;
	cout << "Days: " << day << endl;

	myFile.close();

	return 0;
}

