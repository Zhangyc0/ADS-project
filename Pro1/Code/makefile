CPP = g++
OFLAG = -o
TARGET = test.exe 
OBJS = test.o BplusTree.o hash.o stem.o tyfile.o wzj.o

$(TARGET): $(OBJS)
	$(CPP) $(OFLAG) $(TARGET) $(OBJS)
test.o: test.cpp tyfile.o wzj.o
BplusTree.o: BplusTree.cpp tyfile.o
hash.o: hash.cpp 
stem.o: stem.cpp
tyfile.o: tyfile.cpp stem.o wzj.o
wzj.o: wzj.cpp BplusTree.o hash.o

.PHONY: clean
clean:
	-rm $(TARGET) $(OBJS)