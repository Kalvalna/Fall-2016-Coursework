# hw0, Minutes of Action. Due: Thursday September 8th at 10:00 p.m.

## Update: Example of ["Tokenize"](http://stackoverflow.com/documentation/c%2b%2b/488/stdstring/2148/tokenize#t=201609071057161048622) to 'break' a string into pieces using one or more separators (also known as 'delimiters', such as space character, and comma)

You will create a C++ program that will count the total of minutes, hours, and days mentioned inside of a plain-text file.

## Input 

The input is a plain-text file, where each line is terminated with an end-of-line character.
Each line will have words or numbers.
To simplify we will assume that there will not be words containing numbers such as the word: car4sale. (Or numbers containg letters such as 22E01). A word is a string of letters (upper and lower case).
Lines in the input file that start with the symbol `#` should be considered comments and therefore skipped.

Example 1:

    A person of interest travels 20 minutes each day.
    Meredith travels 1 hour by train to visit Derek. However, Derek can visit her in one minute
    #this line is a comment because it starts with #
    #for example, this comment line contains 1000 minutes but they do not get added anywhere
    Cristina does 4 minutes of yoga on her lunch break; she's done that in the last 3 weeks. 
    She can drink 3 minutemaid bottles a day.

Each line that is not a comment will be processed to find references of minutes, hours, or days.
Such items will be appear first as a number and then one of these words: minute, minutes, hour, hours, day, days.
There may be empty lines in the input file.
The words and numbers may be separated by spaces, commas, parenthesis, semicolon. Words and numbers will be separated by at least one non-letter or non-digit symbol. A word is one or more consecutive letters until a non-letter is next.
You can assume that a word will be at most 30 characters long (always letters). Numbers are always digits (0,1,2,...,9). Numbers will have maximum of 10 digits. There may be things that look like a number but are not, such as: 1024K.

## Program specification

The main program should be called `uhday` and the syntax in which it will be tested is as follows:

`uhday "input=FILENAME"`

The parameter `input` specifies the name of the input file.

Example of program calls:

`uhday "input=gray.txt"`

or, `./uhday "input=gray.txt"`

The source code will be compiled as follows:

`g++ -std=c++11 -o uhday -I ./ *.cpp`

## Output

Your program will output to the console (such as via cout, or printf) with the results of counting, independently, the minutes, hours, and days metioned in the file.
Your program must follow the output format exactly to facilitate automated grading (and to avoid failing test cases due to things such as output of an empty line at the end).

Output for the input example.

    Minutes:24
    Hours:1
    Days:0

## Assumptions

* The input file can fit in main memory (not larger than 10kb).
* The words "Minutes", "Hours", "Days" in the output will be exactly like that. They are expected to always be in plural.
* You can assume that it is safe to treat each line independently. There will not be test cases such as line 1 ending in a number, and line 2 starting with: day. 
* Examples of valid numbers due to the character next to them being a separator: 

    `(20 minutes)`

    `They were sleepy;5 hours later they woke up.`

* Examples of numbers that are not valid, that is, your code is not expected to count them.

    `The student reads 40K minutes every day.`

    `It took 12.67 minutes to form an opinion.`

* The obvious separator is space character. You can assume that these are the separators that you must consider: space, comma, semicolon, left parenthesis, and right parenthesis. That is, any of the last 4 separators beforementioned is basically equivalent to a space character. In the example shown above, `12.67` is simply a number that is not valid (numbers are all digits). 

## Requirements

* This assignment is pass/fail. If your program scores more than 60 points, then you will pass. 
* Place your codes in a folder named: `hw0` (Failure to do so will cause your program to have a zero grade due to inability for doing automated grading).
* Your program should not produce any unexpected output when it is doing intermediate calculations because doing so will interfere with automated grading and some test cases will fail.
* You can not assume a maximum number of lines in the input file.
* You can assume a maximum number of 99 words per line.
