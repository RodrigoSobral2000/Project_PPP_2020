
int stringChecker(char *str, char* error) {
    for (unsigned int i=0 ; i<strlen(str);i++){
        if (str[i] >= '0' && str[i] <= '9') {
            printf("\nERROR 406! %s!!\n\n", error);
            return -1;
        }
    }
    return 1;
}

int intChecker(char *str_number, char number_type, char* error) {
    if (number_type=='i') {
        for (unsigned int i=0 ; i<strlen(str_number);i++){
            if (str_number[i] < '0' || str_number[i] > '9') {
                printf("\nERROR 406! %s!!\n\n", error);
                return -1;
            }
        } return atoi(str_number);
    } else {
        for (unsigned int i=0 ; i<strlen(str_number);i++){
            if ((str_number[i] < '0' || str_number[i] > '9')) {
                printf("\nERROR 406! %s!!\n\n", error);
                return -1;
            }
        } return 1;
    }
}

float floatChecker(char* str_number, char number_type, char* error) {
    if (number_type=='f') {
        for (unsigned int i=0 ; i<strlen(str_number);i++){
            if ((str_number[i] < '0' || str_number[i] > '9') && str_number[i]!=',' && str_number[i]!='.') {
                printf("\nERROR 406! %s!!\n\n", error);
                return -1;
            }
            else if (str_number[i]==',') str_number[i]='.';
        } return atof(str_number);
    } else {
        for (unsigned int i=0 ; i<strlen(str_number);i++){
            if ((str_number[i] < '0' || str_number[i] > '9') && str_number[i]!=',' && str_number[i]!='.') {
                printf("\nERROR 406! %s!!\n\n", error);
                return -1;
            }
        } return -2;
    }
}


StudentNode* readStudents(FILE* file, StudentNode* tree) {
    StudentInfo* new_student= NULL;
    while (!feof(file)) {
        new_student= (StudentInfo*) malloc(sizeof(StudentInfo));
        fread(new_student->name, sizeof(new_student->name), 1, file);
        if (feof(file)) break;
        fread(new_student->id_number, sizeof(new_student->id_number), 1, file);
        tree= addStudent(tree, new_student);
    }
    free(new_student);
    return tree;
}


StudentNode* addStudent(StudentNode *tree, StudentInfo* new_student) {
    int cond;
    if (tree == NULL) {
        tree = (StudentNode*) malloc(sizeof(StudentNode));
        tree->student= new_student;
        tree->student->signed_in_courses=NULL;
        tree->left= tree->right= NULL;
    } 
    else if (strcasecmp(new_student->id_number, tree->student->id_number)==0) return tree;
    else if ((cond = strcasecmp(new_student->name, tree->student->name))<=0) tree->left= addStudent(tree->left, new_student);
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

StudentInfo* searchStudentTreeByID(StudentNode* tree, char* id) {
    if (tree==NULL) return NULL;
    else {
        StudentInfo* student_searched= (StudentInfo*)malloc(sizeof(StudentInfo));
        if (strcasecmp(tree->student->id_number, id)!=0) {
            student_searched= searchStudentTreeByID(tree->left, id);
            if (student_searched!=NULL) return student_searched;
            student_searched= searchStudentTreeByID(tree->right, id);
            return student_searched;
        } else return tree->student;
    }
}

CourseInfo* searchResultTreeByIdAndName(CourseNode* tree, char* id, char* name) {
    if (tree==NULL) return NULL;
    else {
        CourseInfo* result_searched= (CourseInfo*)malloc(sizeof(CourseInfo));
        if (strcasecmp(tree->course->aux_id, id)!=0 && strcasecmp(tree->course->name, name)!=0) {
            result_searched= searchResultTreeByIdAndName(tree->left, id, name);
            if (result_searched!=NULL) return result_searched;
            result_searched= searchResultTreeByIdAndName(tree->right, id, name);
            return result_searched;
        } else return tree->course;
    }
}

void printStudentsTree(StudentNode* tree) {
    if (tree != NULL) {
        printStudentsTree(tree->left);
        printf("Name: %s\tID Number: %s\n", tree->student->name, tree->student->id_number);
        if (tree->student->signed_in_courses!=NULL) printCoursesTree(tree->student->signed_in_courses);
        printStudentsTree(tree->right);
    }
}

void printCoursesTree(CourseNode* tree) {
    if (tree != NULL) {
        printCoursesTree(tree->left);
        printf("Student: %s\tCourse: %s\tProve1: %.2f\tProve2: %.2f\n", tree->course->aux_id, tree->course->name, tree->course->classifications[0], tree->course->classifications[1]);
        printCoursesTree(tree->right);
    }
}
