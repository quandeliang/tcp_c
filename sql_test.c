#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sqlite3.h>



#if 1
int callback(void* notused, int argc, char** argv, char** azColName)
{
      int i;
      static int calltimes = 0; 
      calltimes++;
      for(i=0; i<argc; i++)
	    printf("%s=%s\n", azColName[i], argv[i]);
      printf("number %d callback\n", calltimes);
      return 0; 
}

#endif


int main(int argc,char** argv){

      if(argc!=2){
	    fprintf(stderr,"Usage:%s <filename>\n",argv[0]);
	    exit(1);
      }  
      sqlite3 *db;
      char *zErrMsg,*statement;
      int rc,i;
      if((rc=sqlite3_open(argv[1],&db))){
	    fprintf(stderr,"Can't not open database:%s\n",sqlite3_errmsg(db));
	    sqlite3_close(db);
	    exit(1);
      }
        rc=sqlite3_exec(db,"create table cook_menu(id int,name varchar(20),price int);",NULL,NULL,&zErrMsg);
    

#if 1
	for(i=0;i<3;i++){
	      
	    statement=sqlite3_mprintf("insert into cook_menu(id,name,price) values(123,'ddd',456);",0,0,&zErrMsg);

	    rc=sqlite3_exec(db,statement,NULL,0,0);
	    sqlite3_free(statement);
      }

      rc=sqlite3_exec(db,"select * from cook_menu;",callback,0,&zErrMsg);
      sqlite3_close(db);
#endif
      return 0;
}

