CFLAGS = -Wall -Wextra -pedantic -g

TARGETS = kmeans

all: $(TARGETS)

kmeans: kmeans.o
	gcc $(CFLAGS) -o kmeans kmeans.o

kmeans.o: kmeans.cpp
	gcc $(CFLAGS) -c kmeans.cpp

clean:
	rm -f *.o $(TARGETS)
