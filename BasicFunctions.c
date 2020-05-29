int stringChecker(char *str, char* error) {
    for (unsigned int i=0 ; i<strlen(str);i++){
        if (str[i] >= '0' && str[i] <= '9') {
            printf("\nERROR 406! %s!!\n\n", error);
            return -1;
        }
    }
    return 1;
}

int intChecker(char *str_number, char* error){
    for (unsigned int i=0 ; i<strlen(str_number);i++){
        if (str_number[i] < '0' && str_number[i] > '9') {
            printf("\nERROR 406! %s!!\n\n", error);
            return -1;
        }
    }
    return atoi(str_number);
}