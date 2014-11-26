CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = a5
OBJECTS = settings.o squarefactory.o levelsettings.o grid.o squares/square.o squares/basic.o game.o patterns/pattern.o patterns/basic.o main.o display/game_display.o display/window.o scoreboard.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
