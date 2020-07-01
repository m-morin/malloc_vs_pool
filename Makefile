.phony: run
run: malloc pool
	@echo
	@echo "Running malloc 3 times"
	time ./malloc
	time ./malloc
	time ./malloc
	@echo
	@echo "Running poll 3 times"
	time ./pool
	time ./pool
	time ./pool

malloc: malloc.c
	gcc -Wall -O3 malloc.c -o malloc

pool: pool.c
	gcc -Wall -O3 pool.c -o pool
