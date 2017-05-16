CC=g++
CFLAGS=-c
LDFLAGS=-std=c++11
TRAILFLAGS=-lpanel -lncurses
SOURCES=background.cpp bubbles.cpp building.cpp cactus.cpp pavement.cpp\
	car.cpp engine.cpp gameObj.cpp kelp.cpp player.cpp pothole.cpp quickSand.cpp\
	rLines.cpp sand.cpp setup.cpp sky.cpp water.cpp missle.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=engine

all: $(SOURCES) $(EXECUTABLE) $(TRAILFLAGS)
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(TRAILFLAGS)

.cpp.o:
	$(CC) $(LDFLAGS) $(CFLAGS) $< -o $@ $(TRAILFLAGS)

clean:
	rm -rf *.o

