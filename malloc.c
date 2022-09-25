#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 200

typedef struct human{
	int num;
	char name[20];
	human * next;
}human;

human * head;
head = (human *)malloc(sizeof(human));

int g_h_num = 0;

void add_h(human * h_num){
	(h_num + g_h_num) -> num = (g_h_num + 1) * 2;
	sprintf(h_num[g_h_num++].name,"test%d",g_h_num);
	
}

void print_all(const human * h_num){
	int i = 0;
	while(h_num[i].num){
		printf("====\n");
		printf("[%d] : %d\n",i,h_num[i].num);
		printf("[%d] : %s\n",i,h_num[i].name);
		i++;
		if(i >= MAX){
			break;
		}
	}
}


int main(){
	human h_num[MAX];
	//int * h_num;
	//h_num =(int *)malloc(sizeof(int) * MAX); //malloc : 동적할당, 힙 영역에 메모리할당
	
	
	for(int i = 0; i < MAX;i++){
		add_h(h_num);
	}
	print_all(h_num);

	//free(h_num);
	return 0;
}
