CFLAGS = -Wall -Wextra -pedantic -g

TARGETS = kmeans

all: $(TARGETS)

kmeans: kmeans.cpp kmeans.o
	g++ $(CFLAGS) -o kmeans kmeans.cpp

kmeans.o: kmeans.cpp
	g++ $(CFLAGS) -c kmeans.cpp

kfunctions.o: kfunctions.cpp kfunctions.h
	g++ $(CFLAGS) -c kfunctions.c

clean:
	rm -f *.o $(TARGETS)
