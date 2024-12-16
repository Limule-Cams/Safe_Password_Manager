#include "../include/data.h"


int new_file_password(char *filename){
    sqlite3 *db;
    int rc;
    char *errmsg = 0;
    rc = sqlite3_open(filename, &db);

    if (rc!=SQLITE_OK) {
        fprintf(stderr, "Impossible to create database: %s\n", sqlite3_errmsg(db));
        return ERROR;
    }
    const char *request = 
        "CREATE TABLE IF NOT EXISTS password_t("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT, "
        "username TEXT NOT NULL, "
        "password TEXT NOT NULL, "
        "url TEXT, "
        "is_pwned BOOLEAN DEFAULT 0);";

    rc = sqlite3_exec(db, request, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db); 
        return ERROR;
    }
    sqlite3_close(db);

    return SUCCES;
}

int insert_password_in_file_db(char *filename){
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    rc = sqlite3_open(filename, &db);
  
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db); 
        return ERROR;
    }
    
    const char *request = "INSERT INTO password_t (title, username, password, url, is_pwned) VALUES (?,?,?,?,?);";
    rc = sqlite3_prepare_v2(db, request, -1, &stmt, NULL);
     if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    password_t *pass = NULL;

    sqlite3_bind_text(stmt, 1, pass->title, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pass->title, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, pass->title, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, pass->title, -1, SQLITE_STATIC);

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