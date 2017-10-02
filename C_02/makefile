CC := gcc
CFLAGS := -ggdb -Wno-return-local-addr
OBJS := matrix.o

main : main.exe clean_o

main.exe: $(OBJS) main.o matrix.o
	$(CC) $(CFLAGS) -o main.exe $(OBJS) main.o

matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

main.o: main.c matrix.h
	$(CC) $(CFLAGS) -c main.c

clean :
	$(RM) *.o *.exe

clean_o :
	$(RM) *.o