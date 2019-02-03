CC=g++ 

betyourhome: users.o main.o hierarchy.o state.o
	$(CC) -o betyourhome users.o main.o hierarchy.o state.o
users.o: users.cpp
	$(CC) -c users.cpp
main.o: main.cpp
	$(CC) -c main.cpp
	
hierarchy.o: hierarchy.cpp
	$(CC) -c hierarchy.cpp

state.o: state.cpp
	$(CC) -c state.cpp

clean:
	rm -f betyourthome users.o main.o hierarchy.o state.o

