SRC = test.c align.c

test: $(SRC)
	gcc -o test $(SRC) -lcunit
