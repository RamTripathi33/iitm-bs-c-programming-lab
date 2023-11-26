# Template expander

The goal of this project is to write a simple template expander in C.  This will be used to generate a series of "form letters" to be sent to students with their marks and grades.

The input to this program will be a single file:

- `students.csv`: This is a CSV (comma-separated values) file that contains a list of students for whom you need to create the form letters.

## Template expansion

Consider the following template - the template can be written as a single string in your code:

```
To,
{name} (roll no. {rollno})
Student of BS-ES course, IIT Madras

Dear {name},

You scored {marks} marks in the exam, and your grade is {grade}.

Sincerely,
The Dean
```

In this text, any parts that are placed within curly brackets (eg. `{name}`, `{rollno}` etc) are *placeholders* that need to be replaced with the appropriate text.  For example, if we had the following information:

```
name: Nitin C
rollno: abc123
marks: 50
```

then you need to expand the text as 

```
To,
Nitin C (roll no. abc123)
Student of BS-ES course, IIT Madras

Dear Nitin C,

You scored 50 marks in the exam, and your grade is D.

Sincerely,
The Dean
```

Note that in the above text, the `{grade}` was not specified, but needs to be computed with the following formula for marks:

- marks >= 90: S
- 90 > marks >= 80: A
- 80 > marks >= 70: B
- 70 > marks >= 60: C
- 60 > marks >= 50: D
- 50 > marks >= 40: E
- marks < 40: U

## CSV input file

The list of students will be given to you as a CSV (comma-separated values) file.  This contains a list of entries where each line is one student, and the data are separated by the *comma* (`,`) symbol.  For example:

```
Nitin C,abc123,50
Richard Feynman,xyz987,85
D Ritchie,iop567,99
```

You need to generate one output file for each user, and the name of the file should be `{rollno}.txt`.  For example, the files for this CSV will be

```
abc123.txt
xyz987.txt
iop567.txt
```

## Problem statement

A detailed set of steps for solving the problem are given below.  You need to demonstrate the output of the template expander to the TAs.  Note that you can skip straight to the end and demonstrate just the final code.  The intermediate files are given as helping stages, and will be evaluated for partial credit if the overall problem is not solved.

## Requirements and Useful Information

### Code structure

You are required to define a `struct` type called `student_t` that holds the required information.  The struct should contain strings and numeric types as required to store the information.  The strings should be of maximum length 20 characters, and the marks should be a non-negative integer.

Define functions for the following:

- `read_csv`: should read from a given filename and return an array of structs
- `compute_grade(student_t)`: take a student struct as input and return the grade
- `write_file(student_t)`: create a file for the given roll number and write the output

### Useful functions

- [`fgets`](https://en.cppreference.com/w/c/io/fgets)
- [`fscanf`](https://en.cppreference.com/w/c/io/fscanf)
- [`sprintf` and `fprintf`](https://en.cppreference.com/w/c/io/fprintf)

Other useful functions - not strictly needed here but can be used to generalize.

- [`strtok`](https://en.cppreference.com/w/c/string/byte/strtok)
- [`strstr`](https://en.cppreference.com/w/c/string/byte/strstr)

You should be able to read the CSV file using the `strtok` function, but you can also use any other C functions if needed.  The `sprintf` function can be used to generate the filenames into which you need to save the outputs, and also to generate the output if needed (although you can also use `fprintf` directly for that).

The `strstr` function can be useful to find placeholders and replace them with format specifiers (such as `%s`).

## Assignment

You are given the following pieces of code as starters for the various steps involved.  You need to complete the corresponding codes and demonstrate them working to the TAs.

### Step 1: struct declaration and printing

The file `1_template_struct.c` contains some code that has a partial definition of a `struct`.  Structs were covered in Week 8, and are used to organize data into records.  Here we will define a struct, assign initial values to it, and write a function to print it out.

### Step 2: compute grade

Given a struct as input, write a function that will compute the grade from the mark, and update the struct.  

Modify the previous function to also print out the grade as shown in the example.

### Step 3: read lines into struct with fgets and sscanf

The `fgets` function can be used to read a string from a file into a buffer, and then `sscanf` function can be used to read formatted data from a string into other variables.  Here we will use a special format string that allows us to easily read the CSV file.  The function should return the total number of records that have been read so far.

Use the previous functions to compute the grades for each record, and then print out the values.

### Step 4: Fill in template and print

The template is given directly as a string with `%s`, `%d` etc in appropriate places.  You need to create a `printf` function call that will print out the correct output.  Do this for each of the student records.

To write this to a file, you first need to create the name of the file.  Here you can use the `sprintf` function to create the output filename, open it for writing, then use `fprintf` to write to that file.
