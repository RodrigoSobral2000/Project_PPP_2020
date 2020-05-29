/*----------------LIBRARIES-------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*------------------CONSTANTS------------------*/
#define ADD_STUDENT_OPTION 1
#define MODIFY_STUDENT_OPTION 2
#define DELETE_STUDENT_OPTION 3
#define ADD_RESULT_OPTION 4
#define MODIFY_RESULT_OPTION 5
#define DELETE_RESULT_OPTION 6
#define EXIT_OPTION 0

#define ID_STUDENT_FILE 1
#define ID_RESULTS_FILE 2

#define DIM 50

/*------------------------BASIC FUNCTIONS-----------------------*/

//------------CHECKERS------------
//  Check if it is a correct string
int stringChecker(char*, char*);
//  Check if it is a correct number
int intChecker(char*, char*);