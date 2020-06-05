//  ========================================
//                  LIBRARIES
//  ========================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//  ========================================
//                  CONSTATNS
//  ========================================

//  USEFUL
#define ID_STUDENT_FILE 1
#define ID_RESULTS_FILE 2
#define TOT_PROVES 2
#define DIM 50

#define JUST_PRINT_STUDENTS 0
#define JUST_PRINT_RESULTS 1
#define PRINT_ALL 2

//  MAIN MENU OPTIONS PROGRAM 1
#define ADD_STUDENT_OPTION 1
#define MODIFY_STUDENT_OPTION 2
#define DELETE_STUDENT_OPTION 3
#define ADD_RESULT_OPTION 4
#define MODIFY_RESULT_OPTION 5
#define DELETE_RESULT_OPTION 6
#define PRINT_CUR_STUDENTS 7
#define PRINT_CUR_RESULTS 8
#define EXIT_OPTION 0

//  MODIFY MENU OPTIONS PROGRAM 1
#define MODIFY_NAME 1
#define MODIFY_ID 2
#define MODIFY_PROVE1 3

//  FILE'S DIRECTORY PROGRAM 2
#define ENTRY_FILES_DIR "../Program1/"
#define PASSED_RESULT 9.5
#define TOT_COURSES_PASSED 8

//  ==============================================
//                  DATA STRUCTURES
//  ==============================================

typedef struct aux_course_names StringArray;
struct aux_course_names {
    char string[DIM];
    /*------------*/
    StringArray *next;
};

//  NODE WITH COURSES' INFORMATION
typedef struct {
    char name[DIM];
    float classifications[TOT_PROVES];
    //  ONLY TO USE IN PRINTS OF PROGRAM 1
    char aux_id[DIM/2];
} CourseInfo;

//  TREE WITH ALL COURSES OF EACH STUDENT
typedef struct aux_course CourseNode;
struct aux_course {
    CourseInfo *course;
    CourseNode *left;
    CourseNode *right;
};

//  NODE WITH EACH STUDENT'S INFORMATION (INCLUDING THEIR COURSES)
typedef struct {
    char name[DIM*2];
    char id_number[DIM/2];
    CourseNode* signed_in_courses;
} StudentInfo;

//  TREE WITH ALL THE DATA
typedef struct aux_student StudentNode;
struct aux_student {
    StudentInfo *student;
    StudentNode *left;
    StudentNode *right;
};


//  ========================================
//                  FUNCTIONS
//  ========================================

/*============================BASIC FUNCTIONS============================*/

//  RECEIVE A STRING AND A MESSAGE (IN CASE OF ERROR) TO PRINT
//  RETURNS 1 IF IT IS A CORRECT STRING, -1 IF IT ISN'T
int stringChecker(char*, char*);

//  RECEIVE A STRING, A CHARACTER AND A MESSAGE (IN CASE OF ERROR) TO PRINT
//  THE CHARACTER CAN ONLY BE 'i', 's' DEPENDING THE TYPE OF DATA WE WANT
//      IF 'i' RETURN atoi()
//      ELSE RETURN 1 OR -1 IF THE STRING NUMBER IS CORRECT OR WRONG
int intChecker(char*, char, char*);

//  RECEIVE A STRING, A CHARACTER AND A MESSAGE (IN CASE OF ERROR) TO PRINT
//  THE CHARACTER CAN ONLY BE 'f', 's' DEPENDING THE TYPE OF DATA WE WANT
//      IF 'f' RETURN atof()
//      ELSE RETURN 1 OR -1 IF THE STRING NUMBER IS CORRECT OR WRONG
float floatChecker(char* str_number, char number_type, char* error);


//  RECEIVES THE STUDENT'S FILE AND AN EMPTY TREE
//  RETURNS THE FILLED TREE
StudentNode* readStudents(FILE*, StudentNode*);

//  RECURSIVELY RECEIVES A TREE AND A NODE
//  RECURSIVELY RETURNS THE ORIGINAL TREE WITH THE NODE ADDED
StudentNode* addStudent(StudentNode*, StudentInfo*);

//  RECURSIVELY RECEIVES A TREE AND A NODE
//  RECURSIVELY RETURNS THE ORIGINAL TREE WITH THE NODE ADDED
CourseNode* addCourse(CourseNode*, CourseInfo*);

//  RECEIVES A TREE AND AN ID NUMBER
//  RETURNS THE CORRESPONDING ID NODE
StudentInfo* searchStudentTreeByID(StudentNode*, char*);
CourseInfo* searchResultTreeByName(CourseNode*, char*);

//  RECURSIVELY RECEIVES A TREE AND PRINTS IT'S NODES
void printStudentsTree(StudentNode*, int);

//  RECURSIVELY RECEIVES A TREE AND PRINTS IT'S NDOES
void printCoursesTree(CourseNode*);



/*============================PROGRAM 1 FUNCTIONS============================*/

//  JUST CLEAR THE CONSOLE AND PRINTS THE ENTIRE MAIN MENU
void mainMenu();

//  WRITE AN ELEMENT (STUDENT OR RESULT) IN THE CORRECT FILE 
//  RETURN A TREE WITH THE NEW ELEMENT/NODE (STUDENT OR RESULT)
StudentNode* newStudent(StudentNode*);
StudentNode* newResult(StudentNode*);

StudentNode* modifyStudent(StudentNode*);
StudentNode* modifyResult(StudentNode*);


void saveData(FILE*, FILE*, StudentNode*, char*, char*);
void writeStudentsInFile(FILE*, FILE*, StudentNode*, int);
void writeResultsInFile(FILE*, CourseNode*);


/*============================PROGRAM 2 FUNCTIONS============================*/

//  RECEIVES THE FILE'S DIRECTORY AND AN INT TO IDENITFY WICH FILE IT IS
void receiveFileName(char*, int);

//  RECEIVES THE RESULTS' FILE AND AN EMPTY TREE
//  FILLS STUDENT'S NODES WITH THEIR RESPECTIVE COURSES AND RESULTS
//  RETURNS THE FILLED TREE
StudentNode* readResults(FILE*, StudentNode*);

StudentNode* passedStudentsGenerator(StudentNode* tree, StudentNode* passed_students_tree);

int passedCoursesCounter(CourseNode* courses, int counter);