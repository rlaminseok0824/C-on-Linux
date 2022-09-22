#include<stdio.h>

void swap(int *a,int* b)
{
	printf("a : %d, b : %d\n",*a,*b);	
	int c;
	c = *a;
	*a = *b;
	*b = c;
}

void test(){
	printf("func test\n");
}

int main(){

	char str[100] = "hello world\n";
	char* pstr = str;

	while(*pstr){
		putchar(*pstr++);
	}
	
	void (*fp)();

	fp = swap;
	int a = 3; int b = 5;
	fp();

	fp = test;
	fp();
	
	return 0;
}
