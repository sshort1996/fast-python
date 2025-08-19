#include <Python.h>

// Compute fibonacci recursively in C
static long fib(long n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

// Exposed to Python
static PyObject* py_fib(PyObject* self, PyObject* args) {
    long n;
    if (!PyArg_ParseTuple(args, "l", &n)) {
        return NULL;
    }
    long result = fib(n);
    return PyLong_FromLong(result);
}

// Method table
static PyMethodDef FibMethods[] = {
    {"fib", py_fib, METH_VARARGS, "Compute Fibonacci numbers"},
    {NULL, NULL, 0, NULL}
};

// Module definition
static struct PyModuleDef fibmodule = {
    PyModuleDef_HEAD_INIT,
    "fib",   // module name in Python
    NULL,    // documentation
    -1,      // per-interpreter state
    FibMethods
};

// Init function
PyMODINIT_FUNC PyInit_fib(void) {
    return PyModule_Create(&fibmodule);
}
