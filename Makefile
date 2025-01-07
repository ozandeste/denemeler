# Derleyici
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -g  # Debug için -g ekledim

# Hedef kaynak
TARGET = build/main
SRC = Main.cpp src/DeadlockManager.cpp src/ProcessStackManager.cpp

# Derleme kuralları
all: ${TARGET}

${TARGET}: ${SRC}
	${CXX} ${CXXFLAGS} -o $@ $^

clean:
	rm -f ${TARGET}
