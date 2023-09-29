#include <Python.h>



int main(int argc, char *argv[])
{
  //Py_SetProgramName(argv[0]);  /* optional but recommended */
  Py_Initialize();
  PyRun_SimpleString("value = 0\n"
                     "value = input()\n"
                     "print(value)\n");
  Py_Finalize();
  return 0;
}