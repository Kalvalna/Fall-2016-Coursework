# hw4 Bus Queue, due: Saturday Nov. 5th at 11:50pm

You will create a C++ program that will simulate the departure of buses when people get into them but they are families that would rather wait for the next bus than having family members going in different buses. 
The fundamental data structure will be array-based queues.

## Input 

The input is a plain-text file, where each line is terminated with an end-of-line character.
Each line will identify the arrival of a family consisting of at least two people.
Lines in the input file that start with the symbol `#` should be considered comments and therefore skipped.

Example 1:

    #family name and # of people
    bus:  10
    Hunt  4
    Avery 3
    Karev 2
    Grey 4
    Bailey 3
    Burke 4
    Torres 2

Each line that is not a comment will have exactly two items: name, and an integer indicating the number of people in the family.
Such items will be separated by one tab character (that is, `\t`).
There may be empty lines in the input file but there will always be at least one line with data.
There is a special line that will appear before any data of family members: the bus size. For such special line, the first item will be exacty the string `bus:` and the second item will be the size (or capacity of seats) for the bus.

## Theory

You must use arrays to simulate a queue (or more than 1 if needed).
You are encouraged to write your program so that it processes each line of the input file only once as it is reading the file. 

## Program specification

The main program should be called `uhbus` and the syntax in which it will be tested is as follows:

`uhbus "input=FILENAME"`

The parameter `input` specifies the name of the input file.

Example of program calls:

`uhbus "input=gray.txt"`

## Output

Your program will output to the console (such as via cout, or printf) where each line consistes of two items separated by one tab character.
The first item is the bus name, where the first bus is `bus1`, the second bus is `bus2`, the third bus is `bus3`, and so on and so forth.
The second item is the name of a family in the bus.
Your program must follow the output format exactly to facilitate automated grading (and to avoid failing test cases due to things such as output of an empty line at the end).

Output for the input example when the bus size is set to 40.

    bus1  Hunt  
    bus1  Avery 
    bus1  Karev 
    bus1  Grey
    bus1  Bailey 
    bus1  Burke 
    bus1  Torres 
    
Output for the input example when the bus size is set to 10.

    bus1  Hunt  
    bus1  Avery 
    bus1  Karev 
    bus2  Grey 
    bus2  Bailey 
    bus2  Torres 
    bus3  Burke 

Output for the input example when the bus size is set to 9 (maybe they sent a large SUV instead of a bus).

    bus1  Hunt 
    bus1  Avery 
    bus1  Karev 
    bus2  Grey 
    bus2  Bailey 
    bus2  Torres 
    bus3  Burke 
    

Every line should have an end of line character, such as output via:

`cout << bus << "\t" << name << endl;`

## Assumptions

* The input file can fit in main maimory (not larger than 10kb) and it will always have at least one line of data to work with.
* Names of people are all letters only and exactly one word (no bigger than 100 characters)
* The number of people is always a number greater or equal than 2, and smaller than the size of a bus.
* The minimum number of seats of a bus is 9
* The maximum number of seats of a bus is 500
* There will not be repeated names in the input file
* The maximum number of family names is 500
* The maximum number of buses to handle is 100

## Requirements

* You must build your own queue (array-based recommended, and in a class). Use queues as you see fit in your program.
* Place your codes in a folder named: `hw4` (Failure to do so will cause your program to have a zero grade due to inability for doing automated grading).
* Your program should not produce any unexpected output when it is doing intermediate calculations because doing so will interfere with automated grading and some test cases will fail.
* When a bus is full to its exact capacity it departs. The action that your program needs to do is output the bus information.
* When a bus is not full to its exact capacity, it has to wait until that is the case, or until no more people need to board (which is the time to output the bus information, in the order of the bus number).
* When a family decides to take the next bus, they immediately go into such next bus. If that causes the bus to be full, then the bus departs.
