CC=gcc
CFLAGS=-Wall -Wextra -std=c99

build:
	$(CC) $(CFLAGS) main.c functions.c commands.c doubly_linked_list.c -g -o tema1
	
clean:
	rm -f tema1

