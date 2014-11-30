CXX = g++
CXXFLAGS = -Wall -MMD -g -lX11 -L/opt/X11/lib/ -I/opt/X11/include/
EXEC = ss5k
OBJECTS = settings.o squarefactory.o levelsettings.o grid.o squares/square.o squares/basic.o squares/lateral.o squares/root.o squares/upright.o squares/unstable.o squares/psychedelic.o game.o patterns/pattern.o patterns/basic.o patterns/l1.o patterns/l2.o patterns/l3.o patterns/l4.o patterns/t1.o patterns/t2.o patterns/t3.o patterns/t4.o patterns/fourhorizontal.o patterns/fourvertical.o patterns/fivehorizontal.o patterns/fivevertical.o main.o display/game_display.o display/window.o scoreboard.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
