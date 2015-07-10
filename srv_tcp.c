#include"net.h"
#include"sql.h"
#include "android.h"
//#include "hardware.h"
#include "control.h"
#include<json/json.h>

#define send_buf_size 1024
#define confirm "999"
#define confirmn "999\n"
#define kitchen_cnt "kitchen"
#define kitchen_cntn "kitchen\n"
#define kitchen_ip "192.168.7.82"
#define kitchen_ok_recieve "厨房:成功接受"
#define msg_add 1
#define msg_erg 2
#define msg_del 3
#define msg_over 4
#define msg_man 5
#define error_1 "error_1"
#define error_2 "error_2"
#define error_3 "error_3"
#define cook_ok "上菜"
#define firstdata "..."
#define datafile "cook.db"
#define datanu  2
#define get_json_key_string "jingjing"
#define to_client_head "I am tcp_server_c!"
#define to_client_content "content"
#define  to_client_cmd "cmd" 
#define MSG_SIZE 512
#define to_php_databaseid "database_id"
#define to_php_hardware_id "hardware_id"
#define to_php_hardware_value "hardware_value"



#define get_seatbyip(type) (get_ip_last(inet_ntoa((type)->data_list.fin.sin_addr))) 







static pthread_t server_tid[3];
static int kitchen_fd=-1,msg_id;

int get_ip_last(char* ip){
      
      int nu=0;
      int i;
      for(i=0;i<strlen(ip);i++){
	    if(ip[i]=='.') nu++;
	    if(nu==3){
		   nu=atoi(ip+i+1);
		   break;
	    }
      }

     return nu; 

}



void *over(void* arg){
      pkernellist p;
      p=(pkernellist)arg;
      char urgent_buf[send_buf_size],check_flag=0,i;

      float a;
      pone_seat_ifno mypos;
      list_for_each_entry(mypos,&pone_seat->list,list){
      
	    if(mypos->data_list.ip==get_ip_last(inet_ntoa(p->data_list.fin.sin_addr) )){
		  a=mypos->data_list.whole_price;
		  //del_one_seat_ifno(&mypos->list,&mypos,pone_seat);
		  for(i=0;i<mypos->data_list.idx;i++)
			printf("第%d菜:%s\n",i+1,mypos->data_list.name[i]);
		  delete_each_pos(mypos,list);
		  check_flag=1;
		  break;
	    }
      }
      if(check_flag){
      phome->paid +=a;
      phome->urgent=gui_pay;
      bzero(urgent_buf,send_buf_size);
      sprintf(urgent_buf,RED"座位号:%d,请求结帐!消费总额为:%.2f(元)"NONE,\
		  get_ip_last(inet_ntoa(p->data_list.fin.sin_addr)),a); 
     // sprintf(urgent_buf,RED"座位号:%d,请求结帐!"NONE,\
//		  get_ip_last(inet_ntoa(p->data_list.fin.sin_addr))); 
      refresh_realtime_ifno_ser(phome,urgent_buf);
      }
      
      if((write(p->data_list.connect_fd,confirm,strlen(confirm)))==-1){
		  perror("write_confirm_over_to_cliet");
		  exit(1);
      }

      pthread_exit(0);
}

char home_buf[send_buf_size];

void msg_queue_init(){

      key_t key;
      if((key=ftok("/var/www/unixmen1.local/public_html/2",'1'))==-1){
	    perror("ftok");
	    exit(EXIT_FAILURE);
      }

      if((msg_id=msgget(key,IPC_CREAT|0666))==-1){
	    perror("getmsg");
	    exit(EXIT_FAILURE);
      }
      refresh_realtime_ifno_ser(phome,"communicate with php msg_id=%d",msg_id);

}

char *analy_json_str(pkernellist arg,long *ret,char *json){

      char *tmp=json;
      pkernellist p;
      p=(pkernellist)arg;
      json_object *json_analy_from_client;

      if(*ret=read(p->data_list.connect_fd,json,send_buf_size)){
	    ;
      }

      if(*ret>0){
      json_analy_from_client=json_tokener_parse(json);
      tmp=(char *)json_object_get_string(json_object_object_get(json_analy_from_client,get_json_key_string));
      }
     // printf("json=%s\n",tmp);
      return tmp;

      
}

/***proto:xxxx!xxxx!end*/ //return id; value is in argument 3 
long get_id_from_client_str(char *buf,char **skip, char *value)
{
      long tmp=0;
      //printf("outjson:%s\n",buf);

      while(1)
      {
	    tmp= tmp*10+ (*buf-'0');
	    if((tmp<0)||(*buf<'0')||(*buf>'9')){
		  return 0;
	    }
	    buf++;
	    if(*buf=='!')
		  break;
      }

      buf++;
      while(-5){
     
	    if(((*buf<'0')||(*buf>'9'))&& (*buf !='.')){
		  return -1;
	    }

	    if(value !=NULL){
		  strncat(value,buf,1);
	    }
	    buf++;
	    if((*buf=='e')||(*buf==';'))
		  break;
      
      }
      if(*buf==';')
	    buf++;

      *skip=buf;

      return tmp;
}
int send_to_client_json(char *buf,int count,int fd,char *cmd)
{
      struct json_object *json=NULL;
      json=json_object_new_object();
      json_object_object_add(json,get_json_key_string,
	    json_object_new_string(to_client_head));
      if(cmd!=NULL){
      json_object_object_add(json,to_client_cmd,
	    json_object_new_string(cmd));
      }
      json_object_object_add(json,to_client_content,
	    json_object_new_string(buf));
      buf=(char *)json_object_to_json_string(json);
      
      return write(fd,buf,strlen(buf));

}


 void _send_to_client(pkernellist mypos,int id,char * msg){

      phome->urgent=android_urgent;
      bzero(home_buf,strlen(home_buf));
      sprintf(home_buf,BROWN"往 安卓端:%s 回复 %s  id:%d"NONE,
      inet_ntoa(mypos->data_list.fin.sin_addr),msg,id);
      refresh_realtime_ifno_ser(phome,home_buf); 
      bzero(home_buf,strlen(home_buf));
      sprintf(home_buf,"%s%d",msg,id);
      if(send_to_client_json(home_buf, strlen(home_buf),mypos->data_list.connect_fd,"I")<0){
	    perror("no online write back ot android");
	    exit(1);
      }
 
 }

void del_id_in_hardware(pkernellist mypos,int id)
{
      int i=0;
      for(;;){
	    if(mypos->data_list.id[i]<=0)
		  break;
	    if(mypos->data_list.id[i]==id){
	    mypos->data_list.id[i]=0;
		  for(i++;mypos->data_list.id[i]>0;i++){
			      mypos->data_list.id[i-1]=mypos->data_list.id[i];
			      mypos->data_list.id[i]=0;
		  }
			break;
	    }
	    i++;
      }
}





bool noticeToOtherClient (pkernellist mypos,int id,int cmd)
{
	    int i;
	  bool check=false;  
	  pkernellist find;
      list_for_each_entry(find,&kernellist_head->list,list){
		  if(find->data_list.type != mypos->data_list.type&&(!strcmp(find->data_list.databaseID,mypos->data_list.databaseID))){

		 for(i=0;find->data_list.id[i] !=0 ;i++){
		 
		  if(id == find->data_list.id[i]){
		       check=true;	
		       if(cmd==1){  //add
		  if(mypos->data_list.type==HARDWARE_MSG_TYPE)
			_send_to_client(find,id,HARDWARE_IS_ON_LINE);
		  else if(mypos->data_list.type==ANDROID_MSG_TYPE)
			_send_to_client(mypos,id,HARDWARE_IS_ON_LINE);
		       }else if(cmd==0){//del
			if(mypos->data_list.type==HARDWARE_MSG_TYPE){
			//del_id_in_hardware(mypos,id);
			_send_to_client(find,id,HARDWARE_NO_ON_LINE);
			}
		 		       
		       }
			break;
		  }
		 }
	    }	  
	    }
      

      
     return check; 
}


void do_del_id_in_hardware(pkernellist mypos,int id){

      noticeToOtherClient (mypos,id,0);
      del_id_in_hardware(mypos,id);

}

int _send_data_to_php(unsigned char *databaseID,unsigned long id,unsigned char * value,char  *cmd){

      struct json_object *json=NULL;
      struct msgbuf _buf;
      _buf.mtype=1;
      bzero(_buf.text,strlen(_buf.text));
      json=json_object_new_object();
      json_object_object_add(json,get_json_key_string,
	    json_object_new_string(to_client_head));
      json_object_object_add(json,to_client_cmd,
	    json_object_new_string(cmd));
      json_object_object_add(json,to_php_databaseid,
	    json_object_new_string(databaseID));
      json_object_object_add(json,to_php_hardware_id,
	    json_object_new_ulong(id));
      json_object_object_add(json,to_php_hardware_value,
	    json_object_new_string(value));
      strcpy((char *)_buf.text,(char *)json_object_to_json_string(json));

     // refresh_realtime_ifno_ser(phome,(char *)_buf.text);
      if(*cmd=='w'){
      return  msgsnd(msg_id,&_buf,strlen(_buf.text),0);
      }

      return 0;

}

bool add_id_kernellist(pkernellist mypos,char *skip,char cmd){
	    
	    int i=0,j=0;
	    long ret;
	    char value[20];		  
	    bool check_id=false,flag=false;
	    //save led id to kernelist 
	    for(i=0;i<id_table_nu;i++){   
		  bzero(value,sizeof(value));
	    ret=get_id_from_client_str(skip,&skip,value);	
	    if(ret==0)
		  return false;
	    //refresh_realtime_ifno_ser(phome,"from hardware:ret=%d",ret);
	    for(j=0;mypos->data_list.id[j] != 0;j++){
		  if(mypos->data_list.id[j] ==ret ){
			flag=true;
			break;
		  }
	    }

	    if(!flag){
	    mypos->data_list.id[j]=ret;

		  //register id and notice to android client this id is online
		  if(mypos->data_list.type==HARDWARE_MSG_TYPE&&(cmd !='\0')){
		  phome->urgent=hardware_urgent;
		  bzero(home_buf,strlen(home_buf));
		  sprintf(home_buf,GREEN"来自 :%s 智能硬件:%ld 注册成功!"NONE,
			      inet_ntoa(mypos->data_list.fin.sin_addr),ret);
		  refresh_realtime_ifno_ser(phome,home_buf);
		  noticeToOtherClient(mypos,ret,1);
		  usleep(1000);
		  }else if(mypos->data_list.type==ANDROID_MSG_TYPE){
		  
		  noticeToOtherClient(mypos,ret,1);
		  usleep(1000);

		  }

	    }//ifflag
	    flag=false;
	    //send data to php
	    if(mypos->data_list.type==HARDWARE_MSG_TYPE&&cmd==HARDWARE_DATABASE_CMD){;
	    
	   /* if(_send_data_to_php(mypos->data_list.databaseID,(unsigned long)ret,value,"w")<0){
	      perror("_send_data_to_php");
		  pthread_exit(NULL);
	    }*/

       /* if(_send_data_to_php(1,ret,value,"w")<0){
		  perror("_send_data_to_php");
		  pthread_exit(NULL);
	    }
	*/
	    }
	    if(*skip=='e'){
		  if(ret) check_id=true;
		  break;
	    }
	    }
	    return check_id;

}

/*
void del_id_in_hardware(pkernellist mypos,int id)

bool goToMachAndroidId(pkernellist mypos)
{
      bool flag=false;
      pkernellist find;

      list_for_each_entry(find,&kernellist_head->list,list){
      
	    if(find->data_list.type==ANDROID_MSG_TYPE){
	    }
      }

}


*/

void *analy_info_from_client(void *arg)
{

      pkernellist mypos,find;
      mypos=(pkernellist)arg;
      kernellist eh;
      char *buf,*skip,*data_buf,cmd_buf[30];
      long   ret;
      int   i;
      char  cmd[20];
      bool check_id=false;
      bool have_come=false;
      
      if((buf=(char *)malloc(send_buf_size))==NULL){
	    perror("malloc send_buf_size");
	    pthread_exit(NULL);
      }
      
      while(1){   //do communicate
      
	    bzero(buf,strlen(buf));
	    skip=analy_json_str(mypos,&ret,buf);
		  
	    bzero(home_buf,strlen(home_buf));
	    sprintf(home_buf,"来自 :%s %s",
			      inet_ntoa(mypos->data_list.fin.sin_addr),buf);
		  refresh_realtime_ifno_ser(phome,home_buf);
      
      if(ret<=0||(!strncmp(skip,"exit",4))||(!strncmp(skip,"quit",4))) {
		
		  	    
		 memcpy((void *)&eh,(void *)mypos,sizeof(kernellist));
		  del_kernellist_net(&mypos->list,&mypos,kernellist_head);
		  if(eh.data_list.type==ANDROID_MSG_TYPE){
		  phome->seaten--;
		  phome->urgent=android_urgent;
		  bzero(home_buf,strlen(home_buf));
	     sprintf(home_buf,RED"%s 断开链接..."NONE,inet_ntoa(eh.data_list.fin.sin_addr));
	     refresh_realtime_ifno_ser(phome,home_buf); 
		  }
		  else if(eh.data_list.type==HARDWARE_MSG_TYPE){
		  phome->control_seaten--;
		  phome->urgent=hardware_urgent;
		  bzero(home_buf,strlen(home_buf));
	     sprintf(home_buf,RED"%s 断开链接..."NONE,inet_ntoa(eh.data_list.fin.sin_addr));
	     refresh_realtime_ifno_ser(phome,home_buf); 
		 
		  for(i=0;eh.data_list.id[i]!=0;i++)
		  {	
			noticeToOtherClient(&eh,eh.data_list.id[i],0);
			usleep(8000);
		  }
		  }else{ 
		  phome->unknow_seaten--;
		  bzero(home_buf,strlen(home_buf));
	     sprintf(home_buf,"未知:%s 断开链接...",inet_ntoa(eh.data_list.fin.sin_addr));
	     refresh_realtime_ifno_ser(phome,home_buf); 
		  }
	     close(eh.data_list.connect_fd);
	     break;

      }else if(!strncmp(skip,ANDROID_CLIENT_VERIFY,strlen(ANDROID_CLIENT_VERIFY))){
		
		  if(!have_come){

		  phome->seaten++;
		  phome->unknow_seaten--;
		  phome->urgent=android_urgent;
		  bzero(home_buf,strlen(home_buf));
	     sprintf(home_buf,BROWN"来自:%s 链接成功!"NONE,inet_ntoa(mypos->data_list.fin.sin_addr));
	     refresh_realtime_ifno_ser(phome,home_buf);
	     //refresh_realtime_ifno_ser(phome,BROWN"来自:%s 链接成功!"NONE,
			 //inet_ntoa(mypos->data_list.fin.sin_addr));
		  mypos->data_list.type=ANDROID_MSG_TYPE;
		  if(send_to_client_json("Welcome to jingjing serverC!", \
				    strlen("Welcome to jingjing serverC!"),\
				    mypos->data_list.connect_fd,NULL)<0){
			      perror("no online write back ot android");
			      exit(1);
			}

		  }
		  
	   // if(*data_buf =='f') continue;
	     skip=(char *)(skip+(char )strlen(ANDROID_CLIENT_VERIFY));
	     bzero(mypos->data_list.databaseID,strlen(mypos->data_list.databaseID));
	     get_id_from_client_str(skip,&skip,mypos->data_list.databaseID);
	     refresh_realtime_ifno_ser(phome,"databaseID=%s",mypos->data_list.databaseID);
	     skip++;
	     data_buf=skip-1;
	    
		  if(!have_come){
		  have_come=true;
	        add_id_kernellist(mypos,skip,'\0');
		for(i=0;mypos->data_list.id[i] !=0;i++)
		noticeToOtherClient(mypos,mypos->data_list.id[i],1);
		usleep(8000);
		  }
	    
	    phome->urgent=android_urgent;
	    bzero(home_buf,strlen(home_buf));
	    sprintf(home_buf,BROWN"来自:%s 命令%s"NONE,\
			inet_ntoa(mypos->data_list.fin.sin_addr),data_buf);
	    refresh_realtime_ifno_ser(phome,home_buf); 
      

	        add_id_kernellist(mypos,skip,'\0');
		//for(i=0;mypos->data_list.id[i] !=0;i++)
		//noticeToOtherClient(mypos,mypos->data_list.id[i],1);
		if(*data_buf=='w'){
		  for(;;){ 
		  //printf("skip=%c\n",*skip);
		  bzero(cmd,20);
		  ret=get_id_from_client_str(skip,&skip,cmd);
		  //printf("ret=%d\n",ret);
		  if(ret==0) break; //no more led
		  
		  list_for_each_entry(find,&kernellist_head->list,list){
		  if(find->data_list.type != mypos->data_list.type&&(!strcmp(find->data_list.databaseID,mypos->data_list.databaseID))){
		  for(i=0;i<id_table_nu;i++){
			if(find->data_list.id[i]==0)
			      break;
		  if(find->data_list.id[i]==ret){
		  //do notice to android client
		 // noticeToOtherClient(mypos,ret,1);
			bzero(cmd_buf,30);
			sprintf(cmd_buf,"%ld!%se",ret,cmd);
		  if(send_to_client_json(cmd_buf,strlen(cmd_buf),
				    find->data_list.connect_fd,"w")<0){
			      perror("android write to hardware");
			      exit(1);
			}
		  usleep(1000);
		  	phome->urgent=hardware_urgent;
		  bzero(home_buf,strlen(home_buf));
	     sprintf(home_buf,GREEN"正在往 控制中心:%s, 发送命令 %s"NONE,\
			 inet_ntoa(find->data_list.fin.sin_addr),cmd_buf);
		  refresh_realtime_ifno_ser(phome,home_buf);
		  check_id=true;
			break;

			}
		  } //for
		  if(check_id)
			break;
		  check_id=false;
		  }//if(type)
		  }//kernellist
		  if(*skip=='e')
			break;
		  }//for(;;)

		}
      }else if(!strncmp(skip,HARDWARE_CLIENT_VERIFY,strlen(HARDWARE_CLIENT_VERIFY))){

		  if(!have_come){
		  have_come=true;
		  phome->control_seaten++;
		  phome->unknow_seaten--;
		  mypos->data_list.type=HARDWARE_MSG_TYPE;
		  phome->urgent=hardware_urgent;
	     refresh_realtime_ifno_ser(phome, GREEN"来自:%s 链接成功!"NONE,\
			 inet_ntoa(mypos->data_list.fin.sin_addr));
		  /*if(send_to_client_json(WELCOME_HARDWARE, strlen(WELCOME_HARDWARE),\
				    mypos->data_list.connect_fd,NULL)<0){
			      perror("no online write back ot android");
			      exit(1);
			}*/
		  }
		  
		  skip=(char *)(skip+(char )strlen(ANDROID_CLIENT_VERIFY));
		  bzero(mypos->data_list.databaseID,strlen(mypos->data_list.databaseID));
		  sprintf(mypos->data_list.databaseID,"%ld",get_id_from_client_str(skip,&skip,NULL));
		  refresh_realtime_ifno_ser(phome,"databaseID=%s",mypos->data_list.databaseID);
		  skip++;
		  data_buf=skip-1;
		  phome->urgent=hardware_urgent;
	     refresh_realtime_ifno_ser(phome, GREEN"来自:%s 命令:%s"NONE,
			 inet_ntoa(mypos->data_list.fin.sin_addr),data_buf);
		  if((*data_buf ==HARDWARE_DATABASE_CMD)||( *data_buf == HARDWARE_REGISTER_CMD)){
		  check_id=add_id_kernellist(mypos,skip,*data_buf);
		 if(!check_id){
		  phome->urgent=hardware_urgent;
		  bzero(home_buf,strlen(home_buf));
		  sprintf(home_buf,RED"来自 :%s unknow hardware id register!"NONE,
			      inet_ntoa(mypos->data_list.fin.sin_addr));
		  refresh_realtime_ifno_ser(phome,home_buf);
		  
		  }

		  }
		   if(*data_buf=='n'){ ;//hardware not online
#if 1		
		  for(i=0;i<id_table_nu;i++){   

			      ret=get_id_from_client_str(skip,&skip,NULL);
			      refresh_realtime_ifno_ser(phome,"ret=%d",ret);
			      if(ret<=0)break;
			do_del_id_in_hardware(mypos,ret);
			usleep(8000);
		  	if(*skip=='e') break;	

			}
			
#endif
		  }//elseif data
      	  
      }else{
	   

		  refresh_realtime_ifno_ser(phome,"未知客户端:%s %s\n",
			      inet_ntoa(mypos->data_list.fin.sin_addr),buf);
		 // break;
      }
      }//while(1)

      free(buf);


      pthread_exit(0);

}

void init_select_net(int argc ,char **argv){

      int sock_fd,connect_fd;
      struct sockaddr_in sin,fin;
      fd_set readfds;
      int max_fd,slt_ret;
      struct timeval tv;
      pkernellist new,mypos;


      char ret;
      //1creat socket
      if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) ==-1){
	    perror("socket");
	    exit(1);
      }
      //2fill local address and port
      bzero(&sin,sizeof(struct sockaddr_in));

      sin.sin_family=AF_INET;
      sin.sin_port=htons(atoi(argv[1]));
      //sin.sin_addr.s_addr=inet_addr(argv[2]);
      inet_aton(argv[2],&sin.sin_addr);

      //get client ip and port 
      socklen_t len=sizeof(struct sockaddr_in);
      bzero(&fin,sizeof(struct sockaddr_in));
      //3bind address and socket
      if(bind(sock_fd,(struct sockaddr*)&sin,sizeof(struct sockaddr_in))==-1){
	    perror("bind");
	    exit(1);
      }
      //4listen...

      if(listen(sock_fd,100) == -1){
	    perror("listen");
	    exit(1);
      }
      max_fd=sock_fd;
      initadress(&kernellist_head); 
      //msg_queue_init();
      //5
      while(1){

	    FD_ZERO(&readfds);
	    FD_SET(sock_fd,&readfds);
	    list_for_each_entry(mypos,&kernellist_head->list,list)
		  FD_SET(mypos->data_list.connect_fd,&readfds);

	    tv.tv_sec=5;
	    tv.tv_usec=0;
	    if((slt_ret=select(max_fd+1,&readfds,NULL,NULL,&tv))==-1){
		  perror("select");
		  exit(1);
	    }else if(slt_ret==0){
		  //printf("timeout\n");
		  continue;
	    }else{
		  if(FD_ISSET(sock_fd,&readfds)){// have link request
			if((connect_fd=accept(sock_fd,(struct sockaddr*)&fin,&len))==-1){
			      perror("accept");
			      exit(1);
			}
			
			 phome->unknow_seaten++;
			if(phome->seaten>=all_seat){
			      phome->urgent=all_client;
			 refresh_realtime_ifno_ser(phome,"服务器链接客户端已到上限!");
			}
			
			
	    refresh_realtime_ifno_ser(phome,"新客户端 %s 请求链接...",inet_ntoa(fin.sin_addr));
			

			if((new=(pkernellist)malloc(sizeof(kernellist)))==NULL){
			      perror("malloc");
			      exit(1);
			}
			memset(new,0,sizeof(kernellist));
			new->data_list.connect_fd=connect_fd;
			new->data_list.fin=fin;
			list_add_tail(&new->list,&kernellist_head->list);
			if(max_fd<connect_fd)
			      max_fd=connect_fd;
		  if((pthread_create(server_tid,NULL,analy_info_from_client,(void *)new))){
			perror("pthread_create analy_info_from_client");
			exit(1);	
		  }	

			//printf("max_fd=%d connect_fd=%d\n",max_fd,connect_fd);
		  }
	    }


  } //while(1)


      //7close
      //close(connect_fd);
      close(sock_fd);

}
		  
