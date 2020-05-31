#include "../database.h"
#include "../BasicFunctions.c"

int main() {
    StudentNode* tree_root=NULL;
    FILE *entry_file_students;
    FILE *entry_file_results;
    char file_name_students[DIM/2], file_name_results[DIM/2];

    while (1) {
        system("cls");
        strcpy(file_name_students, ENTRY_FILES_DIR);
        receiveFileName(file_name_students, ID_STUDENT_FILE);
        entry_file_students= fopen(file_name_students, "rb");
        if (entry_file_students!=NULL) break;
        else printf("\nERROR 404! FILE OF STUDENTS NOT FOUND!\n\n");
        sleep(2);
    } 
    while (1) {
        strcpy(file_name_results, ENTRY_FILES_DIR);
        receiveFileName(file_name_results, ID_RESULTS_FILE);
        entry_file_results= fopen(file_name_results, "rb");
        if (entry_file_results!=NULL) break;
        else printf("\nERROR 404! FILE OF RESULTS NOT FOUND!\n\n");
        sleep(2);
    }
    
    tree_root= readStudents(entry_file_students, tree_root);
    tree_root= readResults(entry_file_results, tree_root);
    
    printStudentsTree(tree_root);

    passedStudentsGenerator(tree_root);
    printf("\n200! TABLES CREATED WITH SUCESS!");
    fclose(entry_file_students);
    fclose(entry_file_results);
    return 0;
}

void receiveFileName(char* file_name, int file_id) {
    char aux_file_name[DIM/2];
    if (file_id==1) printf("What is the name of entry student's data file? (no extension needed)\nName: ");
    else if (file_id==2) printf("What is the name of entry result's data file? (no extension needed)\nName: ");
    scanf(" %[^\n]", aux_file_name);
    strcat(file_name, aux_file_name);
    strcat(file_name, ".bin");
}

StudentNode* readResults(FILE* file, StudentNode* tree) {
    CourseInfo* new_course= NULL;
    StudentInfo* aux_student= NULL;
    int prove_id;
    while (!feof(file)) {
        new_course= (CourseInfo*) malloc(sizeof(CourseInfo));
        aux_student=(StudentInfo*) malloc(sizeof(StudentInfo));
        fread(new_course->aux_id, sizeof(new_course->aux_id), 1, file);
        if (feof(file)) break;
        fread(new_course->name, sizeof(new_course->name), 1, file);
        if (feof(file)) break;
        fread(&prove_id, sizeof(int), 1, file);
        if (feof(file)) break;
        fread(&new_course->classifications[prove_id-1], sizeof(float), 1, file);
        if (prove_id==1) new_course->classifications[1]=0;
        else new_course->classifications[0]=0;

        aux_student= searchStudentTree(tree, new_course->aux_id);
        if (aux_student!=NULL) aux_student->signed_in_courses= addCourse(aux_student->signed_in_courses, new_course);
    }
    free(new_course);
    free(aux_student);
    return tree;
}


void passedStudentsGenerator(StudentNode* tree) {
    
}