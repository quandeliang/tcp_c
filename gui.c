#include"gui.h"

void get_homeifno_memory(phome_info *p){

      if((*p=(phome_info)malloc(sizeof(home_info)))==NULL){
	    perror("home_info_malloc");
	    exit(1);
      }
}
char show_home_info(phome_info p,char who){

      char ch;
     
      //printf("show_flag=%d\n",p->home_page_flag);

      if(who==refresh_homepageby_gui){
            system("clear");
      printf("***********************< 欢迎使用静静服务器 >*********************\n");
      printf("*");
      printf(LINE" 剩余资源:%d                                           在线量:%d "NONE,\
		  all_seat-p->seaten-p->control_seaten-p->unknow_seaten,p->seaten);
      printf("*\n");
      printf("*                            安卓端                               *\n");
      printf("*   %s*\n",p->handle_happen[0]);
      printf("*   %s*\n",p->handle_happen[1]);
      printf("*   %s*\n",p->handle_happen[2]);
      printf("*   %s*\n",p->handle_happen[3]);
      printf("*   %s*\n",p->handle_happen[4]);
      printf("*   %s*\n",p->handle_happen[5]);
      printf("*   %s*\n",p->handle_happen[6]);
      printf("*");
      printf(LINE"                                                       在线量:%d "NONE,p->control_seaten);
      printf("*\n");
      printf("*                           控制中心端                            *\n");
      printf("*   %s*\n",p->happen[0]);
      printf("*   %s*\n",p->happen[1]);
      printf("*   %s*\n",p->happen[2]);
      printf("*   %s*\n",p->happen[3]);
      printf("*   %s*\n",p->happen[4]);
      printf("*   %s*\n",p->happen[5]);
      printf("*   %s*\n",p->happen[6]);
      printf("*");
      printf(LINE"                                                       在线量:%d "NONE,p->unknow_seaten);
      printf("*\n");
      printf("*			      其他                               *\n");
      printf("*   %s*\n",p->unknow_happen[0]);
      printf("*   %s*\n",p->unknow_happen[1]);
      printf("*   %s*\n",p->unknow_happen[2]);
      printf("*   %s*\n",p->unknow_happen[3]);
      printf("*");
      printf(LINE"                                                                 "NONE);
      printf("*\n");
      printf("*	    1: 历史信息                  2: 功能设置              *\n");
      printf("*******************************************************************\n");
      printf("享受科技生活,从静静开始!");
      printf("	          	       "); 
      printf("www.52jj.com\n");
      printf("请输入有效数字(1-2),清屏(c/C),退出(e/q):\n");
      scanf("%c",&ch);
      while(getchar()!='\n');

      }
#if 1
      else if(p->home_page_flag==0&&who==refresh_homepageby_server){
      //fprintf(stdin,"%s",tmp);
      //fflush(stdin);
      system("clear");


      printf("***********************< 欢迎使用静静服务器 >*********************\n");
      printf("*");
      printf(LINE" 剩余资源:%d                                           在线量:%d "NONE,\
		  all_seat-p->seaten-p->control_seaten-p->unknow_seaten,p->seaten);
      printf("*\n");
      printf("*                            安卓端                               *\n");
      printf("*   %s*\n",p->handle_happen[0]);
      printf("*   %s*\n",p->handle_happen[1]);
      printf("*   %s*\n",p->handle_happen[2]);
      printf("*   %s*\n",p->handle_happen[3]);
      printf("*   %s*\n",p->handle_happen[4]);
      printf("*   %s*\n",p->handle_happen[5]);
      printf("*   %s*\n",p->handle_happen[6]);
      printf("*");
      printf(LINE"                                                       在线量:%d "NONE,p->control_seaten);
      printf("*\n");
      printf("*                           控制中心端                            *\n");
      printf("*   %s*\n",p->happen[0]);
      printf("*   %s*\n",p->happen[1]);
      printf("*   %s*\n",p->happen[2]);
      printf("*   %s*\n",p->happen[3]);
      printf("*   %s*\n",p->happen[4]);
      printf("*   %s*\n",p->happen[5]);
      printf("*   %s*\n",p->happen[6]);
      printf("*");
      printf(LINE"                                                       在线量:%d "NONE,p->unknow_seaten);
      printf("*\n");
      printf("*			      其他                               *\n");
      printf("*   %s*\n",p->unknow_happen[0]);
      printf("*   %s*\n",p->unknow_happen[1]);
      printf("*   %s*\n",p->unknow_happen[2]);
      printf("*   %s*\n",p->unknow_happen[3]);
      printf("*");
      printf(LINE"                                                                 "NONE);
      printf("*\n");
      printf("*	    1: 历史信息                  2: 功能设置              *\n");
      printf("*******************************************************************\n");
      printf("享受科技生活,从静静开始!");
      printf("	          	       "); 
      printf("www.52jj.com\n");
      printf("请输入有效数字(1-2),清屏(c/C),退出(e/q):\n");
      //scanf("%c",&ch);
      //while(getchar()!='\n');
}
#endif
      //if(who==refresh_homepageby_gui){
      
      return ch;

} 

void welcome(void){

      system("clear");
      printf(back4"******************************************************************\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                     "NONE);
      printf(back4"< 静静 >    服务器"NONE);
      printf(back4"                         *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*              你想要的科技生活, 静静都能做到!                   *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"******************************************************************\n"NONE);

      printf("\n                         < Enter >   \
		  \n\n");

      while(getchar()!='\n');

}
void byebye(void){

      system("clear");
      printf(back4"******************************************************************\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                  "NONE);
      printf(RED"静静有您而精彩!  再会!"NONE);
      printf(back4"                        *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"*                                                                *\n"NONE);
      printf(back4"******************************************************************\n"NONE);


}

void refresh_realtime_ifno_ser(phome_info p,const char* format,...){
	
      char i; 
      char tmp[happen_l];
      va_list ap;
      bzero(tmp,happen_l);
      va_start(ap,format);
      vsprintf(tmp,format,ap);
      va_end(ap);
      if(p->urgent==android_urgent){  //android msg
      
	    if(p->in>=happen_t){  
      for(i=0;i<happen_t-1;i++){
	    bzero(p->handle_happen[i],happen_l);
	    sprintf(p->handle_happen[i],"%d: ",i+1);
	    del_nu_from_string(p->handle_happen[i+1]);
	    strcat(p->handle_happen[i],p->handle_happen[i+1]);
      }

	    bzero(p->handle_happen[i],happen_l);
	    sprintf(p->handle_happen[i],"%d: ",i+1);
	    strcat(p->handle_happen[i],tmp);
      }else{
      sprintf(p->handle_happen[((p->in)%happen_t)],"%d: ",(p->in)+1);
      strcat(p->handle_happen[((p->in++)%happen_t)],format);
      if(p->in>happen_t-1)p->in=happen_t;
      }
     
	   p->urgent=0; 

      }else if(p->urgent==hardware_urgent){  //hardware  msg
      
	    if(p->hardware_index>=happen_t){  
      for(i=0;i<happen_t-1;i++){
	    bzero(p->happen[i],happen_l);
	    sprintf(p->happen[i],"%d: ",i+1);
	    del_nu_from_string(p->happen[i+1]);
	    strcat(p->happen[i],p->happen[i+1]);
      }

	    bzero(p->happen[i],happen_l);
	    sprintf(p->happen[i],"%d: ",i+1);
	    strcat(p->happen[i],tmp);
      }else{
      sprintf(p->happen[((p->hardware_index)%happen_t)],"%d: ",(p->hardware_index)+1);
      strcat(p->happen[((p->hardware_index++)%happen_t)],tmp);
      if(p->hardware_index>happen_t-1)p->hardware_index=happen_t;
      }
     
	   p->urgent=0; 

      }
      else
      {
      if(p->index>=unknow_t){  
      for(i=0;i<unknow_t-1;i++){
	    bzero(p->unknow_happen[i],happen_l);
	    sprintf(p->unknow_happen[i],"%d: ",i+1);
	    del_nu_from_string(p->unknow_happen[i+1]);
	    strcat(p->unknow_happen[i],p->unknow_happen[i+1]);
      }

	    bzero(p->unknow_happen[i],happen_l);
	    sprintf(p->unknow_happen[i],"%d: ",i+1);
	    strcat(p->unknow_happen[i],tmp);
      }else{
      sprintf(p->unknow_happen[((p->index)%unknow_t)],"%d: ",(p->index)+1);
      strcat(p->unknow_happen[((p->index++)%unknow_t)],tmp);
      if(p->index>unknow_t-1)p->index=unknow_t;
      }
      }
      show_home_info(p,refresh_homepageby_server);
      

}

void insert_nu_to_string(int nu,char* text){

      char tmp[100];
      bzero(tmp,sizeof(tmp));
      sprintf(tmp,"%d:",nu);
      strcat(tmp,text);
      bzero(text,strlen(text));
      strcpy(text,tmp);
}
void del_nu_from_string(char *t){
      
	    char j,k,check=0; 
	    for(j=0,k=strlen(t);j<k;j++,t++){
		  if(*t==' '&&check==0){
			check=j;
		  }else if(check){
			t[-check-1]=*t;
		  }
	    }
	    //for(j=k-check,t=t-check;j<k;j++,t++)
	    memset((void*)(t-check-1),0,check+1);
}
