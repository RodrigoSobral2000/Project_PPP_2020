#include "../database.h"
#include "../BasicFunctions.c"

char* receiveFileName();

int main() {
    FILE *entry_file_students;
    FILE *entry_file_results;
    char file_name_students[DIM], file_name_results[DIM];
    while (1) {
        system("cls");
        entry_file_students= fopen(receiveFileName(file_name_students, 1), "r");
        if (entry_file_students!=NULL) break;
        else printf("\nERROR 404! FILE OF STUDENTS NOT FOUND!\n\n");
    } while (1) {
        system("cls");
        entry_file_results= fopen(receiveFileName(file_name_results, 2), "r");
        if (entry_file_results!=NULL) break;
        else printf("\nERROR 404! FILE OF RESULTS NOT FOUND!\n\n");
    }

    
    printf("Ya, es um bicho\n");
    fclose(entry_file_students);
    fclose(entry_file_results);
    return 0;
}

char* receiveFileName(char* file_name, int file_id) {
    do {
        if (file_id==1) printf("What is the name of entry student's data file? (no extension needed)\nName: ");
        else if (file_id==2) printf("What is the name of entry result's data file? (no extension needed)\nName: ");
        scanf(" %[^\n]", file_name);
        strcat(file_name, ".bin");
    } while (stringChecker(file_name, "INTRODUCE A VALID FILE NAME")==-1);
    return file_name;
}


//  ================================
//              CHECKERS
//  ================================

//  Check if it is a correct string
int stringChecker(char *str, char* error) {
    for (unsigned int i=0 ; i<strlen(str);i++){
        if (str[i] >= '0' && str[i] <= '9') {
            printf("\nERROR 406! %s!!\n\n", error);
            return -1;
        }
    }
    return 1;
}

//  Check if it is a correct number
int numberChecker(char *str_number, char* error){
    for (unsigned int i=0 ; i<strlen(str_number);i++){
        if (str_number[i] < '0' && str_number[i] > '9') {
            printf("\nERROR 406! %s!!\n\n", error);
            return -1;
        }
    }
    return atoi(str_number);
}