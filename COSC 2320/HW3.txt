# hw3, uhstack. Due date: Saturday 10/22 6 p.m. 

You will create a C++ program that will evaluate math operations (using stacks).

In this homework, your program will calculate operations such as those involved in buying cell phones, cell phone accessories, and service plans. The math operations are implicit place via **buying**, **adding**, applying a **discount**, and calculating a **total**. 

The operations are listed in an input file where each line follows a defined format that includes the customer, and the action.

## Input

The input is one plain-text file, where each line is terminated with an end-of-line character.
Each line will have a fixed set of data, separated by the `tab` character (that is, `\t`).
Lines that start with the symbol `#` should be considered comments and therefore skipped. There may be empty lines in the input file; such lines should be skipped.

Example 1:

    Olaf   buy  100
    Olaf   times 2
    Olaf   total

Each line that is not a comment (or empty line) will always have either two, or three items. The first is the customer. The second, and third are operations or pricing of merchandise.

Each line indicates what happens when a person is buying a cell phone and the math behind it to calculate the total. In example 1, Olaf buys two items, each costs 100. When the line `total` is read, your program needs to calculate the total by utilizing stacks. Normally, your program will create a posfix notation of the mathematical expression and then it will evaluate it.

In example 1, the posfix expression would look like: `100 2 *` but it is used internally in your program. The only output is the total of the result(s) of evaluation the mathematical expression(s) for the customer(s) using stacks. 

## Program specification

The main program should be called `uhstack` and the syntax in which it will be tested is as follows:

`./uhstack "input=FILENAME"`

The parameter `input` specifies the name of the input file.

Example of program calls:

`./uhstack "input=example.txt"`

The source code will be compiled as follows:

`g++ -std=c++11 -o uhstack -I ./ *.cpp`

What to expect in the input file:

  1. The first field can be either of the following:
    * the name of a customer. In example 1, the name is `Olaf`
    * `price` indicates the cost of a product. The second field is the name of the product. Product names are arbitrary. The third field is the cost of the product: it is always a number. 

  1. The second field can be either of the following
    * `buy` indicates that a product name, or a numerical value is next. This is normally the begining of a math expression. 
    Therefore, when the second field is `buy`, then there will always be a third field: either a number, or the name of a product.
    * `times` indicates multiplication, and it will always have a third field that is a number.
    * `add` indicates addtion, and it will always have a third field: either a number, or the name of a product.
    * `total` indicates that we have are ready to calculate the total for the customer. Your program will evaluate the math expression and it will output the result of the calculation.
    * `open` indicates that a customer has a shopping bag, which is analogous to a left parenthesis `(` in mathematics. The third field will always be `bag`
    * `close` indicates that a customer has completed placing items inside of a shopping bag, which is analogous to a right parenthesis `)` in mathematics. The third field will always be `bag`
    * `discount%` indicates the percentage of a discount to be applied to the previous math expression.

   The order matters because otherwise the math expression would be calculated in an unpredictable way.
   
   The `price` indicates the cost of a product. Product prices sometimes are updated. A customer must be charged by the price of a product at the time that the `total` is calculated.

## Output

Your program will output to the console (such as via `cout`) with the results of math evaluations, if any.
Your program must follow the output format exactly to facilitate automated grading (and to avoid failing test cases due to things such as output of an empty line at the end).

Output for the input example 1.

    200

Example of how to output a line:

`cout << total << endl;`

The output of your program should not have empty lines or comments.

## Assumptions

* Each input file can fit in main memory (not larger than 10kb).
* Numbers are always integers (no decimals, no decimal point).
* The precedence of `times` is the same as that of `discount%`
* If you choose to do your stack data structures via an underlying array, you can assume that an array of size 200 will be sufficient

## Requirements

* Must utilize your own implementation of stack data structures to do any mathematical evaluation of operations. Failure to do so will result in a grade of 2 points (out of 100).
* Place your codes in a folder in your home directory, named: `hw3` (Failure to do so will cause your program to have a zero grade due to inability for doing automated grading).
* Your program should not produce any unexpected output when it is doing intermediate calculations because doing so will interfere with automated grading and some test cases will fail.
* You can not assume a maximum number of lines in the input file.
* Any numerical output is integer (it should not include decimals, it should not include decimal point).

## More examples

Example variable substitutions:
Input:

    price  case  20
    Olaf   buy  case
    price  adapter  8
    Olaf   add  adapter
    Olaf   total

Output:

    28
    
Example c:

Summary of test cases:

    * `a` .. `c`, `t` most basic calculation
    * `d`, `e` simple add, multiply
    * `f`, `g`, `h` division with parenthesis
    * `i` .. `l` combined operations
    * `m` .. `p`  simple add, multiply, with variable substitutions
    * `q` .. `r`  variable substitutions, more than 1 customer

