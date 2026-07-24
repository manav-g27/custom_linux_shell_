CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = myshell

SRCS = main.cpp executor.cpp jobs.cpp parser.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o

install: $(TARGET)
	install -m 755 $(TARGET) /usr/local/bin/$(TARGET)

test: all
	bash test_shell.sh

.PHONY: all clean install test