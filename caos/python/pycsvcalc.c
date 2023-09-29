#include <Python.h>
#include <stddef.h>
#include <stdio.h>

static PyObject* csvcalc(PyObject* self, PyObject* args){
  PyObject* table;
  if (!PyArg_ParseTuple(args, "O", &table)) {
    return NULL;
  }
  PyObject* base_list;
  base_list = PyList_New(1);
  int length = PyUnicode_GetLength(PyList_GetItem(table, 0));
  PyList_SetItem(base_list, 0, PyUnicode_Split(PyList_GetItem(table, 0), PyUnicode_FromString(";"), 1000));
  int count_spl = PyUnicode_Count(PyList_GetItem(table, 0), PyUnicode_FromString(";"), 0, length - 1);
  if (count_spl == PyList_Size(PyList_GetItem(base_list, 0)) - 1) {
    printf("chetko\n");
  }
  //printf("%d", count_spl);
  return base_list;
}

static char csvcalc_docs[] =
    "very important documentation\n";

static PyMethodDef module_methods[] = {
    {"csvcalc", (PyCFunction)csvcalc, METH_VARARGS, csvcalc_docs},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef initcsvcalc =
    {
        PyModuleDef_HEAD_INIT,
        "csvcalc",
        "DOcumentation",
        -1,
        module_methods
    };

PyMODINIT_FUNC PyInit_csvcalc(void)
{
  return PyModule_Create(&initcsvcalc);
}