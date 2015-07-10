#ifndef __NET_H__
#define __NET_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include"kernellist.h"
#include"pthread.h"
#include"gui.h"
#include"mymsg.h"

#define get_sql_buf_size 1024

extern void init_select_net(int argc ,char **argv);

char get_spl_buf[get_sql_buf_size];

/*typedef struct pass{

      int tid_i;
      int connect_fd;
      struct sockaddr_in fin;

}pthread_pass;
*/

#endif
