MODULES = udpsocket.o clientlink.o serverpacket.o serverlink.o clientpacket.o
C_OBJS = udpsocket.o clientpacket.o clientlink.o clientmain.o serverpacket.o
S_OBJS = udpsocket.o serverpacket.o serverlink.o servermain.o clientpacket.o
CXX = g++ -g
CFLAGS = -lpthread
LFLAGS = -lpthread

all: server client sockets_module.o

client : $(C_OBJS)
	$(CXX) $(LFLAGS) $(C_OBJS) -o client

server : $(S_OBJS)
	$(CXX) $(LFLAGS) $(S_OBJS) -o server

sockets_module.o: $(MODULES)
	ld -r -o sockets_module.o $(MODULES)

%.o: %.cxx %.hxx
	$(CXX) -c $(inputs) -o $(outputs)

clean:
	\rm *.o client server
