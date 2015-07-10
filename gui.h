#ifndef __GUI_H__
#define __GUI_H__
#include"net.h"
#include"print.h"
#include<stdarg.h>

#define all_seat 100
#define happen_t 7
#define unknow_t 4
#define happen_l 200
#define refresh_homepageby_gui 'g'
#define refresh_homepageby_server 's'
#define gui_pay 1
#define no_kitchen 2
#define no_client 3
#define all_client 4
#define need_man 5
#define need_cook_ok 6
#define hardware_urgent 2
#define android_urgent 1



typedef struct gui{

      double all_order;
      double paid;
      char seaten;
      char control_seaten;
      char unknow_seaten;
      char happen[happen_t][happen_l];
      char handle_happen[happen_t][happen_l];
      char unknow_happen[unknow_t][happen_l];
      char index;
      char in;
      char hardware_index;
      char home_page_flag;
      char urgent;
      

}home_info,*phome_info;

phome_info phome;



extern void welcome(void);
extern void byebye(void);
extern void get_homeifno_memory(phome_info *p);
extern char show_home_info(phome_info p,char who);
extern void refresh_realtime_ifno_ser(phome_info p,const char* format,...);
extern void insert_nu_to_string(int nu,char* text);
extern void del_nu_from_string(char *t);

#endif
