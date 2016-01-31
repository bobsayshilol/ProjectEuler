CC=g++
LD=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11
LDFLAGS=
SOURCES=main.cpp solution_1.cpp solution_2.cpp
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
