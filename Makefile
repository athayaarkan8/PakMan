CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
TARGET = pakman

SRCS = main.cpp \
       game/stack.cpp \
       game/rewind.cpp \
       player/player.cpp \
       ghost/ghost.cpp \
       ghost/bfs.cpp \
       maze/graph.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean
