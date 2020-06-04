#include "../GlobalInterface.h"
#include "../BasicFunctions.c"

int main() {
    StudentNode* main_tree=NULL;
    StudentNode* passed_students_tree=NULL;
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
    
    main_tree= readStudents(entry_file_students, main_tree);
    main_tree= readResults(entry_file_results, main_tree);
    
    printStudentsTree(main_tree, PRINT_ALL);

    printf("\n200! TABLES CREATED WITH SUCESS!\n");
    passed_students_tree= passedStudentsGenerator(main_tree, passed_students_tree);
    if (passed_students_tree!=NULL) {
        strcpy(students_file_name, "");
        receiveFileName(students_file_name, ID_STUDENT_FILE);
        FILE* passed_students_tree_file= fopen(students_file_name, "wb");
        writeStudentsInFile(passed_students_tree_file, passed_students_tree);
        fclose(passed_students_tree_file);
    } else printf("417 UPS! IT SEEMS THERE IS NO STUDENT PASSING!\n\n");
    fclose(entry_file_students);
    fclose(entry_file_results);
    return 0;
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
        if (courses->course->classifications[0]+courses->course->classifications[1]>=PASSED_RESULT) return 1;
        else return 0;
        counter+= passedCoursesCounter(courses->right, counter);
    }
    else return 0;
}