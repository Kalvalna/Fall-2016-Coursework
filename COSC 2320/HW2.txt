# hw2, Recursive Notifications

## Early deadline: Friday 10/7 4pm, +6 extra points, folder name: hw2early

## Regular deadline: Saturday 10/8 6pm, folder name: hw2

## Overdue deadline: Wednesday 10/12 at 11am, maximum grade: 40/100, folder name hw2due

 * Details about Overdue Deadline: 
   * A few students requested an extension. 
   * In order to move on to the next assignment, the Overdue Deadline is an option that would get you up to 40% of the points for this assignment (because it is late, and having the option of getting full points is not totally fair to students that did things on time). 
   * Assignments overdue will be evaluated without the test cases requiring functionality of reading more than 1 file (your program can skip functionality listed in hw1 under: "Rules to combine input files"), and without the test cases requiring implementing special cases (bullet points 3, and 4 in hw1's program specification).  
   * That is, you get maximum of 40% (instead of 100) but your program does not have to implement reading more than 1 file, and it does not have to implement the special cases.
   * The objective is to be able to aim for 40% grade instead of the frustration of a grade of zero, but without the burden of implementing everything in the assignment because more programming assignments are coming. 
   * We can review pros and cons of this Overdue Deadline extension on next class (if needed).
   * Finally, please be aware of the following: There were more than twice the students that are in the early deadline option than the number of students that were in the early deadline option in the previous assignment.

You will create a C++ program that will recursively combine notifications (using doubly linked lists).

The requirements are the same as those of hw1 unless explicitly indicated here.

## Program specification

The main program should be called `coogsive` and the syntax in which it will be tested is as follows:

`./coogsive "input=FILENAME"`

Example of program calls:

`./coogsive "input=uh-gray.1.txt"`

The source code will be compiled as follows:

`g++ -std=c++11 -o coogsive -I ./ *.cpp`


Example of combining notifications from all input files:

    File 1 has notifications 
    A s1 b1
    B s2 b2
    C s3 b3
    D s4 b4

    File 2 has notifications 
    G s5 b5
    H s6 b6
    K s7 b7

    File 3 has notifications 
    M s8 b8
    N s9 b9

    File 4 has notifications 
    Q s10 b10
    R s11 b11
    T s12 b12
    S s13 b13

    The global list would be: 
    A s1 b1
    G s5 b5
    M s8 b8
    Q s10 b10
    B s2 b2
    H s6 b6
    N s9 b9
    R s11 b11
    C s3 b3
    K s7 b7
    T s12 b12
    D s4 b4
    S s13 b13
    
## Requirements

* Must utilize your own linked-lists to do the combining of operations (either within a file, or when combining various files into a single list of notifications). Failure to do so will result in a grade of 2 points (out of 100). That is, using any existing library for linked-lists is not allowed.
* Everything in your code needs to be done via recursion instead of via loops (such as `for` or `while`). Each time that your program uses a `for` or `while` loop (or similar) will have a penalty of 27 points (out of 100).
* Place your codes in a folder in your home directory, named: `hw2` (Failure to do so will cause your program to have a zero grade due to inability for doing automated grading). In case that you are going for the early deadline, the folder name must be: `hw2early`

## Miscellaneous

* An example for reading the file recursively is included here as well. Yes, the file reading need to be recursive.
