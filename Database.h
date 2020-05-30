//  ================================
//             LIBRARIES
//  ================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//  ================================
//              CONSTATNS
//  ================================

#define ID_STUDENT_FILE 1
#define ID_RESULTS_FILE 2
#define TOT_PROVES 2
#define DIM 50

//  PROGRAM 1
#define ADD_STUDENT_OPTION 1
#define MODIFY_STUDENT_OPTION 2
#define DELETE_STUDENT_OPTION 3
#define ADD_RESULT_OPTION 4
#define MODIFY_RESULT_OPTION 5
#define DELETE_RESULT_OPTION 6
#define EXIT_OPTION 0

//  PROGRAM 2
#define ENTRY_FILES_DIR "../Program1/"

//  ======================================
//              DATA STRUCTURES
//  ======================================
typedef struct {
    char name[DIM];
    float classifications[TOT_PROVES];
} CourseInfo;

typedef struct aux_course {
    CourseInfo *course;
    struct aux_course *left;
    struct aux_course *right;
} CourseNode;

typedef struct {
    char name[DIM*2];
    char id_number[DIM/2];
    CourseNode* signed_in_courses;
} StudentInfo;

typedef struct aux_student {
    StudentInfo *student;
    struct aux_student *left;
    struct aux_student *right;
} StudentNode;


//  ================================
//             FUNCTIONS
//  ================================

/*------------------------BASIC FUNCTIONS-----------------------*/
//  Check if it is a correct string
int stringChecker(char*, char*);
//  Check if it is a correct number
int numberChecker(char*, char, char*);

/*------------------------PROGRAM 1 FUNCTIONS-----------------------*/
//  JUST CLEAR THE CONSOLE AND PRINTS THE ENTIRE MENU
void mainMenu();
//  WRITE A NEW STUDENT OR RESULT IN THE RIGHT FILE
void addElement(FILE*, int);

/*------------------------PROGRAM 2 FUNCTIONS-----------------------*/
void receiveFileName(char*, int);
StudentNode* readStudents(FILE*, StudentNode*);
StudentNode* readResults(FILE*, StudentNode*);
StudentNode* addStudent(StudentNode*, StudentInfo*);
CourseNode* addCourse(CourseNode*, CourseInfo*);
StudentInfo* searchStudentTree(StudentNode*, char*);
void printTree(StudentNode*);