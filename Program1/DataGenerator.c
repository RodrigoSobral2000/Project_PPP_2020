#include "../Database.h"
#include "../BasicFunctions.c"

int main(int argc, char *argv[]) {
    if (argc!=3) fprintf(stderr, "wrong parameters\npass the two files' names you want to create (no extension needed)");
    else {
        static FILE *students_file;
        static FILE *results_file;
        static char students_file_name[DIM/2], results_file_name[DIM/2];
        static StudentNode *students_tree=NULL;
        static CourseNode *results_tree=NULL;
        strcpy(students_file_name, strcat(argv[ID_STUDENT_FILE], ".bin"));
        strcpy(results_file_name, strcat(argv[ID_RESULTS_FILE], ".bin"));
                
        if(access(students_file_name, F_OK)!=-1) {
            students_file= fopen(students_file_name, "rb");
            students_tree= readStudents(students_file, students_tree);
            fclose(students_file);
        } if(access(results_file_name, F_OK)!=-1) {
            results_file= fopen(results_file_name, "rb");
            results_tree= checkResults(results_file, results_tree);
            fclose(results_file);
        }

        static int option;
        static char str_option[5];
        //static char enter_pressed;

        //  RECEIVES OPTIONS
        while (1) {
            do {
                mainMenu();
                printf("\n\tOption=> ");
                scanf(" %[^\n]", str_option);
                option= intChecker(str_option, 'i', "INTRODUCE A VALID OPTION");
            } while (option<EXIT_OPTION || option>PRINT_CUR_RESULTS);

            if (option==ADD_STUDENT_OPTION || option==ADD_RESULT_OPTION) {
                if (option==ADD_STUDENT_OPTION) students_tree= newStudent(students_tree);
                else results_tree= newResult(results_tree);
                sleep(3);
            } else if (option==MODIFY_STUDENT_OPTION || option==MODIFY_RESULT_OPTION) {
                if (option==MODIFY_STUDENT_OPTION) students_tree= modifyStudent(students_tree);
                else results_tree= modifyResult(results_tree);
                sleep(3);
            } else if (option==DELETE_STUDENT_OPTION || option==DELETE_RESULT_OPTION) {
                //if (option==DELETE_STUDENT_OPTION) deleteElement(ID_STUDENT_FILE);
                //else deleteElement(ID_RESULTS_FILE);
            } else if (option==PRINT_CUR_STUDENTS) {
                if (students_tree==NULL) {
                    printf("\nERROR 400! THERES IS NO STUDENTS' DATA SAVED YET!\nBACKING TO MAIN MENU...\n\n");
                    sleep(3);
                } else {
                    system("cls");
                    printf("\n=============SIGNED IN STUDENTS=============\n\n");
                    printStudentsTree(students_tree);
                    sleep(7);
                }
            } else if (option==PRINT_CUR_RESULTS) {
                if (results_tree==NULL) {
                    printf("\nERROR 400! THERES IS NO RESULTS' DATA SAVED YET!\nBACKING TO MAIN MENU...\n\n");
                    sleep(3);
                } else {
                    system("cls");
                    printf("\n=============SIGNED IN RESULTS=============\n\n");
                    printCoursesTree(results_tree);
                    sleep(7);
                }
            } else if (option==EXIT_OPTION) {
                saveData(students_file, results_file, students_tree, results_tree, students_file_name, results_file_name);
                printf("\n200! PROGRAM CLOSED AND DATA SAVED WITH SUCESS!!\n\n");
                break;
            }
        }
        fclose(students_file);
        fclose(results_file);
    }
    return 0;
}

void mainMenu() {
    system("cls");
    printf("\t|-------------------------------------------------------|\n");
    printf("\t|\t\t\tMAIN MENU\t\t\t|\n");
    printf("\t|-------------------------------------------------------|\n");
    printf("\t|\t1=> REGIST A STUDENT\t\t\t\t|\n");
    printf("\t|\t2=> MODIFY A STUDENT\t\t\t\t|\n");
    printf("\t|\t3=> DELETE A STUDENT\t\t\t\t|\n");
    printf("\t|-------------------------------------------------------|\n");
    printf("\t|\t4=> REGIST A RESULT\t\t\t\t|\n");
    printf("\t|\t5=> MODIFY A RESULT\t\t\t\t|\n");
    printf("\t|\t6=> DELETE A RESULT\t\t\t\t|\n");
    printf("\t|-------------------------------------------------------|\n");
    printf("\t|\t7=> PRINT CURRENT STUDENTS\t\t\t|\n");
    printf("\t|\t8=> PRINT CURRENT RESULTS\t\t\t|\n");
    printf("\t|-------------------------------------------------------|\n");
    printf("\t|\t0=> EXIT\t\t\t\t\t|\n");
    printf("\t|-------------------------------------------------------|\n");
}

StudentNode* newStudent(StudentNode* tree) {
    StudentInfo* new_student= (StudentInfo*) malloc(sizeof(StudentInfo));
    while(1) {
        printf("\n\tNAME OF THE NEW STUDENT: ");
        scanf(" %[^\n]", new_student->name);
        if (stringChecker(new_student->name, "INTRODUCE A VALID STUDENT NAME")==1) break;
    }
    printf("\n\t200! STUDENT NAME ADDED WITH SUCESS!!\n");
    while(1) {
        printf("\n\tID NUMBER OF THE NEW STUDENT: ");
        scanf(" %[^\n]", new_student->id_number);
        if (intChecker(new_student->id_number, 's', "INTRODUCE A VALID STUDENT ID NUMBER")==1) break;
    }
    printf("\n\t200! STUDENT ID NUMBER ADDED WITH SUCESS!!\n");
    tree= addStudent(tree, new_student);
    return tree;
}

CourseNode* newResult(CourseNode* tree) {
    CourseInfo* new_result= (CourseInfo*) malloc(sizeof(CourseInfo));
    static char str_result_id[DIM/5], str_result[DIM/5];
    static int result_id;
    new_result->classifications[0]= new_result->classifications[1]= 0;
    while(1) {
        printf("\n\tSTUDENT ID NUMBER OF THE NEW RESULT: ");
        scanf(" %[^\n]", new_result->aux_id);
        if (intChecker(new_result->aux_id, 's', "INTRODUCE A VALID STUDENT ID NUMBER")==1) break;
    } 
    printf("\n\t200! STUDENT ID NUMBER ADDED WITH SUCESS!!\n");
    while(1) {
        printf("\n\tCOURSE NAME: ");
        scanf(" %[^\n]", new_result->name);
        if (stringChecker(new_result->name, "INTRODUCE A VALID COURSE NAME")==1) break;
    } 
    printf("\n\t200! COURSE NAME ADDED WITH SUCESS!!\n");
    while(1) {
        printf("\n\tPROVE NUMBER (1 OR 2): ");
        scanf(" %[^\n]", str_result_id);
        result_id= intChecker(str_result_id, 'i', "INTRODUCE A VALID PROVE NUMBER");
        if (result_id==1 || result_id==2) break;
        else printf("\n\tERROR 406! INTRODUCE A VALID PROVE NUMBER!\n\n");
    } 
    printf("\n\t200! PROVE NUMBER ADDED WITH SUCESS!!\n");
    while(1) {
        printf("\n\t%s RESULT IN PROVE NUMBER %d OF %s: ", new_result->aux_id, result_id, new_result->name);
        scanf(" %[^\n]", str_result);
        if ((new_result->classifications[result_id-1]= floatChecker(str_result, 'f', "INTRODUCE A VALID PROVE NUMBER"))>=0 && new_result->classifications[result_id-1]<=20) break;
        else printf("\n\tERROR 406! INTRODUCE A VALID RESULT!\n\n");
    }
    printf("\n\t200! RESULT ADDED WITH SUCESS!!\n");

    tree= addCourse(tree, new_result);
    return tree;
}

StudentNode* modifyStudent(StudentNode* tree) {
    if (tree==NULL) {
        printf("\nERROR 400! THERES IS NO STUDENTS' DATA SAVED YET!\nBACKING TO MAIN MENU...\n\n");
        sleep(3);
    } else {
        char id_pretended[DIM/2];
        StudentInfo* student_found= (StudentInfo*)malloc(sizeof(student_found));
        system("cls");
        printf("\n=============SIGNED IN STUDENTS=============\n\n");
        printStudentsTree(tree);
        printf("\nWHAT IS THE ID OF THE STUDENT YOU WANT TO MODIFY?\nID: ");
        scanf(" %[^\n]", id_pretended);
        if ((student_found= searchStudentTreeByID(tree, id_pretended))==NULL) {
            printf("\nERROR 404! STUDENT NOT FOUND!\nBACKING TO MAIN MENU...\n");
            sleep(3);
        } else {
            char str_option[5], new_name[DIM*2], new_id[DIM/2];
            int option;
            printf("\n200! STUDENT FOUND!!\n\n");
            printf("NAME: %s\nID NUMBER: %s\n\n", student_found->name, student_found->id_number);
            do {
                printf("WHAT YOU WANT TO CHANGE? [1- NAME | 2- ID]");
                scanf(" %[^\n]", str_option);
                option= intChecker(str_option, 'i', "INTRODUCE A VALID OPTION");
            } while (option!=1 && option!=2);
            if (option==1) {
                while (1) {
                    printf("INSERT A NEW NAME: ");
                    scanf(" %[^\n]", new_name);
                    if (stringChecker(new_name, "INTRODUCE A VALID STUDENT NAME")==1) break;
                } strcpy(student_found->name, new_name);
                printf("\n200! STUDENT NAME CHANGED WITH SUCESS!!\n\n");
            } else {
                while (1) {
                    printf("INSERT A NEW ID NUMBER:");
                    scanf(" %[^\n]", new_id);
                    if (intChecker(new_id, 's', "INTRODUCE A VALID STUDENT ID NUMBER")==1) break;
                } strcpy(student_found->id_number, new_id);
                printf("\n200! STUDENT ID NUMBER CHANGED WITH SUCESS!!\n\n");
            }
        }
    }
    return tree;
}

CourseNode* modifyResult(CourseNode* tree) {
    if (tree==NULL) {
        printf("\nERROR 400! THERES IS NO STUDENTS' DATA SAVED YET!\nBACKING TO MAIN MENU...\n\n");
        sleep(3);
    } else {
        char student_id[DIM/2], course_name[DIM*2];
        CourseInfo* result_found= (CourseInfo*)malloc(sizeof(result_found));
        system("cls");
        printf("\n=============SIGNED IN RESULTS=============\n\n");
        printCoursesTree(tree);
        printf("\nWHAT IS THE STUDENT ID OF THE RESULT YOU WANT TO MODIFY?\nID: ");
        scanf(" %[^\n]", student_id);
        printf("\nWHAT IS THE COURSE NAME OF THE RESULT YOU WANT TO MODIFY?\nID: ");
        scanf(" %[^\n]", course_name);
        if ((result_found= searchResultTreeByIdAndName(tree, student_id, course_name))==NULL) {
            printf("\nERROR 404! RESULT NOT FOUND!\nBACKING TO MAIN MENU...\n");
            sleep(3);
        } else {
            char str_option[5];
            int option;
            printf("\n200! RESULT FOUND!!\n\n");
            printf("NAME: %s\nPROVE1: %.2f\tPROVE2: %.2f\n\n", result_found->name, result_found->classifications[0], result_found->classifications[1]);
            do {
                printf("WHAT YOU WANT TO CHANGE? [1- NAME | 2- STUDENT ID | 3- PROVE 1 | 4- PROVE 2]");
                scanf(" %[^\n]", str_option);
                option= intChecker(str_option, 'i', "INTRODUCE A VALID OPTION");
            } while (option!=1 && option!=2 && option!=3 && option!=4);
            if (option==MODIFY_NAME) {
                char new_name[DIM*2];
                while (1) {
                    printf("INSERT A NEW COURSE NAME: ");
                    scanf(" %[^\n]", new_name);
                    if (stringChecker(new_name, "INTRODUCE A VALID STUDENT NAME")==1) break;
                } strcpy(result_found->name, new_name);
                printf("\n200! COURSE NAME CHANGED WITH SUCESS!!\n\n");
            } else if (option==MODIFY_ID) {
                char new_id[DIM/2];
                while (1) {
                    printf("INSERT A NEW ID NUMBER:");
                    scanf(" %[^\n]", new_id);
                    if (intChecker(new_id, 's', "INTRODUCE A VALID STUDENT ID NUMBER")==1) break;
                } strcpy(result_found->aux_id, new_id);
                printf("\n200! STUDENT ID NUMBER CHANGED WITH SUCESS!!\n\n");
            } else {
                char str_result[5];
                float new_result;
                while (1) {
                    printf("INSERT THE NEW RESULT:");
                    scanf(" %[^\n]", str_result);
                    if ((new_result= floatChecker(str_result, 'f', "INTRODUCE A VALID STUDENT ID NUMBER"))!=-1) break;
                } 
                if (option==MODIFY_PROVE1) {
                    printf("\n200! PROVE 1 RESULT CHANGED WITH SUCESS!!\n\n");
                    result_found->classifications[0]= new_result;
                } else {
                    result_found->classifications[1]= new_result;
                    printf("\n200! PROVE 2 RESULT CHANGED WITH SUCESS!!\n\n");
                }
            }
        }
    } return tree;
}

CourseNode* checkResults(FILE* file, CourseNode* tree) {
    CourseInfo* new_course= NULL;
    int prove_id;
    while (!feof(file)) {
        new_course= (CourseInfo*) malloc(sizeof(CourseInfo));
        new_course->classifications[0]= new_course->classifications[1]= 0;
        fread(new_course->aux_id, sizeof(new_course->aux_id), 1, file);
        if (feof(file)) break;
        fread(new_course->name, sizeof(new_course->name), 1, file);
        if (feof(file)) break;
        fread(&prove_id, sizeof(int), 1, file);
        if (feof(file)) break;
        fread(&new_course->classifications[prove_id-1], sizeof(float), 1, file);
        tree= addCourse(tree, new_course);
    }
    free(new_course);
    return tree;
}

void saveData(FILE* students_file, FILE* results_file, StudentNode* students_tree, CourseNode* results_tree, char* students_file_name, char* results_file_name) {
    students_file=fopen(students_file_name, "wb");
    results_file= fopen(results_file_name, "wb");
    writeStudentsInFile(students_file, students_tree);
    writeResultsInFile(results_file, results_tree);
    fclose(students_file);
    fclose(results_file);
}

void writeStudentsInFile(FILE* fp, StudentNode* tree) {
    if (tree != NULL) {
        writeStudentsInFile(fp, tree->left);
        fwrite(tree->student->name, sizeof(tree->student->name), 1, fp);
        fwrite(tree->student->id_number, sizeof(tree->student->id_number), 1, fp);
        writeStudentsInFile(fp, tree->right);
    }
}

void writeResultsInFile(FILE* fp, CourseNode* tree) {
    if (tree != NULL) {
        writeResultsInFile(fp, tree->left);
        int prove_id;
        fwrite(tree->course->aux_id, sizeof(tree->course->aux_id), 1, fp);
        fwrite(tree->course->name, sizeof(tree->course->name), 1, fp);
        if (tree->course->classifications[0]==0) prove_id=2;
        else prove_id=1;
        fwrite(&prove_id, sizeof(int), 1, fp);
        fwrite(&tree->course->classifications[prove_id-1], sizeof(tree->course->classifications[prove_id-1]), 1, fp);
        writeResultsInFile(fp, tree->right);
    }
}
