v0.1 — Initial Project Setup and Basic Student Data Processing

In this version, the fundamental structure of the application was created, including the implementation of a Person class responsible for storing and processing student academic data.

1. Repository Initialization

A GitHub repository was created with the main branch (main).

The README.md file was added, describing the purpose of the project.

The initial project skeleton was committed.

2. Implementation of the Person Class

The Person class stores information about a single student and calculates their final grade based on homework and exam results.

Class fields:

std::string name;

std::string surname;

std::vector<int> homework;

int exam;

double finalAverage;

double finalMedian;

Implemented methods:

Default constructor

Copy constructor (Rule of Three)

Copy assignment operator (Rule of Three)

Destructor (Rule of Three)

Overloaded operator>> — input of name and surname

Overloaded operator<< — formatted output of results

calculateGrades() method
Calculates:

final grade using homework average

final grade using homework median

Setter methods:
setName(), setHomework(), setExam()

3. Final Grade Calculation Logic

Two grading methods were implemented:

Average-based final grade:
Final = 0.4 * average(homework) + 0.6 * exam

Median-based final grade:
Final = 0.4 * median(homework) + 0.6 * exam

4. User Interaction

The program allows the user to:

enter a student's first name and surname

input an arbitrary number of homework grades

enter the exam grade

automatically compute the final grade based on the chosen method (average or median)

5. Output Formatting

The results are displayed in a clean, table-like format:

Name        Surname      Final (Avg.)
-------------------------------------
John        Doe              8.24
Anna        Smith            6.91
