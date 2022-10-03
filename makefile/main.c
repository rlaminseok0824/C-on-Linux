#include <stdio.h>
#include "sum.h"

int main(){
	int a= 3, b= 4;
#ifdef DEBUG
	printf("Debug\n");
	printf("sum : %d\n",sum(a,b));
#else
	printf("Hello World!\n");
	printf("sum : %d\n",sum(a,b));

#endif
	return 1;
}
