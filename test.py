import time
import fibmodule.fib as fib
import fibmodule_asm.fibasm as fibasm
from numba import jit

# Pure Python Fibonacci
def py_fib(n):
    if n < 2:
        return n
    return py_fib(n - 1) + py_fib(n - 2)

# Numba JIT Fibonacci
@jit(nopython=True)
def nb_fib(n):
    if n < 2:
        return n
    return nb_fib(n - 1) + nb_fib(n - 2)

@jit(nopython=True)
def nb_fib_iter(n):
    a, b = 0, 1
    for _ in range(n):
        a, b = b, a + b
    return a

def benchmark(func, n, label):
    t0 = time.time()
    result = func(n)
    elapsed = time.time() - t0
    print(f"{label}: fib({n}) = {result}, time = {elapsed:.6f} sec")

if __name__ == "__main__":
    n = 40

    benchmark(py_fib, n, "Pure Python")
    benchmark(fib.fib, n, "C extension")
    benchmark(fibasm.fib, n, "C asm extension")
    benchmark(nb_fib, 1, "Numba JIT (first run, includes compile time)")
    benchmark(nb_fib, n, "Numba JIT (second run, cached)")
    benchmark(nb_fib, 1, "Numba JIT iterative (first run, includes compile time)")
    benchmark(nb_fib, n, "Numba JIT iterative (second run, cached)")
