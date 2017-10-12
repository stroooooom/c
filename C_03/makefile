CC := gcc
CFLAGS := -ggdb -Wno-return-type
OBJS := node.o

all : main clean_o

main: $(OBJS) main.o node.o
	$(CC) $(CFLAGS) -o main $(OBJS) main.o

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

main.o: main.c node.h
	$(CC) $(CFLAGS) -c main.c

clean :
	$(RM) *.o *.exe *.out

clean_o :
	$(RM) *.o