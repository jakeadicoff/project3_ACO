CC = g++ -O3
CFLAGS = -std=c++11 -Wall

ACO : main.o acoo.o
	$(CC) -o $@ main.o acoo.o

main.o : main.cpp main.h
	$(CC) -c $(CFLAGS) main.cpp -o $@

acoo.o : ACO.cpp ACO.h
	$(CC) -c $(CFLAGS) ACO.cpp -o $@

clean:
	rm ACO
	rm *.o
