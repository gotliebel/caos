#include <Python.h>
#include <stddef.h>
#include <stdio.h>

static PyObject* dot(PyObject* self, PyObject* args){
  size_t size = 0;
  PyObject *m1;
  PyObject *m2;
  PyObject *res;
  if (!PyArg_ParseTuple( args, "IOO", &size, &m1, &m2)) {
    return NULL;
  }
  res = PyList_New(size);
  for (size_t i = 0; i < size; i++) {
    PyObject* row = PyList_New(size);
    for (size_t j = 0; j < size; j++) {
      double i_j = 0;
      for (size_t k = 0; k < size; k++) {
        if (k < PyList_Size(m1) && i < PyList_Size(PyList_GetItem(m1, k)) && j < PyList_Size(m2) && k < PyList_Size(PyList_GetItem(m2, j))) {
          i_j += PyFloat_AsDouble(PyList_GetItem(PyList_GetItem(m1, i), k))
              * PyFloat_AsDouble(PyList_GetItem(PyList_GetItem(m2, k), j));
        } else {
          i_j += 0;
        }
      }
      PyList_SetItem(row, j, PyFloat_FromDouble(i_j));
    }
    PyList_SetItem(res, i, row);
  }
  return res;
}

static char dot_docs[] =
    "dot: multiply matrices\n";

static PyMethodDef module_methods[] = {
    {"dot", (PyCFunction)dot, METH_VARARGS, dot_docs},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef initmatrix =
    {
        PyModuleDef_HEAD_INIT,
        "matrix",
        "DOcumentation",
        -1,
        module_methods
    };

PyMODINIT_FUNC PyInit_matrix(void)
{
  return PyModule_Create(&initmatrix);
}