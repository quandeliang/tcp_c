
#ifndef __MYMSG_H__
#define __MYMSG_H__

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<signal.h>
#include<sys/msg.h>


#define MSG_SZIE 512
struct msgbuf{
      long mtype;
      char text[MSG_SZIE];
};

#endif
