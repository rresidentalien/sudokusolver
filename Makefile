run: build
	./sudoku

build: sudoku.c
	gcc sudoku.c functions.c -o sudoku

clean:
	rm -f sudoku