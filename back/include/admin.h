#ifndef _ADMIN_H_
#define _ADMIN_H_

#include "data.h"

 //define const
#define MASTER_FILE "setting.sqlite3"
#define P_MAX 20
#define H_MAX 100


typedef struct  {
    char master_hash[P_MAX];
    char hint[H_MAX];
} Admin, *Padmin ;

/*
@parms settings file master password
*/
int _init_(char *settings);
Admin *get_entry_save();
int authentificate(const char *hash_master);
//int change_master(Admin master);
int check_file_exist(char *file);
int insert_master(sqlite3 *db, Admin *master);
void check_sqlite_error(int rc, sqlite3 *db);
#endif 
