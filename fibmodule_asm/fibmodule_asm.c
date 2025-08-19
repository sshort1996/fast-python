#include <Python.h>

/*
   fibasm.fib(n) -> n-th Fibonacci number

   This version uses inline AArch64 assembly for the addition step:
   res = a + b  ==>  "add %0, %1, %2"
   On non-aarch64 platforms it falls back to plain C.
*/

static inline unsigned long add_ul(unsigned long a, unsigned long b) {
#if defined(__aarch64__)
    unsigned long res;
    __asm__ volatile (
        "add %0, %1, %2\n\t"
        : "=r"(res)
        : "r"(a), "r"(b)
        : 
    );
    volatile unsigned long sink = res; // prevent optimization
    return sink;
#else
    return a + b;
#endif
}

// Iterative Fibonacci using inline-asm add
__attribute__((noinline)) static unsigned long fib_asm_impl(unsigned long n) {
    volatile unsigned long a = 0, b = 1; // volatile forces actual memory operations
    for (unsigned long i = 0; i < n; ++i) {
        volatile unsigned long tmp = add_ul(a, b);
        a = b;
        b = tmp;
    }
    return b;
}

// Python wrapper: fib(n: int) -> int
static PyObject* py_fib_asm(PyObject* self, PyObject* args) {
    unsigned long n;
    if (!PyArg_ParseTuple(args, "k", &n)) {
        return NULL;
    }
    unsigned long result = fib_asm_impl(n);
    return PyLong_FromUnsignedLong((unsigned long)result);
}

static PyMethodDef FibAsmMethods[] = {
    {"fib", py_fib_asm, METH_VARARGS, "Compute Fibonacci using inline AArch64 asm for addition."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef fibasmmodule = {
    PyModuleDef_HEAD_INIT,
    "fibasm",
    "Fibonacci with inline AArch64 assembly.",
    -1,
    FibAsmMethods
};

PyMODINIT_FUNC PyInit_fibasm(void) {
    return PyModule_Create(&fibasmmodule);
}
