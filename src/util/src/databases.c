#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "databases.h"

void database_init(char* server, char* user, char* password, char* database)
{
  conn = mysql_init(NULL);

  if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
  {
          exit(1);
  }
}

void set_table(char* table_name)
{
  g_table_name = table_name;
}

void insert_data(float temp, float alti, float press, float light, char* datetime)
{
  MYSQL_RES *res;

  double _temp = temp;
  double _alti = alti;
  double _press = press;
  double _light = light;

  char query[255];

  sprintf(query, "INSERT INTO %s (Temp, Light, Press, Alti, Date) VALUES ('%f', '%f', '%f', '%f', '%s')",
        g_table_name, temp, alti, press, light, datetime);

  if(mysql_query(conn, query))
  {
          return 1;
  }
}

void insert_data_wake(float temp, float alti, float press, float light, char* alarmtime, char* waketime)
{
  MYSQL_RES *res;

  double _temp = temp;
  double _alti = alti;
  double _press = press;
  double _light = light;

  char query[255];

  sprintf(query, "INSERT INTO %s (Temp, Light, Press, Alti, Alarmon, Alarmoff) VALUES ('%f', '%f', '%f', '%f', '%s', '%s')",
        g_table_name, temp, alti, press, light, alarmtime, waketime);

  if(mysql_query(conn, query))
  {
          return 1;
  }
}

void database_deinit()
{
  conn = NULL;
}
