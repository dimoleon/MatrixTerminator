CC = gcc
CFLAGS = -O2 -Wall -Wextra -pedantic -std=c17

all: 
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c


