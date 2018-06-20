# hw6, LeafLead. Due date extended to: 11/29 11:50 p.m.

You will create a C++ program that will simulate the selection (via tree traversal and sorting) of candidates to a ficticious Top-6 company that hires CS majors.
In real companies/organizations, selection of applicants follows a well-thought procedure that is extremely unlikely to mirror the selection method in this programming assignment.
The fundamental data structure concept to practice is creation of a tree, and its traversal.

## Input

The input is a plain-text file, where each line is terminated with an end-of-line character.
Each line will identify an applicant to join the top-6 ficticious company.

Each line will have a fixed set of data, separated by the `tab` character (that is, `\t`).

The data of each line are as follows:

  1. Person name (not repeated in the input file).
  1. GPA, which is a number between 0 to 4, and it may contain at most 1 digit after the decimal point (if any).
  1. CST score (ficticious standardized Computer Science Test with range of 0 to 999). It will not have decimals.
  1. Leader name. (When the leader name is exactly the same as the person name, then it is the root node).

Lines that start with the symbol `#` should be considered comments and therefore skipped. There may be empty lines in the input file; such lines should be skipped.

Example 1:

    Olaf   1.0   876   Anna
    Anna   4.0   976   Elsa
    Krystoff   1.4   196   Anna
    Madelleine	2.9	397	Elsa
    Frenchy	2.9	397	Lexie
    Lexie	3.1	479	Madelleine
    Lex	3.1	479	Madelleine
    Batman	3.2	543	Elsa
    Coulson	3.4	765	Batman
    Director	3.4	765	Lexie
    Robot	3.1	479	Batman
    Skye	3.4	765	Coulson
    Supergirl	3.8	876	Elsa
    Superman	3.8	876	Anna
    Wonderwoman	3.2	543	Anna
    Sven   0.4   16   Krystoff
    Elsa   2.4   476   Elsa
    instructions	leaves

The last line is a special line that indicates which people to select.
Such line will have two items (separated by the `tab` character).

1. The first item is exactly the string `instructions`
1. When the second item is exactly the string `leaves` then leaf nodes are to be selected.
1. When the second item is exactly the string `lead1` then nodes that are leaders of at least one leaf are to be selected.
1. When the second item is exactly the string `lead2` then nodes that are leaders of at least one leader of a leaf are to be selected.

## Program specification

The main program should be called `leaflead` and the syntax in which it will be tested is as follows:

`./leaflead "input=FILENAME"`

The parameter `input` specifies the name of the input file.

Example of program calls:

`./leaflead "input=example.txt"`

The source code will be compiled as follows:

`g++ -std=c++11 -o leaflead -I ./ *.cpp`

## Output

* The nodes to be output must be first sorted based on the `score` and output from highest score to lower score.
* Your program will output to the console (such as via `cout`) with the results of selected people to be given job offers (if any).
* The name of a person should be output at most once.
* Your program must follow the output format exactly to facilitate automated grading (and to avoid failing test cases due to things such as output of an empty line at the end).

Example of how to output each line:

`cout << personname << endl;`

## Score value used for sorting

A score will be calculated for each person depending on their data as follows:

`score = GPA * 200 + CST`

## Example output for input example

The output would be:

    Supergirl
    Superman
    Director
    Skye
    Wonderwoman
    Lex
    Robot
    Olaf
    Frenchy
    Sven

## Example output for input example when instructions are: lead1

The output would be:

    Anna
    Coulson
    Batman
    Lexie
    Madelleine
    Elsa
    Krystoff

## Example output for input example when instructions are: lead2

The output would be:

    Anna
    Batman
    Madelleine
    Elsa

## Assumptions

* Each input file can fit in main memory (not larger than 10kb).
* You can assume a maximum number of 1299 lines in the input file.
* There will be only one tree (that is, only one root node). 
* The maximum number of children nodes of a parent node is 4.
* Your program will be tested with data where no two nodes will have the exact same score.

## Requirements

* Must utilize your own implementation of a tree traversal method. Failure to do so will result in a grade of 2 points (out of 100).
* Place your codes in a folder in your home directory, named: `hw6` (Failure to do so will cause your program to have a zero grade due to inability for doing automated grading).
* Your program should not produce any unexpected output when it is doing intermediate calculations because doing so will interfere with automated grading and some test cases will fail.

## Random related notes

  * It is suggested that test cases be shared (ideally via pull-request).
