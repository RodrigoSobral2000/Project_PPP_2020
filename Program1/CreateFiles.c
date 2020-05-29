#include "../Database.h"
#include "../BasicFunctions.c"

void mainMenu();
void addElement(FILE*, int);

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
                option= intChecker(str_option, "INTRODUCE A VALID OPTION");
            } while (option<EXIT_OPTION || option>DELETE_RESULT_OPTION);

            if (option==ADD_STUDENT_OPTION || option==ADD_RESULT_OPTION) {
                printf("ta a dar fixe");
                if (option==ADD_STUDENT_OPTION) addElement(students_file, ID_STUDENT_FILE);
                //else addElement(results_file, ID_RESULTS_FILE);
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
        char new_student_name[DIM*2], str_new_student_id[DIM];
        int new_student_id;
        while (1) {
            printf("NAME OF THE NEW STUDENT: ");
            scanf(" %[^\n]", new_student_name);
            if (stringChecker(new_student_name, "INTRODUCE A VALID STUDENT NAME")==1) break;
        } while(1) {
            printf("ID NUMBER OF THE NEW STUDENT: ");
            scanf(" %[^\n]", new_student_id);
            if ((new_student_id=intChecker(new_student_id, "INTRODUCE A VALID STUDENT ID NUMBER"))!=-1) break;
        }
        fwrite(new_student_name, sizeof(new_student_name), 1, fp);
        fwrite(new_student_id, sizeof(new_student_id), 1, fp);
    } else {

    }
}
