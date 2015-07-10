#ifndef __KERNELLIST_H__
#define __KERNELLIST_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"list.h"
#include"net.h"
#define OffsetSize(h) \
(int)((char*)&h->list-(char*)h)

#define get_data(type,head,now)\
      (((type )((char *)now-OffsetSize(head)) )->data_list)

#define get_address(type,head,where)\
      ((type )((char *)where-OffsetSize(head)) )

#define def_var_by_type(type)\
      typeof(type)

#define malloc_size(type)\
      sizeof(type)

#define delete_each_pos(pos,list_member)\
      ( {typeof(pos) tmp;\
	tmp=pos;\
	__list_del_entry(&pos->list_member);\
	pos=list_entry(pos->list_member.prev,typeof(*pos),list_member);\
	free(tmp);\
	})
#define delete_all_pos(pos_head,data_member,list_member)\
      ({typeof(*pos_head)pos;\
       list_for_each_entry(pos,&pos_head->data_member,list_member)\
       delete_each_pos(pos,&pos->list_member,list_member);\
       free(pos_head);}\
       )

#define id_table_nu 20
#define database_nu 10
typedef struct{
      
      char type;
      long id[id_table_nu];
      int connect_fd;
      struct sockaddr_in fin;
      unsigned char databaseID[database_nu]; 

}kernellist_dt;




typedef struct DATA{

       kernellist_dt data_list;
       struct list_head list;
}kernellist,*pkernellist;

pkernellist kernellist_head;



typedef struct menu{
      int id;
      char name[20];
      int price;
}menu_data,*pmenu_data;

typedef struct{

     menu_data data_list;
    struct list_head list; 
}order_info,*porder_info;


typedef struct need_hanld{
      char record_handle_name[100];
}handle_data;

typedef struct data3{

      handle_data data_list;
      struct list_head list;

}need_handle_info,*pneed_handle_info;

typedef struct data4{

      int ip;
      float whole_price;
      char name[20][100];
      char idx;
}one_seat_data;

typedef struct one_seat{

      one_seat_data data_list;
      struct list_head list;
}one_seat_ifno,*pone_seat_ifno;


pneed_handle_info pneed_handle_head;
pone_seat_ifno pone_seat;

extern void initadress(pkernellist *I);
extern void order_info_initadress(porder_info *I);
extern void need_handle_initadress(pneed_handle_info *I);
extern void one_seat_initadress(pone_seat_ifno *I);
extern void show_kernellist(pkernellist h);
extern void del_kernellist_net(struct list_head *del,pkernellist *p,pkernellist h);
extern void del_all_order_info(porder_info h);
extern void del_order_info(struct list_head *del,porder_info *p,porder_info h);
extern void del_need_handle_ifno(struct list_head *del,pneed_handle_info *p,pneed_handle_info h);
extern void del_one_seat_ifno(struct list_head *del,pone_seat_ifno *p,pone_seat_ifno h);

extern void insert_kernellistB(struct list_head *in,struct list_head *new);
extern void insert_kernellistF(struct list_head *new,struct list_head *in);
extern bool empty_kernellist(pkernellist h1);
extern bool empty_all(struct list_head *h);


#endif
