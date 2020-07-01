Is a simple pool allocator faster than malloc?

Yes.

```
$ make
gcc -Wall -O3 malloc.c -o malloc
gcc -Wall -O3 pool.c -o pool

Running malloc 3 times
time ./malloc
28571427238093
0.50user 0.23system 0:00.74elapsed 98%CPU (0avgtext+0avgdata 313088maxresident)k
0inputs+0outputs (0major+78453minor)pagefaults 0swaps
time ./malloc
28571427238093
0.53user 0.17system 0:00.70elapsed 99%CPU (0avgtext+0avgdata 313084maxresident)k
0inputs+0outputs (0major+78451minor)pagefaults 0swaps
time ./malloc
28571427238093
0.40user 0.29system 0:00.70elapsed 99%CPU (0avgtext+0avgdata 313088maxresident)k
0inputs+0outputs (0major+78452minor)pagefaults 0swaps

Running poll 3 times
time ./pool
28571427238093
0.15user 0.18system 0:00.34elapsed 99%CPU (0avgtext+0avgdata 234940maxresident)k
0inputs+0outputs (0major+58884minor)pagefaults 0swaps
time ./pool
28571427238093
0.14user 0.20system 0:00.34elapsed 98%CPU (0avgtext+0avgdata 234940maxresident)k
0inputs+0outputs (0major+58883minor)pagefaults 0swaps
time ./pool
28571427238093
0.18user 0.15system 0:00.34elapsed 99%CPU (0avgtext+0avgdata 234940maxresident)k
0inputs+0outputs (0major+58882minor)pagefaults 0swaps
```
