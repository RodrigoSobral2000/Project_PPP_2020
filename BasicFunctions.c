int stringChecker(char *str, char* error) {
    for (unsigned int i=0 ; i<strlen(str);i++){
        if (str[i] >= '0' && str[i] <= '9') {
            printf("\nERROR 406! %s!!\n\n", error);
            return -1;
        }
    }
    return 1;
}

int numberChecker(char *str_number, char number_type, char* error) {
    if (number_type=='i') {
        for (unsigned int i=0 ; i<strlen(str_number);i++){
            if (str_number[i] < '0' || str_number[i] > '9') {
                printf("\nERROR 406! %s!!\n\n", error);
                return -1;
            }
        } return atoi(str_number);
    } else if (number_type=='f') {
        for (unsigned int i=0 ; i<strlen(str_number);i++){
            if ((str_number[i] < '0' || str_number[i] > '9') && str_number[i]!=',' && str_number[i]!='.') {
                printf("\nERROR 406! %s!!\n\n", error);
                return -1;
            }
            else if (str_number[i]==',') str_number[i]='.';
        } return atof(str_number);
    } else if (number_type=='s') {
        for (unsigned int i=0 ; i<strlen(str_number);i++){
            if ((str_number[i] < '0' || str_number[i] > '9')) {
                printf("\nERROR 406! %s!!\n\n", error);
                return -1;
            }
        } return 1;
    }
    return 0;
}