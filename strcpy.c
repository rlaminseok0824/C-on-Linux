#include<stdio.h>
//#include<string.h>

size_t strlen(const char *s);
char *strcpy(char *dest,const char *src);
int strcmp(const char *s1,const char *s2);


int main(){
	//for strcpy
	//char str[20] = "hello world\n";
	//char str_c[20] = "good job!\n";
	
	char str[20] = "aba";
	char str_a[20] = "abac";

	printf("%d\n",strcmp(str,str_a));

/*
	printf("strcpy------------\n");
	printf("str_c : %s",str_c);
	strcpy(str_c,str);
	printf("after---------\n");
	printf("str_c : %s",str_c);
*/
	return 0;
}

size_t strlen(const char *s){
	int count = 0;
 	if(s == NULL) return -1;
	for(int i = 0;;i++){
		if(*(s+i) == 0){
		break;
		}
		else{
		count++;
		}
	}
	return count;
}
char *strcpy(char *dest,const char *src){

	/*while(*src){
		*dest++ = *src++;
	}*/

	for(int i = 0; i < strlen(src);i++){
		dest[i] = src[i];
	}
	return dest;
}
int strcmp(const char *s1,const char *s2){
	int s1len = strlen(s1);

	for(int i = 0; i < s1len + 1;i++){
		int temp = *(s1 + i) - *(s2 + i);
		if(temp != 0 || s2[i] == 0)
			return temp;
	}
	if(s2 + s1len != NULL )
		return *(s2 + s1len);
	return 0;
}
