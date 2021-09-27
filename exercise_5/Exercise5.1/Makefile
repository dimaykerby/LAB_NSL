CC = g++
CFLAGS = -Wall -O3 --std=c++11

main5.exe : main5.o random.o lib.h integranda.h
	$(CC) random.o main5.o -o main5.exe
main5.o : main5.cpp
	$(CC) -c main5.cpp -o main5.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o main5.exe
cleanall :
	rm ps1.csv ps2.csv
