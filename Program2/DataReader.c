#include "../GlobalInterface.h"
#include "../BasicFunctions.c"

int isIn(StringArray* array, char* name);
StringArray* addName(StringArray* array, char* name);
StringArray* getStudentCourses(CourseNode* tree, StringArray* names_array);
StringArray* getAllCourses(StudentNode* tree, StringArray* names_array);
void printNames(StringArray* names);

int main() {
    StudentNode* all_students=NULL;
    StudentNode* passed_students_tree=NULL;
    StringArray* all_course_names=NULL;
    FILE *entry_file_students;
    FILE *entry_file_results;
    char students_file_name[DIM/2], results_file_name[DIM/2];

    while (1) {
        system("cls");
        strcpy(students_file_name, ENTRY_FILES_DIR);
        receiveFileName(students_file_name, ID_STUDENT_FILE);
        entry_file_students= fopen(students_file_name, "rb");
        if (entry_file_students!=NULL) break;
        else printf("\n404! FILE OF STUDENTS NOT FOUND!\n\n");
        sleep(2);
    } 
    while (1) {
        strcpy(results_file_name, ENTRY_FILES_DIR);
        receiveFileName(results_file_name, ID_RESULTS_FILE);
        entry_file_results= fopen(results_file_name, "rb");
        if (entry_file_results!=NULL) break;
        else printf("\n404! FILE OF RESULTS NOT FOUND!\n\n");
        sleep(2);
    }
    
    all_students= readStudents(entry_file_students, all_students);
    all_students= readResults(entry_file_results, all_students);
    
    all_course_names= getAllCourses(all_students, all_course_names);
    if (all_course_names!=NULL) makeTables(all_students, all_course_names);
    else printf("\n400! THERE ARE NO STUDENTS TO MAKE TABLES, SO, TABLES' FILE WASN'T DONE\n\n");
    //printNames(all_course_names);


    passed_students_tree= passedStudentsGenerator(all_students, passed_students_tree);
    if (passed_students_tree!=NULL) {
        strcpy(students_file_name, "");
        receiveFileName(students_file_name, 4);
        FILE* passed_students_tree_file= fopen(students_file_name, "wb");

        writeStudentsInFile(passed_students_tree_file, NULL, passed_students_tree, PRINT_CUR_STUDENTS);
        
        fclose(passed_students_tree_file);
        printf("\n200! TABLES CREATED WITH SUCESS!\n");
    } else printf("\n417 UPS! IT SEEMS THERE IS NO STUDENT PASSING!\n\n");
    fclose(entry_file_students);
    fclose(entry_file_results);
    return 0;
}

int isIn(StringArray* array, char* name) {
    if (array==NULL) return 0;
    else if (strcasecmp(array->string, name)==0) return 1;
    else return isIn(array->next, name);
}

StringArray* addName(StringArray* array, char* name) {
    if (array == NULL) {
        array = (StringArray*) malloc(sizeof(StringArray));
        strcpy(array->string, name);
        array->next= NULL;
    } else if (strcasecmp(array->string, name)==0) return array;
    else array->next = addName(array->next, name);
    return array;
}
StringArray* getStudentCourses(CourseNode* tree, StringArray* names_array) {
    if (tree!=NULL)  {
        getStudentCourses(tree->left, names_array);
        names_array=addName(names_array, tree->course->name);
        getStudentCourses(tree->right, names_array);
    }
    return names_array;
}    
StringArray* getAllCourses(StudentNode* tree, StringArray* names_array) {
    if (tree!=NULL) {
        getAllCourses(tree->left, names_array);
        names_array= getStudentCourses(tree->student->signed_in_courses, names_array);
        getAllCourses(tree->right, names_array);
    }
    return names_array;
}
void printNames(StringArray* names) {
    if (names!=NULL) {
        printf("Course: %s\n", names->string);
        printNames(names->next);
    }
}


void searchCourseInStudent(FILE* tables_file, CourseNode* courses_tree, char* name) {
    if (courses_tree!=NULL)  {
        searchCourseInStudent(tables_file, courses_tree->left, name);
        if (strcasecmp(courses_tree->course->name, name)==0) {
            /* neste momento fiquei a percorrer a lista ligada dos nomes das cadeiras e a encontrar
             * esses nomes na arvore dos alunos
             * falta: escrever os resultados no ficheiro e desenvolver program 3
             */
        }
        searchCourseInStudent(tables_file, courses_tree->right, name);
    }
}    

void searchStudentWithCourse(FILE* tables_file, StudentNode* students_tree, char* name) {
    if (students_tree!=NULL) {
        searchStudentWithCourse(tables_file, students_tree->left, name);
        searchCourseInStudent(tables_file, students_tree->student->signed_in_courses, name);
        searchStudentWithCourse(tables_file, students_tree->right, name);
    }
}

void makeTables(StudentNode* students_tree, StringArray* names) {
    FILE *tables_file;
    char tables_file_name[DIM/2];
    while (1) {
        system("cls");
        receiveFileName(tables_file_name, ID_STUDENT_FILE);
        tables_file= fopen(tables_file_name, "wb");
        sleep(2);
    } 
    
    while (names) {
        searchCourseInStudent(tables_file, students_tree, names->string);
        names=names->next;
    }
    fclose(tables_file);
}


StudentNode* passedStudentsGenerator(StudentNode* tree, StudentNode* passed_students_tree) {
    if (tree != NULL) {
        passed_students_tree= passedStudentsGenerator(tree->left, passed_students_tree);
        if (passedCoursesCounter(tree->student->signed_in_courses, 0)>=TOT_COURSES_PASSED) {
            passed_students_tree= addStudent(passed_students_tree, tree->student);
        }
        passed_students_tree= passedStudentsGenerator(tree->right, passed_students_tree);
    }
    return passed_students_tree;
}

int passedCoursesCounter(CourseNode* courses, int counter) {
    if (courses != NULL) {
        counter+= passedCoursesCounter(courses->left, counter);
        if ((courses->course->classifications[0]+courses->course->classifications[1])/2>=PASSED_RESULT) return 1;
        else return 0;
        counter+= passedCoursesCounter(courses->right, counter);
    }
    else return 0;
}