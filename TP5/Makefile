CC = g++ -std=c++17
C_FFLAGS = -o
C_EFLAGS = -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

all: clean main

main:
	$(CC) $(C_FFLAGS) main main.cpp $(C_EFLAGS)
	
clean:
	rm main
