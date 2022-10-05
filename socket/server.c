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
#define BUFFSIZE 200

int g_client_socket[CLNT_MAX];
int g_client_count = 0;
pthread_mutex_t g_mutex;

void send_all_clnt(char * msg,int my_sock){
	pthread_mutex_lock(&g_mutex);
	for(int i = 0 ; i < g_client_count;i++){
		printf("To . [%d]  send : %s\n",g_client_socket[i],msg);
		if(g_client_socket[i] != my_sock){
			write(g_client_socket[i],msg,strlen(msg)+1);
		}
	}
	pthread_mutex_unlock(&g_mutex);
}

void * clnt_connection(void * arg){
	int clnt_sock = (int)arg;
	int str_len = 0;
	char msg[BUFFSIZE];
	int i;
	while(1){	
		str_len = read(clnt_sock,msg,sizeof(msg)); //받은 문자열 길이 반환
		if(str_len == -1){
			printf("clnt[%d] exit\n",clnt_sock);

			break;
		}
		send_all_clnt(msg,clnt_sock);
		printf("recv : %s\n",msg);
	}
	
	pthread_mutex_lock(&g_mutex);
	
	close(clnt_sock);

	for(int i = 0; i < g_client_count ; i++){
		if(clnt_sock == g_client_socket[i]){
			for(;i<g_client_count -1;i++)
				g_client_socket[i] = g_client_socket[i + 1];
			break;
		}
	}
	pthread_mutex_unlock(&g_mutex);
	pthread_exit(0);
	return NULL;
}

int main(int argc,char ** argv){

	int serv_sock;
	int clnt_sock;

	pthread_t t_thread;

	int clnt_addr_size;
	struct sockaddr_in clnt_addr;

	struct sockaddr_in serv_addr;

	pthread_mutex_init(&g_mutex,NULL);

	serv_sock = socket(PF_INET,SOCK_STREAM,0); //socket 선언
	//PF_INET : Ipv4
	//SOCK_STREAM(1) : TCP 프로토콜, SOCK_DGRAM(2) : UDP 프로토콜
	//0이면 자동 search 후 넣음, IPPROTO_TCP(6) : TCP 프로토콜, IPPROTO_UDP(17) : UDP 프로토콜
	 
	serv_addr.sin_family = AF_INET; //Ipv4 사용
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //현재 PC IP 구하는 함수
	serv_addr.sin_port = htons(5555); //htons atoi(argv[1]) 넣기

	if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1){
		printf("bind error\n");
		exit(0);
	}
	
	if(listen(serv_sock,5) == -1){
		printf("listen error");
		exit(0);
	} //몇 명을 listen 상태로 대기하냐의 backlog : 5의 의미
	
	char buff[200];
	int recv_len = 0;
	while(1){
		clnt_addr_size = sizeof(clnt_addr);
		clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size); //소켓 받을 때 ip 주소 담아서 옴(2번째 인자)
		
		pthread_mutex_lock(&g_mutex);
		g_client_socket[g_client_count++] = clnt_sock;
		pthread_mutex_unlock(&g_mutex);

		pthread_create(&t_thread,NULL,clnt_connection,(void *)clnt_sock);

		//while(1){
		//	recv_len = read(clnt_sock,buff,200); //클라에서 받아온 sock, buff에 저장
		//	printf("recv : ");
		//	for(int i = 0; i < recv_len;i++){
		//		printf("%02x",(unsigned char)buff[i]);
		//	}
		//	printf("\n");
		//}
	}
	return 1;
}
