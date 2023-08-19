all: run clean

build:
	g++ main.cpp -l "ws2_32" -o main.o

run: 
ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
	g++ main.cpp -l "ws2_32" -o main.o
else
	g++ main.cpp -o main.o
endif
	./main.o

clean:
	rm main.o