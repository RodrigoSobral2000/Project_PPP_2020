#include "../GlobalInterface.h"
#include "../BasicFunctions.c"

int main() {
    static FILE *students_file;
    static FILE *results_file;
    static char students_file_name[DIM/2], results_file_name[DIM/2];
    static StudentNode *students_tree=NULL;
    static CourseNode *results_tree=NULL;
    receiveFileName(students_file_name, ID_STUDENT_FILE);
    receiveFileName(results_file_name, ID_RESULTS_FILE);

    if(access(students_file_name, F_OK)!=-1) {
        students_file= fopen(students_file_name, "rb");
        students_tree= readStudents(students_file, students_tree);
        fclose(students_file);
    } else printf("\n404! PASSED STUDENTS FILE NOT FOUND!\n\n");
    if(access(results_file_name, F_OK)!=-1) {
        results_file= fopen(results_file_name, "rb");
        results_tree= checkResults(results_file, results_tree);
        fclose(results_file);
    } else printf("\n404! COURSES FILE NOT FOUND!\n\n");
    
    return 0;
}
