#ifndef __DATABASES_H__
#define __DATABASES_H__

#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

MYSQL *conn;
char* g_table_name;

void database_init(char* server, char* user, char* password, char* test);
void database_deinit();
void set_table(char* table_name);
void insert_data(float temp, float alti, float press, float light);

#endif  __DATABASES_H__
