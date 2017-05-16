MODULES = GameWindow.o InteractScreen.o screens.o GameOverScreen.o StatusWindow.o StaticScreen.o ScreenBackground.o Fireworks.o AniExplode.o AniBullet.o TextScreen.o EndLevelScreen.o StartLevelScreen.o WaitScreen.o MenuTextBox.o TitleTextBox.o TankLoadWindow.o TutorialTextBox.o

S_OBJS = GameWindow.o InteractScreen.o screens.o StaticScreen.o StatusWindow.o GameOverScreen.o AniExplode.o ScreenBackground.o Fireworks.o AniBullet.o TextScreen.o EndLevelScreen.o StartLevelScreen.o WaitScreen.o MenuTextBox.o TitleTextBox.o TankLoadWindow.o TutorialTextBox.o 

LFLAGS =  -lcurses -lpanel 
CXX=g++

all: screen_module.o
screen_module.o: $(MODULES)
	ld -r -o screen_module.o $(MODULES)

%.o: %.cxx %.hxx
	$(CXX) -c $(inputs) -o $(outputs)

clean:
	rm -f *.o mainprog
