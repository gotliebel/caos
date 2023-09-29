#include <Python.h>

static PyObject* addList_add(PyObject* self, PyObject* args){

  PyObject * listObj;

  if (! PyArg_ParseTuple( args, "O", &listObj))
    return NULL;

  long length = PyList_Size(listObj);

  long i, sum =0;
  for(i = 0; i < length; i++){
    PyObject* temp = PyList_GetItem(listObj, i);
  }

  return Py_BuildValue("i", sum);
}

static char addList_docs[] =
    "add( ): add all elements of the list\n";

static PyMethodDef module_methods[] = {
    {"add", (PyCFunction)addList_add, METH_VARARGS, addList_docs},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef initaddList =
    {
        PyModuleDef_HEAD_INIT,
        "addlist",
        "DOcu",
        -1,
        module_methods
    };

PyMODINIT_FUNC PyInit_addList(void)
{
  return PyModule_Create(&initaddList);
}