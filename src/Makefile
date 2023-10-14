all: run clean

build:
	g++ main.cpp -l "ws2_32" -o main.o

run: 
ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
	g++ main.cpp -g -l "ws2_32" -o main.o
else
	g++ main.cpp -g -o main.o
endif
	./main.o

test:
	g++ main.cpp -g -l "ws2_32" -o main.o

clean:
	rm main.o