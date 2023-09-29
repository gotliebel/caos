#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_line(char* line, char* table[10][26], int number_line) {
  char * token = strtok(line, ";");
  int index = 0;
  int count_delim = 0;
  int size = strlen(line);
  for (int i = 0; i < size; i++) {
    if (line[i] == ';') {
      count_delim++;
    }
  }

  while (token != NULL) {
    table[number_line][index] = malloc(100);
    strcpy(table[number_line][index], token);
    printf("%s\n", token);
    token = strtok(NULL, ";");
    //printf("%s\n", token);
    index++;
  }
}

int main() {
  /*Py_Initialize();
  PyObject* table;*/
  /*if (!PyArg_ParseTuple(args, "O", &table)) {
      return NULL;
  }
  PyObject* base_list;
  base_list = PyList_New(1);
  int length = PyUnicode_GetLength(PyList_GetItem(table, 0));
  PyList_SetItem(base_list, 0, PyUnicode_Split(PyList_GetItem(table, 0), PyUnicode_FromString(";"), 1000));
  int count_spl = PyUnicode_Count(PyList_GetItem(table, 0), PyUnicode_FromString(";"), 0, length - 1);
  if (count_spl == PyList_Size(PyList_GetItem(base_list, 0)) - 1) {
    printf("chetko\n");
  }*/
  /*
  do {
    PyObject* my_module = PyImport_ImportModule("openpyxl");
    PyObject* my_function = PyObject_GetAttrString(my_module, "Workbook");
    PyObject* wb = PyObject_CallObject(my_function, NULL);
    PyObject* attr = PyObject_GetAttrString(wb, "active");
    PyObject* ws = PyObject_CallObject(attr, NULL);
    //ws = PyDict_New();
    PyObject_SetItem(ws, PyUnicode_FromString("A1"), PyLong_FromLong(42));
    PyObject_Print(ws, stdout, 0);
  } while (0);
  Py_Finalize();*/
  char* table[10][26];
  char* line = malloc(1000);
  int number_line = 0;
  while (scanf("%s", line) != EOF) {
    parse_line(line, table, number_line);
    number_line++;
  }
  for (int i = 0; i < number_line; i++) {
    for (int j = 0; j < 2; j++) {
      printf("%s ", table[i][j]);
    }
    printf("\n");
  }
  return 0;
}