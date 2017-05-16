MODULES = background.o building.o car.o gameObj.o missle.o player.o quickSand.o\
	  sand.o sky.o bubbles.o cactus.o engine.o kelp.o pavement.o\
	  pothole.o rLines.o water.o whirlpool.o shark.o
E_OBJS = background.o building.o car.o gameObj.o missle.o player.o quickSand.o\
	  sand.o sky.o bubbles.o cactus.o engine.o kelp.o pavement.o\
	  pothole.o rLines.o water.o setup.o whirlpool.o shark.o
CXX = g++ -g -std=c++11 
CFLAGS = -lpthread
LFLAGS = -lpanel -lncurses

all: engine engine_module.o

engine : $(E_OBJS)
	$(CXX) $(E_OBJS) -o engine $(LFLAGS) 

engine_module.o: $(MODULES)
	ld -r -o engine_module.o $(MODULES)

%.o: %.cxx
	$(CXX) -c $(inputs) -o $(outputs)

clean:
	\rm *.o engine
