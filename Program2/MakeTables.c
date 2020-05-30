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
    
    printTree(tree_root);
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

StudentNode* readStudents(FILE* file, StudentNode* tree) {
    StudentInfo* new_student= NULL;
    while (!feof(file)) {
        new_student= (StudentInfo*) malloc(sizeof(StudentInfo));
        fread(new_student->name, sizeof(new_student->name), 1, file);
        if (feof(file)) break;
        fread(new_student->id_number, sizeof(new_student->id_number), 1, file);
        new_student->signed_in_courses=NULL;
        tree= addStudent(tree, new_student);
    }
    free(new_student);
    return tree;
}

StudentNode* readResults(FILE* file, StudentNode* tree) {
    CourseInfo* new_course= (CourseInfo*) malloc(sizeof(CourseInfo));
    StudentInfo* aux_student=(StudentInfo*) malloc(sizeof(StudentInfo));
    char student_id[DIM/2];
    int prove_id;
    while (!feof(file)) {
        fread(student_id, sizeof(student_id), 1, file);
        fread(new_course->name, sizeof(new_course->name), 1, file);
        fread(&prove_id, sizeof(int), 1, file);
        fread(&new_course->classifications[prove_id], sizeof(float), 1, file);
        aux_student= searchStudentTree(tree, student_id);
        aux_student->signed_in_courses= addCourse(aux_student->signed_in_courses, new_course);
    }
    return tree;
}

StudentNode* addStudent(StudentNode *tree, StudentInfo* new_student) {
    int cond;
    if (tree == NULL) {
        tree = (StudentNode*) malloc(sizeof(StudentNode));
        tree->student= new_student;
        tree->left= tree->right= NULL;
    } 
    else if ((cond = strcasecmp(new_student->id_number, tree->student->id_number)) == 0) return tree;
    else if (cond<0) tree->left= addStudent(tree->left, new_student);
    else tree->right = addStudent(tree->right, new_student);
    return tree;
}

CourseNode* addCourse(CourseNode *tree, CourseInfo* new_course) {
    int cond;

    if (tree == NULL) {
        tree = (CourseNode*) malloc(sizeof(CourseNode));
        tree->course= new_course;
        tree->left= tree->right= NULL;
    } 
    else if ((cond = strcasecmp(new_course->name, tree->course->name)) == 0) return tree;
    else if (cond<0) tree->left= addCourse(tree->left, new_course);
    else tree->right = addCourse(tree->right, new_course);
    return tree;
}

StudentInfo* searchStudentTree(StudentNode* tree, char* id) {
    if (tree==NULL) return NULL;
    else {
        StudentInfo* student_searched= (StudentInfo*)malloc(sizeof(StudentInfo));
        if (strcasecmp(tree->student->id_number, id)!=0) {
            student_searched= searchStudentTree(tree->left, id);
            printf("Name: %s\nNumber: %s", tree->student->name, tree->student->id_number);
            student_searched= searchStudentTree(tree->right, id);
            return student_searched;
        } else return tree->student;
    }
}

void printTree(StudentNode* tree) {
    if (tree != NULL) {
        printTree(tree->left);
        printf("Name: %s\nNumber: %s\n", tree->student->name, tree->student->id_number);
        printTree(tree->right);
    }
}
