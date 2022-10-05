#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUFFSIZE 200
//#define NAMESIZE 20
void * rcv(void * arg){
	int sock = (int) arg;
	char buff[BUFFSIZE];
	int len;
	while(1){
		len = read(sock,buff,sizeof(buff));

		if(len== -1){
			printf("sock close\n");
			break;
		}
		printf("%s",buff);
	}

	pthread_exit(0);
	return NULL;
}


int main(int argc,char ** argv){
	int sock;
	struct sockaddr_in serv_addr;
	pthread_t rcv_thread;
		
	char id[100];
	strcpy(id,argv[1]);
	printf("id : %s\n",id);

	sock = socket(PF_INET,SOCK_STREAM,0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(5555);

	if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))== -1){
		printf("connect() error");
	}

	pthread_create(&rcv_thread,NULL,rcv,(void *)sock);
	char msg[BUFFSIZE];
	char chat[100];
	while(1){
		gets(chat);
		sprintf(msg,"[%s] : %s",id,chat);
		printf("send : %s",msg);
		write(sock,msg,strlen(msg) + 1);
		sleep(1);
	}


	close(sock);	
	return 1;
}
