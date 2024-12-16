#include "../include/admin.h"

#include <stdio.h>
#include <unistd.h>

void check_sqlite_error(int rc, sqlite3 *db) {
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);  
    }
}

int check_file_exist(char *file){
    return (access(file, F_OK) == 0) ? SUCCES : ERROR;
}


int _init_(char *setting_file) {

    if (check_file_exist(setting_file) == SUCCES) {
        fprintf(stderr, "Database already exists.\n");
        return ERROR;
    }

    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    rc = sqlite3_open(MASTER_FILE, &db);
    if (rc!=SQLITE_OK) {
        fprintf(stderr, "Impossible to create database: %s\n", sqlite3_errmsg(db));
        return ERROR;
    }

    const char *create_table = 
        "CREATE TABLE setting ("
        "id INTEGER PRIMARY KEY, "
        "master_hash TEXT NOT NULL, "
        "hint TEXT NOT NULL);";

    rc = sqlite3_exec(db, create_table, 0, 0, &errMsg);

    Admin *master = get_entry_save();
    insert_master(db, master);
    free(master);
    

    check_sqlite_error(rc, db);
    sqlite3_close(db);

    return SUCCES;
}

int insert_master(sqlite3 *db, Admin *master) {
    sqlite3_stmt *stmt;
    const char *request = "INSERT INTO setting (master_hash, hint) VALUES (?, ?);"; 

    int rc = sqlite3_prepare_v2(db, request, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_bind_text(stmt, 1, master->master_hash, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, master->hint, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    printf("User successfully registered in settings.\n");
    return 0;
}

Admin *get_entry_save(){
    Admin *master = calloc(1, sizeof(Admin));
    if(master==NULL){
        perror("erreur d'allocatio");
        exit(EXIT_FAILURE);
    }
    printf("Entry password admin : ");
    fgets(master->master_hash, P_MAX, stdin);
    master->master_hash[strlen(master->master_hash)-1]=='\0';
    printf("Entry your hint : ");
    fgets(master->hint, P_MAX, stdin);
    master->hint[strlen(master->hint)-1]=='\0';
    return master;
}

int authentificate(const char *hash_master){
    if (check_file_exist(MASTER_FILE) == ERROR) {
        fprintf(stderr, "no database\n");
        return ERROR;
    }

    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc = sqlite3_open(MASTER_FILE, &db);
    if (rc!=SQLITE_OK) {
        fprintf(stderr, "unable to open database: %s\n", sqlite3_errmsg(db));
        return ERROR;
    }
    const char *request = "SELECT master_hash FROM setting WHERE id=1";
    rc = sqlite3_prepare_v2(db, request, -1, &stmt, NULL);
    if(rc!= SQLITE_OK){
         fprintf(stderr, "Erreur lors de la préparation de la requête : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return ERROR;
    }
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char *hash_pass = (const char *)sqlite3_column_text(stmt, 0);
        if(strcmp(hash_master, hash_pass)){
            printf("   welcome  master \n");
            printf("value database  pass  :  %s\n", hash_master);
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return SUCCES;
        }
        
    } else { 

        printf("Aucun utilisateur trouvé avec id = 1\n");
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return ERROR;
}
