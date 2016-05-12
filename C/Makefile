CC=g++
LD=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11 -g -O3 -flto
LDFLAGS=-g -O3 -flto
SOURCES=main.cpp
SOURCES+=solution_1.cpp  solution_2.cpp  solution_3.cpp  solution_4.cpp  solution_5.cpp
SOURCES+=solution_6.cpp  solution_7.cpp  solution_8.cpp  solution_9.cpp  solution_10.cpp
SOURCES+=solution_11.cpp solution_12.cpp solution_13.cpp solution_14.cpp solution_15.cpp
SOURCES+=solution_16.cpp solution_17.cpp solution_18.cpp solution_19.cpp solution_20.cpp
SOURCES+=solution_21.cpp solution_22.cpp solution_23.cpp solution_24.cpp solution_25.cpp
SOURCES+=solution_26.cpp solution_28.cpp
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
