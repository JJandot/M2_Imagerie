CC = g++ -std=c++17
C_FFLAGS = -o
C_EFLAGS = -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

all: tp0 tp2

tp0: tp0_1 tp0_2 tp0_3 tp0_4

tp0_1:
	$(CC) $(C_FFLAGS) TP0/TP0_1 TP0/TP0_1.cpp $(C_EFLAGS) 
	
tp0_2:
	$(CC) $(C_FFLAGS) TP0/TP0_2 TP0/TP0_2.cpp $(C_EFLAGS) 

tp0_3:
	$(CC) $(C_FFLAGS) TP0/TP0_3 TP0/TP0_3.cpp $(C_EFLAGS)

tp0_4:
	$(CC) $(C_FFLAGS) TP0/TP0_4 TP0/TP0_4.cpp $(C_EFLAGS)
	
tp0_5:
	$(CC) $(C_FFLAGS) TP0/TP0_5 TP0/TP0_5.cpp $(C_EFLAGS)

tp2:
	$(CC) $(C_FFLAGS) TP2/TP2 TP2/TP2.cpp $(C_EFLAGS)
