CC = g++
CFLAGS = -Wall -O3 --std=c++11

main1.2.exe : main1.2.o random.o lib.h
	$(CC) random.o main1.2.o -o main1.2.exe
main1.2.o : main1.2.cpp lib.h
	$(CC) -c main1.2.cpp -o main1.2.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o main1.2.exe
cleanall:
	rm dices.csv