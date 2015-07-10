#include"sql.h"


      static int calltimes = 0; 
 int callback(void* out, int num, char** value, char** name)
{
      int i,ret;
      //if(calltimes>=1&&calltimes<=10)
      if(calltimes)
      for(i=0; i<num; i++){
	    strncat(value[i],"\n",strlen(value[i]));
	    if((ret=write(*(int*)out,value[i],strlen(value[i])+1))==-1){
		  perror("write_send_all_ifno_to_client");
		  exit(1);
	    }
	    usleep(5000);
	    //printf("%s ", value[i]);
	    //if((i+1)%3==0)printf("\n");
      }
      

      //printf("number %d callback\n", calltimes);
      calltimes++;
      return 0; 
}


int callback_get_ifno(void* out, int num, char** value, char** name){
      
      pmenu_data p;
      p=(pmenu_data)out;

      //p->id=atoi(value[0]);
      strncpy(p->name,value[1],strlen(value[1]));
      p->price=atoi(value[2]);
/*
      for(i=0;i<num;i++){
	    printf("%s ",value[i]);
      }
  */   
      return 0;

}

void get_send_all_sql_ifno(int argc,char** argv,int connect_fd){

      if(argc!=2){
	    fprintf(stderr,"Usage:%s <filename>\n",argv[0]);
	    exit(1);
      }  
      sqlite3 *db;
      char *zErrMsg;
      int rc;
      //打开数据库
      if((rc=sqlite3_open(argv[1],&db))){
	    fprintf(stderr,"Can't not open database:%s\n",sqlite3_errmsg(db));
	    sqlite3_close(db);
	    exit(1);
      }
    
      //标准回调,获得数据
      //printf("send ifno to client:\n");
      if((rc=sqlite3_exec(db,"select * from cook_menu;",callback,(void *)&connect_fd,&zErrMsg)) !=SQLITE_OK){
	    fprintf(stderr,"callback\n");
	    exit(1);
      }
      calltimes=0;
      sqlite3_close(db);
}


void get_sql_ifno_by_id(int argc,char** argv,int id,pmenu_data get_ifno){

      if(argc!=2){
	    fprintf(stderr,"Usage:%s <filename>\n",argv[0]);
	    exit(1);
      }  
      sqlite3 *db;
      char *zErrMsg;
      char tmp[100];
      int rc;
      //打开数据库
      if((rc=sqlite3_open(argv[1],&db))){
	    fprintf(stderr,"Can't not open database:%s\n",sqlite3_errmsg(db));
	    sqlite3_close(db);
	    exit(1);
      }
      bzero(tmp,sizeof(tmp));
      sprintf(tmp,"select * from cook_menu where id=%d;",id);
      //标准回调,获得数据
      if((rc=sqlite3_exec(db,tmp,callback_get_ifno,(void *)get_ifno,&zErrMsg)) !=SQLITE_OK){
	    fprintf(stderr,"callback_getifno\n");
	    exit(1);
      }
      sqlite3_close(db);
}

