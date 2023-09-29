#include <Python.h>
#include <stddef.h>
#include <stdio.h>

static PyObject* factor_out(PyObject* self, PyObject* args){
  long number = 0;
  if (!PyArg_ParseTuple( args, "l", &number)) {
    return NULL;
  }
  if (number < 2) {
    return NULL;
  }
  PyObject* list;
  list = PyList_New(0);
  for (long i = 2; i <= number; i++) {
    while (number % i == 0) {
      PyList_Append(list, PyLong_FromSize_t(i));
      number /= i;
    }
  }
  if (PyList_Size(list) == 1) {
    return PyUnicode_FromString("Prime!");
  }
  return list;
}

static char factor_docs[] =
    "factor_out: primes\n";

static PyMethodDef module_methods[] = {
    {"factor_out", (PyCFunction)factor_out, METH_VARARGS, factor_docs},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef initprimes =
    {
        PyModuleDef_HEAD_INIT,
        "primes",
        "DOcumentation",
        -1,
        module_methods
    };

PyMODINIT_FUNC PyInit_primes(void)
{
  return PyModule_Create(&initprimes);
}