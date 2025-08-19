from setuptools import setup, Extension

setup(
    name="fib",
    ext_modules=[Extension("fib", ["fibmodule.c"])],
)
