CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = a5
OBJECTS = grid.o squares/square.o levels/level.o levels/level0.o patterns/pattern.o patterns/basic.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
