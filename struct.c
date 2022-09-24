#include<stdio.h>
#include<string.h>

typedef struct human{
	char name[20];
	int age;
	char gender;
}human;


typedef struct student{
	int s_id;
	//char name[20];
	human * man;
	char temp;
}st;

//typedef struct student st;

void std_func(st * st1);

int main(){

	st st1;
	human hm;
	st1.man = &hm;
	std_func(&st1);

	printf("human size : %ld\n",sizeof(hm));
	printf("st size : %ld\n",sizeof(st1)); //효율을 위하여 포인터가 8byte이므로 나머지도 8byte 메모리 할당
	printf("s_id : %d\n",st1.s_id);
	printf("s_id : %s\n",st1.man->name);


	printf("st1 : %p\n",st1); //st1의 주소는 struct 선언의 주소(아무 값 x) => 헤더값을 주소로 가짐?
	printf("&st1 : %p\n",(&st1)); //&st1의 주소는 struct의 첫번째 변수의 주소
	return 1;
}
void std_func(st * st1){
	st1->s_id = 10;
	strcpy(st1->man->name,"Kim min seok");
	printf("s_id : %d\n",st1->s_id);
	printf("s_id : %s\n",st1->man->name);
}
