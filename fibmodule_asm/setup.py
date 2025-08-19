from setuptools import setup, Extension

ext_modules = [
    Extension("fibasm", ["fibmodule_asm.c"], extra_compile_args=["-O0"])
]

setup(
    name="fibasm",
    version="0.1.0",
    ext_modules=ext_modules,
)

