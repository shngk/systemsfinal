CFLAGS = -Wall -Wextra -pedantic -g

TARGETS = kmeans

all: $(TARGETS)

kmeans: kmeans.o
	gcc $(CFLAGS) -o kmeans kmeans.o

kmeans.o: kmeans.c
	gcc $(CFLAGS) -c kmeans.c

clean:
	rm -f *.o $(TARGETS)
