#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>

#define CLNT_MAX 10

int g_client_socket[CLNT_MAX];
int g_client_count = 0;

int main(int argc,char ** argv){

	int serv_sock;
	int clnt_sock;

	int clnt_addr_size;
	struct sockaddr_in clnt_addr;

	struct sockaddr_in serv_addr;
	serv_sock = socket(PF_INET,SOCK_STREAM,0); //socket 선언
	//PF_INET : Ipv4
	//SOCK_STREAM(1) : TCP 프로토콜, SOCK_DGRAM(2) : UDP 프로토콜
	//0이면 자동 search 후 넣음, IPPROTO_TCP(6) : TCP 프로토콜, IPPROTO_UDP(17) : UDP 프로토콜
	 
	serv_addr.sin_family = AF_INET; //Ipv4 사용
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //현재 PC IP 구하는 함수
	serv_addr.sin_port = htons(5555); //htons atoi(argv[1]) 넣기

	if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1){
		printf("bind error\n");
	}
	
	if(listen(serv_sock,5) == -1){
		printf("listen error");
	} //몇 명을 listen 상태로 대기하냐의 backlog : 5의 의미
	
	char buff[200];
	int recv_len = 0;
	while(1){
		clnt_addr_size = sizeof(clnt_addr);
		clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size); //소켓 받을 때 ip 주소 담아서 옴(2번째 인자)
		g_client_socket[g_client_count++] = clnt_sock;

		recv_len = read(clnt_sock,buff,200); //클라에서 받아온 sock, buff에 저장
		while(1){
			printf("recv : ");
			for(int i = 0; i < recv_len;i++){
			printf("%02x",(unsigned char)buff[i]);
			}
			printf("\n");

		}
	}
	return 1;
}
