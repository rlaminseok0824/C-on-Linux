CROSS = 
CC=$(CROSS) gcc
EXE=test

C_SRC = $(wildcard *.c)
OBJS= $(C_SRC: .c=.o)
#OBJS = main.o sum.o
DEFINES=#-DDEBUG  //컴파일 시 범위 나누기 좋음
CFLAGS=-I./include $(DEFINES)#헤더파일 따로 보관 후 포함시키는 방법
LDFLAGS=-lpthread


all : $(EXE)
	echo completed!!

$(EXE) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)


#all : main.o sum.o #원래는 obh 파일 명령어까지 해야하지만 알아서 만들어줌
#	gcc -o test main.o sum.o

#main.o : main.c
#	gcc -c main.c
#sum.o : sum.c
#	gcc -c sum.c

clean :
	rm *.o
	rm test
	

