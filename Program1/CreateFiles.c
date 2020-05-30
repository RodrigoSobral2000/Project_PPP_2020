#include "../Database.h"
#include "../BasicFunctions.c"

int main(int argc, char const *argv[]) {
    if (argc!=3) fprintf(stderr, "wrong parameters");
    else {
        FILE *students_file= fopen(strcat(argv[1],".bin"), "wb");
        FILE *results_file= fopen(strcat(argv[2],".bin"), "wb");
        int option;
        char str_option[5];

        while (1) {
            do {
                mainMenu();
                printf("\n\tOption=> ");
                scanf(" %[^\n]", str_option);
                option= numberChecker(str_option, 'i', "INTRODUCE A VALID OPTION");
            } while (option<EXIT_OPTION || option>DELETE_RESULT_OPTION);

            if (option==ADD_STUDENT_OPTION || option==ADD_RESULT_OPTION) {
                if (option==ADD_STUDENT_OPTION) addElement(students_file, ID_STUDENT_FILE);
                else addElement(results_file, ID_RESULTS_FILE);
            } else if (option==MODIFY_STUDENT_OPTION || option==MODIFY_RESULT_OPTION) {
                //if (option==MODIFY_STUDENT_OPTION) modifyElement(students_file, ID_STUDENT_FILE);
                //else modifyElement(results_file, ID_RESULTS_FILE);
            } else if (option==DELETE_STUDENT_OPTION || option==DELETE_RESULT_OPTION) {
                //if (option==DELETE_STUDENT_OPTION) deleteElement(students_file, ID_STUDENT_FILE);
                //else deleteElement(results_file, ID_RESULTS_FILE);
            } else if (option==EXIT_OPTION) {
                printf("\n200! PROGRAM CLOSED WITH SUCESS!!\n\n");
                break;
            }
            sleep(3);
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
    printf("\t|\t0=> EXIT\t\t\t\t\t|\n");
    printf("\t|-------------------------------------------------------|\n");
}

void addElement(FILE *fp, int file_type) {
    if (file_type==ID_STUDENT_FILE) {
        char new_student_name[DIM*2], new_student_id[DIM/2];
        while(1) {
            printf("\n\tNAME OF THE NEW STUDENT: ");
            scanf(" %[^\n]", new_student_name);
            if (stringChecker(new_student_name, "INTRODUCE A VALID STUDENT NAME")==1) break;
        }
        printf("\n\t200! STUDENT NAME ADDED WITH SUCESS!!\n");
        while(1) {
            printf("\n\tID NUMBER OF THE NEW STUDENT: ");
            scanf(" %[^\n]", new_student_id);
            if (numberChecker(new_student_id, 's', "INTRODUCE A VALID STUDENT ID NUMBER")==1) break;
        }
        printf("\n\t200! STUDENT ID NUMBER ADDED WITH SUCESS!!\n");
        fwrite(new_student_name, sizeof(new_student_name), 1, fp);
        fwrite(new_student_id, sizeof(new_student_id), 1, fp);
    } else {
        char student_id[DIM/2], new_result_course[DIM], str_result_id[DIM/5], str_result[DIM/5];
        int result_id;
        float result;
        while(1) {
            printf("\n\tSTUDENT ID NUMBER OF THE NEW RESULT: ");
            scanf(" %[^\n]", student_id);
            if (numberChecker(student_id, 's', "INTRODUCE A VALID STUDENT ID NUMBER")==1) break;
        } 
        printf("\n\t200! STUDENT ID NUMBER ADDED WITH SUCESS!!\n");
        while(1) {
            printf("\n\tCOURSE NAME: ");
            scanf(" %[^\n]", new_result_course);
            if (stringChecker(new_result_course, "INTRODUCE A VALID COURSE NAME")==1) break;
        } 
        printf("\n\t200! COURSE NAME ADDED WITH SUCESS!!\n");
        while(1) {
            printf("\n\tPROVE NUMBER (1 OR 2): ");
            scanf(" %[^\n]", str_result_id);
            result_id= numberChecker(str_result_id, 'i', "INTRODUCE A VALID PROVE NUMBER");
            if (result_id==1 || result_id==2) break;
            else printf("\n\tERROR 406! INTRODUCE A VALID PROVE NUMBER!\n\n");
        } 
        printf("\n\t200! PROVE NUMBER ADDED WITH SUCESS!!\n");
        while(1) {
            printf("\n\t%s RESULT IN PROVE NUMBER %d OF %s: ", student_id, result_id, new_result_course);
            scanf(" %[^\n]", str_result);
            if ((result= numberChecker(str_result, 'f', "INTRODUCE A VALID PROVE NUMBER"))>=0 && result<=20) break;
            else printf("\n\tERROR 406! INTRODUCE A VALID RESULT!\n\n");
        }
        printf("\n\t200! RESULT ADDED WITH SUCESS!!\n");
        
        fwrite(student_id, sizeof(student_id), 1, fp);
        fwrite(new_result_course, sizeof(new_result_course), 1, fp);
        fwrite(&result_id, sizeof(int), 1, fp);
        fwrite(&result, sizeof(float), 1, fp);
    }
}
