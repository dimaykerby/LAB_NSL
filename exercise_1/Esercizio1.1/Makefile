CC = g++
CFLAGS = -Wall -O3 --std=c++11

make: main1.1.1.exe main1.1.2.exe main1.1.3.exe
main1.1.1.exe : main1.1.1.o random.o lib.h
	$(CC) random.o main1.1.1.o -o main1.1.1.exe
main1.1.1.o : main1.1.1.cpp lib.h
	$(CC) -c main1.1.1.cpp -o main1.1.1.o $(CFLAGS)
main1.1.2.exe : main1.1.2.o random.o lib.h
	$(CC) random.o main1.1.2.o -o main1.1.2.exe
main1.1.2.o : main1.1.2.cpp lib.h
	$(CC) -c main1.1.2.cpp -o main1.1.2.o $(CFLAGS)
main1.1.3.exe : main1.1.3.o random.o lib.h
	$(CC) random.o main1.1.3.o -o main1.1.3.exe
main1.1.3.o : main1.1.3.cpp lib.h
	$(CC) -c main1.1.3.cpp -o main1.1.3.o $(CFLAGS)
random.o : random.cpp random.h 
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o main1.1.1.exe main1.1.2.exe main1.1.3.exe

cleanall :
	rm data.csv data_r_square.csv data_chi.csv
