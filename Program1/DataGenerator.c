#include "../Database.h"
#include "../BasicFunctions.c"

int main(int argc, char *argv[]) {
    if (argc!=3) fprintf(stderr, "wrong parameters\npass the two files' names you want to create (no extension needed)");
    else {
        static FILE *students_file;
        static FILE *results_file;
        static char aux[DIM];
        static StudentNode *students_tree=NULL;
        static CourseNode *results_tree=NULL;
        
        //  IF A FILE EXISTS ONLY APPENDS DATA
        strcpy(aux, strcat(argv[ID_STUDENT_FILE], ".bin"));
        if(access(aux, F_OK)!=-1) {
            FILE *fp= fopen(aux, "rb");
            students_tree= readStudents(fp, students_tree);
            fclose(fp);
            students_file= fopen(aux, "ab");
        } else students_file= fopen(aux, "wb");
        strcpy(aux, strcat(argv[ID_RESULTS_FILE], ".bin"));
        if(access(aux, F_OK)!=-1) {
            FILE *fp= fopen(aux, "rb");
            results_tree= checkResults(fp, results_tree);
            fclose(fp);
            results_file= fopen(aux, "ab");
        } else results_file= fopen(aux, "wb");

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
                if (option==ADD_STUDENT_OPTION) students_tree= newStudent(students_file, students_tree);
                else results_tree= newResult(results_file, results_tree);
                sleep(3);
            } else if (option==MODIFY_STUDENT_OPTION || option==MODIFY_RESULT_OPTION) {
                if (option==MODIFY_STUDENT_OPTION) students_tree= modifyStudent(students_file, students_tree);
                else results_tree= modifyResult(results_file, results_tree);
            } else if (option==DELETE_STUDENT_OPTION || option==DELETE_RESULT_OPTION) {
                //if (option==DELETE_STUDENT_OPTION) deleteElement(students_file, ID_STUDENT_FILE);
                //else deleteElement(results_file, ID_RESULTS_FILE);
            } else if (option==PRINT_CUR_STUDENTS) {
                if (students_tree==NULL) {
                    printf("\nERROR 400! THERES IS NO STUDENTS' DATA SAVED YET!\nBACKING TO MAIN MENU...\n\n");
                    sleep(3);
                } else {
                    system("cls");
                    printStudentsTree(students_tree);
                    sleep(7);
                    /*do {
                        system("cls");
                        printStudentsTree(students_tree);
                        printf("\n\nENTER TO CONTINUE... ");
                        scanf(" %c", &enter_pressed);
                    } while (enter_pressed!='\n');*/
                }
            } else if (option==PRINT_CUR_RESULTS) {
                if (results_tree==NULL) {
                    printf("\nERROR 400! THERES IS NO RESULTS' DATA SAVED YET!\nBACKING TO MAIN MENU...\n\n");
                    sleep(3);
                } else {
                    system("cls");
                    printCoursesTree(results_tree);
                    sleep(7);
                    /*do {
                        system("cls");
                        printCoursesTree(results_tree);
                        printf("\n\nENTER TO CONTINUE... ");
                        scanf(" %c", &enter_pressed);
                    } while (enter_pressed!='\n');*/
                }
            } else if (option==EXIT_OPTION) {
                printf("\n200! PROGRAM CLOSED WITH SUCESS!!\n\n");
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

StudentNode* newStudent(FILE *fp, StudentNode* tree) {
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
    fwrite(new_student->name, sizeof(new_student->name), 1, fp);
    fwrite(new_student->id_number, sizeof(new_student->id_number), 1, fp);
    tree= addStudent(tree, new_student);
    return tree;
}

CourseNode* newResult(FILE *fp, CourseNode* tree) {
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
    
    fwrite(new_result->aux_id, sizeof(new_result->aux_id), 1, fp);
    fwrite(new_result->name, sizeof(new_result->name), 1, fp);
    fwrite(&result_id, sizeof(int), 1, fp);
    fwrite(&new_result->classifications[result_id-1], sizeof(new_result->classifications[result_id-1]), 1, fp);
    tree= addCourse(tree, new_result);
    return tree;
}

StudentNode* modifyStudent(StudentNode* tree) {
    if (tree==NULL) {
        printf("\nERROR 400! THERES IS NO STUDENTS' DATA SAVED YET!\nBACKING TO MAIN MENU...\n\n");
        sleep(3);
    } else {
        char id_pretended[DIM/2];
        StudentInfo* student_found=NULL;
        system("cls");
        printf("WHAT IS THE ID OF THE STUDENT YOU WANT TO MODIFY?\nID: ");
        scanf(" %[^\n]", id_pretended);
        if ((student_found= searchStudentTree(tree, id_pretended))==NULL) {
            printf("\nERROR 404! STUDENT NOT FOUND!\nBACKING TO MAIN MENU...\n");
            sleep(3);
        } else {
            char *str_option[5], new_name[DIM*2], new_id[DIM/2];
            int option;
            printf("\n200! STUDENT FOUND!!\n\n");
            printf("NAME: %s\nID NUMBER: %s\n\n", student_found->name, student_found->id_number);
            do {
                printf("WHAT YOU WANT TO CHANGE? [1- NAME | 2- ID]");
                scanf(" %[^\n]", str_option);
                option= intChecker(str_option, 'i', "INTRODUCE A VALID OPTION")
            } while (option!=1 && option!=2);
            if (option==1) {
                while (1) {
                    printf("INSERT A NEW NAME:");
                    scanf(" %[^\n]", new_name);
                    if (stringChecker(new_name, "INTRODUCE A VALID STUDENT NAME")==1) break;
                } student_found->name=new_name;
            } else {
                while (1) {
                    printf("INSERT A NEW ID NUMBER:");
                    scanf(" %[^\n]", new_id);
                    if (intChecker(new_id, 's', "INTRODUCE A VALID STUDENT ID NUMBER")==1) break;
                } student_found->id_number=new_id;
            }
        }
    }
}

CourseNode* modifyResult(CourseNode* tree) {

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
