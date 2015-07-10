#include"net.h"
#include"gui.h"


struct pass_main{
      int argc;
      char **argv;
}para;

void * fun_main(void* arg){

      init_select_net(para.argc,para.argv);
      pthread_exit(0);
}

int main(int argc,char** argv){

      if(argc<3){
	fprintf(stderr,"Usage:%s <server_port> <server_ip>\n",argv[0]);
	exit(1);
	}

      para.argc=argc;
      para.argv=argv;

      char i;
      pthread_t tid;

      welcome();
      //创一线程与客户和厨房端通信，主线程处理服务器交互界面
      if((pthread_create(&tid,NULL,fun_main,NULL))){
	    perror("pthread_create");
	    exit(1);
      }
      //初始化待处理信息链表头
      need_handle_initadress(&pneed_handle_head);
      one_seat_initadress(&pone_seat);
      //初始化主界面指针
      get_homeifno_memory(&phome);

      //清空主画面信息
      bzero(phome,sizeof(home_info));
#if 1
      for(;;){

	    i=show_home_info(phome,refresh_homepageby_gui);
	    if(phome->home_page_flag)
	    phome->home_page_flag=0;
	    if(i=='e'||i=='q'){
		  printf("确认退出服务器?(y/n):");
		  scanf("%c",&i);
		  while(getchar()!='\n');

		  if(i=='n'||i=='N');
		  else
			break;
	    }else if(i=='1'||i=='2'){
	    
		  phome->home_page_flag=1;

	    }else if(i=='3');
	    else if(i=='c'||i=='C'){
		  for(i=0;i<happen_t;i++){
		   memset(phome->happen[i],0,happen_l);
		   memset(phome->handle_happen[i],0,happen_l);
		   if(i<unknow_t)
		   memset(phome->unknow_happen[i],0,happen_l);
		  }
		  phome->index=0;
		  phome->in=0;
		  phome->hardware_index=0;
		  show_home_info(phome,refresh_homepageby_server);
	    }
	    else{

		  printf("你要退出服务器吗?(y/n):");
		  scanf("%c",&i);
		  while(getchar()!='\n');

		  if(i=='n'||i=='N');
		  else
			break;
	    }

      }
	    byebye();
#endif
      exit(0);
      //pthread_exit(EXIT_SUCCESS);
}
