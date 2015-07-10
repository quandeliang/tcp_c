#include"net.h"


void *read_srv(void *arg)
{
      char buf[100];
      int fd=*(int *)arg;
      while(1){
	    
	    bzero(buf,sizeof(buf));
	     read(fd,buf,sizeof(buf));
	     printf("from other:%s\n",buf);
	     if(!strncmp(buf,"exit",strlen("eixt")))
	     {
		  break;
	     }
      
      }
      pthread_exit(0);
}

int main(int argc,char** argv){


      if(argc!=3){
	    fprintf(stderr,"Usage:%s <port> <ip>\n",argv[0]);
	    exit(1);
      }
      int sock_fd;
      struct sockaddr_in sin; 
      //1creat socket
      if((sock_fd = socket(AF_INET,SOCK_STREAM,0)) ==-1){
	        perror("socket");
	        exit(1);
      }
      //2fill address
      bzero(&sin,sizeof(struct sockaddr_in));
      sin.sin_family=AF_INET;
      sin.sin_port=htons(atoi(argv[1]));
      sin.sin_addr.s_addr=inet_addr(argv[2]);
#if 0
      //3bind address and socket
      if(bind(sock_fd,(struct sockaddr*)&sin,sizeof(struct sockaddr_in))==-1){
	        perror("dong_bind");
	        exit(1);
      }
      //4listen the socket
      if(listen(sock_fd,10)==-1){
	        perror("dong_listen");
	        exit(1);
      }
      //5wait the visiter
      if((connect_fd=accept(sock_fd,NULL,NULL))==-1){
	        perror("dong_accept");
	        exit(1);
      }
#endif
      
      //printf("pid=%d\n",getpid());
      if((connect(sock_fd,(struct sockaddr*)&sin,sizeof(sin)))==-1){
	        perror("dong_connect");
	        exit(1);
      }

      pthread_t tid;
      pthread_create(&tid,NULL,read_srv,(void *)&sock_fd);
      
      //6read and write
      char ret,buf[BUFSIZ];
      while(1){
	    bzero(buf,BUFSIZ);
	    fgets(buf,BUFSIZ,stdin); 
	    if((ret=write(sock_fd,buf,strlen(buf)))==-1){
	        perror("client_write");
	        exit(1);
	    }
	    else {
	    
		  if(!strncmp(buf,"exit",4)) break;
	    }
      }
      //7close
      close(sock_fd);

      exit(EXIT_SUCCESS);
}
