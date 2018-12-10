#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include "databases.h"

void database_init(char* server, char* user, char* password, char* database)
{
  // char *server = "localhost";
  // char *user = "root";
  // char *password = "";
  // char *database = "test";


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

  printf("\n\n%s\n\n", query);

  if(mysql_query(conn, query))
  {
          return 1;
  }
}

void database_deinit()
{
  conn = NULL;
}

// int main()
// {
//   float a = 1.1;
//
//
//   database_init("localhost", "root", "1111", "4linux");
//   set_table("logs");
//   insert_data(a, a, a, a);
//   database_deinit();
//
//   return 0;
// }

// int main()
// {
//         MYSQL *conn;
//         MYSQL_RES *res;
//         MYSQL_ROW row;
//
//         char *server = "localhost";
//         char *user = "root";
//         char *password = "";
//         char *database = "test";
//
//
//         conn = mysql_init(NULL);
//
//         if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
//         {
//                 exit(1);
//         }
//         if(mysql_query(conn,"show tables"))
//         {
//                 exit(1);
//         }
//
//         res = mysql_use_result(conn);
//         printf("MYSQL Tables in mysql database : \n");
//         while((row = mysql_fetch_row(res)) != NULL)
//                 printf("%s \n",row[0]);
//
//
//         if(mysql_query(conn,"SELECT * FROM R_TEST"))
//         {
//                 return 1;
//         }
//
//         res = mysql_use_result(conn);
//
//         printf("Returning List of Names : \n");
//         while((row = mysql_fetch_row(res)) != NULL)
//                 printf("%s %s %s \n",row[0],row[1],row[2]);
//
//
//         mysql_free_result(res);
//         mysql_close(conn);
//         return 0;
// }
