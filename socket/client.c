#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>

//#define BUFFSIZE 200
//#define NAMESIZE 20


int main(){
	int sock;
	struct sockaddr_in serv_addr;

	sock = socket(PF_INET,SOCK_STREAM,0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(5555);

	if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))== -1){
		printf("connect() error");
	}
	unsigned char buff[200] = {0x01,2,3,4,5,6,7,8,9};
	while(1){
		printf("send : \n");
		write(sock,buff,9);
		sleep(1);
	}


	close(sock);

	
	
	return 1;
}
