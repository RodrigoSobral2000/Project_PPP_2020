#include "../GlobalInterface.h"
#include "../BasicFunctions.c"

int main() {
    static FILE *passed_students_file;
    static FILE *results_file;
    static char passed_students_file_name[DIM/2], results_file_name[DIM/2];

    while (1) {
        system("cls");
        strcpy(passed_students_file_name, ENTRY_FILES_DIR_2);
        receiveFileName(passed_students_file_name, ID_STUDENT_FILE, ".bin");
        results_file= fopen(passed_students_file_name, "rb");
        if (results_file==NULL) printf("\n404! FILE OF PASSED STUDENTS NOT FOUND!\n\n");
        sleep(2);
        break;
    }  while (1) {
        strcpy(results_file_name, ENTRY_FILES_DIR_2);
        receiveFileName(results_file_name, ID_RESULTS_FILE, ".bin");
        passed_students_file= fopen(results_file_name, "rb");
        if (passed_students_file==NULL) printf("\n404! FILE OF FINAL RESULTS NOT FOUND!\n\n");
        sleep(2);
        break;
    }

    if (results_file==NULL && passed_students_file==NULL) printf("\n400! SEEMS THERE ARE NO FILES TO READ, SO WE CANNOT WRITE\n\n");
    else translateFiles(results_file, passed_students_file, results_file_name, passed_students_file_name);
    return 0;
}

void translateFiles(FILE* bin_results, FILE* bin_passed_students, char* results_file_name, char* passed_students_file_name) {
    strcpy(results_file_name, "");
    strcpy(passed_students_file_name, "");
    receiveFileName(results_file_name, 3, ".txt");
    receiveFileName(passed_students_file_name, 4, ".txt");
    FILE* final_results_file= fopen(results_file_name, "w");
    FILE* passed_students_file= fopen(passed_students_file_name, "w");

    char course_name[DIM], student_name[DIM*2], student_id[DIM/2];
    int n_students_in_course;
    float final_result;

    fprintf(final_results_file, "\t\t=============FINAL RESULTS=============\n");
    while (!feof(bin_results)) {
        fread(&course_name, sizeof(course_name), 1, bin_results);
        if (feof(bin_results)) break;
        fprintf(final_results_file, "\nCourse: %s\n", course_name);
        fread(&n_students_in_course, sizeof(n_students_in_course), 1, bin_results);
        if (feof(bin_results)) break;
        for (int i = 0; i<n_students_in_course; i++) {
            fread(student_name, sizeof(student_name), 1, bin_results);
            if (feof(bin_results)) break;
            fread(student_id, sizeof(student_id), 1, bin_results);
            if (feof(bin_results)) break;
            fread(&final_result, sizeof(float), 1, bin_results);
            if (feof(bin_results)) break;
            fprintf(final_results_file, "\tName: %s\t\tID: %s\t\tResult: %.2f\n", student_name, student_id, final_result);
        }
    } printf("\n200! FINAL RESULTS FILE WRITTEN WITH SUCESS!\n");

    if (bin_passed_students==NULL) printf("\n417 UPS! IT SEEMS THERE IS NO STUDENT PASSING!\n\n");
    else {
        fprintf(final_results_file, "\t\t=============PASSED STUDENTS=============\n");
        StudentNode* passed_students_tree= NULL;
        passed_students_tree= readStudents(bin_passed_students, passed_students_tree);
        writePassedStudents(passed_students_tree, passed_students_file);
        printf("\n200! PASSED STUDENTS FILE WRITTEN WITH SUCESS!\n");
    }
    fclose(final_results_file);
    fclose(passed_students_file);
}

void writePassedStudents(StudentNode* passed_students_tree, FILE* passed_students_file) {
    if (passed_students_tree!=NULL) {
        writePassedStudents(passed_students_tree, passed_students_file);
        fprintf(passed_students_file, "\tName: %s\t\tID: %s\n", passed_students_tree->student->name, passed_students_tree->student->id_number);
        writePassedStudents(passed_students_tree, passed_students_file);
    }
}
