#ifndef _DATA_H_
#define _DATA_H_

// include_file
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#define MASTER_LEN 32
#define SUCCES 1
#define ERROR -1

typedef struct {
    char title[30];
    char username[30];
    char password[30];
    char url[30];
    int is_pwned;
} password_t;

int new_file_password(char *filename);
int insert_password_in_file_db(char *filename);

#endif 