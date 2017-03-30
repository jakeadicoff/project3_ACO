CC = g++ -O3
CFLAGS = -std=c++11 -Wall

ACO : main.o ac.o eas.o acs.o
	$(CC) -o $@ main.o ac.o eas.o acs.o

main.o : main.cpp main.h
	$(CC) -c $(CFLAGS) main.cpp -o $@

ac.o : AC.cpp AC.h
	$(CC) -c $(CFLAGS) AC.cpp -o $@

eas.o : EAS.cpp EAS.h
	$(CC) -c $(CFLAGS) EAS.cpp -o $@

acs.o : ACS.cpp ACS.h
	$(CC) -c $(CFLAGS) ACS.cpp -o $@

clean:
	rm ACO
	rm *.o
