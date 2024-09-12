run: build
	./sudoku

build: main.c
	gcc main.c functions.c -o sudoku

clean:
	rm -f sudoku