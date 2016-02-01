CC=g++
LD=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11 -g
LDFLAGS=-g
SOURCES=main.cpp
SOURCES+=solution_1.cpp  solution_2.cpp  solution_3.cpp  solution_4.cpp  solution_5.cpp
SOURCES+=solution_6.cpp  solution_7.cpp  solution_8.cpp  solution_9.cpp  solution_10.cpp
SOURCES+=solution_11.cpp solution_12.cpp solution_13.cpp solution_14.cpp solution_15.cpp
SOURCES+=solution_16.cpp solution_17.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=solutions

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

# since common.h is common to everything, just stick it here
%.o: %.cpp common.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
