CFLAGS = -Wall -Wextra -pedantic -g

TARGETS = kmeans

all: $(TARGETS)

kmeans: kmeans.cpp kmeans.o
	gcc $(CFLAGS) -o kmeans kmeans.cpp

kmeans.o: kmeans.cpp
	gcc $(CFLAGS) -c kmeans.cpp

kfunctions.o: kfunctions.cpp kfunctions.h
	gcc $(CFLAGS) -c kfunctions.c

clean:
	rm -f *.o $(TARGETS)
