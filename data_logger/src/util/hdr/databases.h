#ifndef __DATABASES_H__
#define __DATABASES_H__

#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

MYSQL *conn;
char* g_table_name;

void database_init(char* server, char* user, char* password, char* database);
void database_deinit();
void set_table(char* table_name);
void insert_data(float temp, float alti, float press, float light, char* datetime);
void insert_data_wake(float temp, float alti, float press, float light, char* alarmtime, char* waketime);

#endif
