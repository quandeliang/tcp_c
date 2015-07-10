#include"kernellist.h"


void initadress(pkernellist *I){

   *I=(pkernellist)malloc(sizeof(kernellist));
   if(*I==NULL){
   perror("Failed to allocate storage\n");
   exit(1);
   }

   INIT_LIST_HEAD(&(*I)->list); 
   
}
void order_info_initadress(porder_info *I){

   *I=(porder_info)malloc(sizeof(order_info));
   if(*I==NULL){
   perror("Failed to allocate storage\n");
   exit(1);
   }

   INIT_LIST_HEAD(&(*I)->list); 
   
}
void need_handle_initadress(pneed_handle_info *I){

   *I=(pneed_handle_info)malloc(sizeof(need_handle_info));
   if(*I==NULL){
   perror("Failed to allocate storage\n");
   exit(1);
   }

   INIT_LIST_HEAD(&(*I)->list); 
   
}
 
void one_seat_initadress(pone_seat_ifno *I){

   *I=(pone_seat_ifno)malloc(sizeof(one_seat_ifno));
   if(*I==NULL){
   perror("Failed to allocate storage\n");
   exit(1);
   }

   INIT_LIST_HEAD(&(*I)->list); 
   
}
void del_all_order_info(porder_info h){
      
      porder_info mypos;
  list_for_each_entry(mypos,&h->list,list)
  del_order_info(&mypos->list,&mypos,h);
  free(h);

}
bool empty_all(struct list_head *h){


      if(h->next==h)
	    return true;
      else 
	    return false;
}
#if 0
void sort_kernellist(pkernellist h){

      struct list_head *p=h->list.next;
      struct list_head *insert=h->list.prev,*temp;

      while(p!=insert){
       
	    if((int)(get_data(pkernellist,h,p)%2)!=0)
		   p=p->next;
	    else{
	           
		   temp=p;
                   p=p->next;

		   //Cut
                      //del_kernellist(temp);
		      //list_del(temp);
		      
		  //move
		      //list_move_tail(temp,insert);
		      list_move(temp,insert);


		   //insert_kernellistB(insert,temp);
		   //list_add(temp,insert);
		   //insert_kernellistF(temp,insert);

	    
	    }

      
      }
                  //printf("\n");

}
#endif

void del_kernellist(struct list_head *del){
       
      del->prev->next=del->next;
      del->next->prev=del->prev;
}

void del_kernellist_net(struct list_head *del,pkernellist *p,pkernellist h){
     
      struct list_head *tmp;
      tmp=del->prev; 
      del->prev->next=del->next;
      del->next->prev=del->prev;
      free(*p);
      *p=get_address(pkernellist,h,tmp);
}
void del_order_info(struct list_head *del,porder_info *p,porder_info h){

      struct list_head *tmp;
      tmp=del->prev; 
      del->prev->next=del->next;
      del->next->prev=del->prev;
      free(*p);
      *p=get_address(porder_info,h,tmp);
}
void del_need_handle_ifno(struct list_head *del,pneed_handle_info *p,pneed_handle_info h){

      struct list_head *tmp;
      tmp=del->prev; 
      del->prev->next=del->next;
      del->next->prev=del->prev;
      free(*p);
      *p=get_address(pneed_handle_info,h,tmp);
}
void del_one_seat_ifno(struct list_head *del,pone_seat_ifno *p,pone_seat_ifno h){
     
      struct list_head *tmp;
      tmp=del->prev; 
      del->prev->next=del->next;
      del->next->prev=del->prev;
      free(*p);
      *p=get_address(pone_seat_ifno,h,tmp);
}

void insert_kernellistB(struct list_head *in,struct list_head *new){
   
      new->next=in->next;
      new->prev=in;
      in->next->prev=new;
      in->next=new;

}

void insert_kernellistF(struct list_head *new,struct list_head *in){

      new->next=in;
      new->prev=in->prev;
      in->prev->next=new;
      in->prev=new;
}


void show_kernellist(pkernellist h){
  
  //pkernellist mypos;
  //list_for_each_entry(mypos,&h->list,list)
  //printf("%d ", mypos ->data_list);
  
   //struct list_head *p;
  //for(p=h->list.next;p!= &h->list;p=p->next)
    // printf("%d ",get_data(pkernellist,h,p));
     
 // printf("\n");
}

bool empty_kernellist(pkernellist h1){

     if(h1->list.prev==&h1->list)
	   return true;
     else 
	   return false;
}
