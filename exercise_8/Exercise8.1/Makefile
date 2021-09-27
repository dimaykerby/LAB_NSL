CC = g++
CFLAGS = -Wall -O3 --std=c++11

main8.exe : main8.o random.o lib.h integranda.h
	$(CC) random.o main8.o -o main8.exe
main8.o : main8.cpp
	$(CC) -c main8.cpp -o main8.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o main8.exe
cleanall :
	rm data.csv Energies.csv Parameters.csv psi.csv
