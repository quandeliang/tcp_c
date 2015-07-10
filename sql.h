#ifndef __SQL_H__
#define __SQL_H__

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sqlite3.h>
#include"net.h"

extern void get_send_all_sql_ifno(int argc,char** argv,int connect_fd);
extern  int callback(void* out, int num, char** value, char** name);
extern void get_sql_ifno_by_id(int argc,char** argv,int id,pmenu_data get_ifno);

#endif
