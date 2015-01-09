OBJS=socket.o shm.o

SRCS=tcpclient.c tcpserver.c socket.c shm.c
SRCS1=tcpclient.c
SRCS2=tcpserver.c

LIBFULLNAME=libstatictcpex.a
LIBNAME=statictcpex
.SUFFIXES:.c.o
all:tcpclient tcpserver
tcpclient : $(OBJS) $(LIBFULLNAME)
	gcc -o $@ $(SRCS1) -L./ -lstatictcpex
tcpserver: $(OBJS) $(LIBFULLNAME)
	gcc -o $@ $(SRCS2) -L./ -lstatictcpex
$(LIBFULLNAME) : $(OBJS)
	$(AR) rc $@ socket.o shm.o
#socket.o : socket.c
#	gcc -c socket.c
#shm.o : shm.c
#	gcc -c shm.c
