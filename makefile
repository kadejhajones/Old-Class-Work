# 
#  Makefile 
# 

SOURCE =\
	hello.c\
	main.c

CFLAGS  = -g

.c.o:
	gcc $(CFLAGS) -c $*.c; 

hello: *.o
	gcc *.o -o $@; 
