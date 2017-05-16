LFLAGS = -lpanel -lncurses -lpthread
CXX = g++ -g -std=c++11

all: 
	(cd netcode; make all)
	(cd screens; make all)
	(cd engine; make all)
	make player

player: player.o netcode/sockets_module.o screens/screen_module.o engine/engine_module.o
	$(CXX) player.o netcode/sockets_module.o screens/screen_module.o engine/engine_module.o -o player $(LFLAGS)

%.o: %.cxx
	$(CXX) -c $(inputs) -o $(outputs)

clean:
	(cd netcode; make clean)
	(cd screens; make clean)
	(cd engine; make clean)
	rm -f *.o player
