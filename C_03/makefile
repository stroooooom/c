CC := gcc
CFLAGS := -ggdb -Wno-return-type
OBJS := node.o

all : main.exe clean_o

main.exe: $(OBJS) main.o node.o
	$(CC) $(CFLAGS) -o main.exe $(OBJS) main.o

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

main.o: main.c node.h
	$(CC) $(CFLAGS) -c main.c

clean :
	$(RM) *.o *.exe

clean_o :
	$(RM) *.o