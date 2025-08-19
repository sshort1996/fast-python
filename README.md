Noodling about with JIT compiled, native C, and native C with inline assembly for computing fibonnaci numbers. Results below:

```
Dev/noodling/arb-C-py via 🐍 v3.10.11 
❯ python test.py

Pure Python: fib(40) = 102334155, time = 13.893268 sec

C extension: fib(40) = 102334155, time = 0.154505 sec
C asm extension: fib(40) = 102334155, time = 0.000001 sec

Numba JIT (first run, includes compile time): fib(1) = 1, time = 0.452582 sec
Numba JIT (second run, cached): fib(40) = 102334155, time = 0.300798 sec

Numba JIT iterative (first run, includes compile time): fib(1) = 1, time = 0.000002 sec
Numba JIT iterative (second run, cached): fib(40) = 102334155, time = 0.301474 sec
```
