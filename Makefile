CC       = g++
CFLAGS  = -g -Wall -std=c++11
TARGET  = P4
OBJS    = main.o Parser.o scanner.o BuildTree.o testTree.o semantics.o Generation.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

scanner.o: Parser.cpp Parser.h
	$(CC) $(CFLAGS) -c scanner.cpp

Parser.o: scanner.cpp scanner.h
	$(CC) $(CFLAGS) -c Parser.cpp

BuildTree.o: BuildTree.cpp BuildTree.h
	$(CC) $(CFLAGS) -c BuildTree.cpp

testTree.o: testTree.cpp testTree.h
	$(CC) $(CFLAGS) -c testTree.cpp

semantics.o: semantics.cpp semantics.h
	$(CC) $(CFLAGS) -c semantics.cpp

Generation.o: Generation.cpp Generation.h
	$(CC) $(CFLAGS) -c Generation.cpp

clean:
	/bin/rm -f *.o $(TARGET)
