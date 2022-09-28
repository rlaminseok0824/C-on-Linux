#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	int num;
	char name[20];
	struct node * next;
}node;

node * g_head = NULL;
node * g_tail = NULL;


node * find(int num){
	node * temp = g_head;
	while(temp){
		if(temp->num == num){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}


void printAll(){
	node * temp = g_head;
	while(temp->next){
		printf("======\n");
		printf("num : %d\n",temp->num);
		printf("name : %s\n",temp->name);
		temp = temp->next;
	}
	printf("======\n");
	printf("num : %d\n",temp->num);
	printf("name : %s\n",temp->name);	
}

int insert(int num,char * name){	
	node * insertNode = malloc(sizeof(node));
	
	insertNode->next = NULL;
	insertNode->num = num;
	if(name != NULL){
		strcpy(insertNode->name,name);
	}

	if(g_head == NULL){
		g_head = insertNode;
		g_tail = insertNode;
	}
	else{
		node * temp = g_head;
		while(temp->next){
			temp = temp->next;	
		}
		temp->next = insertNode;
		g_tail = insertNode;
	}

	return 1;
}


int main(){
	char name[20] = "";
	for(int i = 0; i < 10;i++){
		sprintf(name,"test%d",i);
		insert(i,name);
	}
	printAll();
	node * t_node = find(5);
	printf("node_num : %d\n",t_node->num);
	printf("node_name : %s\n",t_node->name);

	return 0;
}
