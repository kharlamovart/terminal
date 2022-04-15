all:
	gcc main.c -o terminal -fsanitize=address
