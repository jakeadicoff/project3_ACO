CC = g++ -O3
CFLAGS = -std=c++11 -Wall

ACO : main.o ac.o eac.o acs.o
	$(CC) -o $@ main.o acoo.o eas.o acs.o

main.o : main.cpp main.h
	$(CC) -c $(CFLAGS) main.cpp -o $@

ac.o : AC.cpp AC.h
	$(CC) -c $(CFLAGS) ACO.cpp -o $@

eas.o : EAS.cpp EAS.h
	$(CC) -c $(CFLAGS) eas.cpp -o $@

acs.o : ACS.cpp ACS.h
	$(CC) -c $(CFLAGS) ACS.cpp -o $@

clean:
	rm ACO
	rm *.o
