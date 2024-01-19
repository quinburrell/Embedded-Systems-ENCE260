#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 80      // The longest line this program will accept
#define MAX_NUM_STUDENTS 500    // The maximum number of students this program can handle
#define MAX_NAME_SIZE 50        // The maximum allowable name length

// The declaration of the student record (or struct). Note that
// the struct contains the name as an array of characters, rather than
// containing just a pointer to the name as before.

typedef struct student_s Student;

struct student_s {
    char name[MAX_NAME_SIZE];
    int age;
    Student* next;              // Pointer to next student in a list
};

// Create a pool of student records to be allocated on demand

Student studentPool[MAX_NUM_STUDENTS];  // The student pool
int firstFree = 0;

// Return a pointer to a new student record from the pool, after
// filling in the provided name and age fields. Returns NULL if
// the student pool is exhausted.
Student* newStudent(const char* name, int age)
{
    Student* student = NULL;
    if (firstFree < MAX_NUM_STUDENTS) {
        student = &studentPool[firstFree];
        firstFree += 1;
        strncpy(student->name, name, MAX_NAME_SIZE);
        student->name[MAX_NAME_SIZE - 1] = '\0';  // Make sure it's terminated
        student->age = age;
        student->next = NULL;
    }
    return student;
}

// Read a single student from a csv input file with student name in first column,
// and student age in second.
// Returns: A pointer to a Student record, or NULL if EOF or an invalid
// student record is read. Blank lines, or lines in which the name is
// longer than the provided name buffer, or there is no comma in the line
// are considered invalid.
Student* readOneStudent(FILE* file)
{
    char buffer[MAX_LINE_LENGTH] = {0};  // Buffer into which we read a line from stdin
    Student* student = NULL;       // Pointer to a student record from the pool

    // Read a line, extract name and age

    char* inputLine = fgets(buffer, MAX_LINE_LENGTH, file);
    if (inputLine != NULL) {        // Proceed only if we read something
        char* commaPos = strchr(buffer, ',');
        if (commaPos != NULL) {
            int age = atoi(buffer);
            *strchr(buffer, '\n') = '\0';
            student = newStudent(commaPos + 2, age);
        }
    }
    return student;
}

// Reads a list of students from a given file. Input stops when
// a blank line is read, or an EOF occurs, or an illegal input
// line is encountered.
// Returns a pointer to the first student in the list or NULL if no
// valid student records could be read.
Student* readStudents(FILE *file)
{
    Student* first = NULL;     // Pointer to the first student in the list
    Student* last = NULL;      // Pointer to the last student in the list
    Student* student = readOneStudent(file);
    while (student != NULL) {
        if (first == NULL) {
            first = last = student;   // Empty list case
        } else {
            last = first;
            first = student;
            first->next = last;
        }
        student = readOneStudent(file);
    }
    return first;
}

// printOneStudent: prints a single student, passed by value
void printOneStudent(Student student)
{
    printf("%s (%d)\n", student.name, student.age);
}


// printStudents: print all students in a list of students, passed
// by reference
void printStudents(const Student* student)
{
    while (student != NULL) {
        printOneStudent(*student);
        student = student->next;
    }
}


// Main program. Read a linked list of students from a csv file, then display
// the contents of that list.
int main(void)
{
    FILE* inputFile = stdin;
    if (inputFile == NULL) {
        fprintf(stderr, "File not found\n");
    } else {
        Student* studentList = readStudents(inputFile);
        printStudents(studentList);

        // The program could now do various things that make use of
        // the linked list, like deleting students and adding new ones,
        // but the program is already quite long enough!
    }
}
