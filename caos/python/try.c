#include <Python.h>


int main()
{
  // Если не используются wchar_t*, то по умолчанию подразумевается,
  // что все однобайтные строки - в кодировке UTF-8
  static const char TheText[] = "сейчас 23 59 не время спать";

  // Инициализация API Python
  Py_Initialize();

  // Создание Python-строк из Си-строк
  PyObject *py_text = PyUnicode_FromString(TheText);
  PyObject *py_space_symbol = PyUnicode_FromString(" ");

  // Создание пустого списка
  PyObject *py_result = PyList_New(0);
  // str.split(py_text, py_space_symbol, maxsplit=-1)
  PyObject *py_tokens = PyUnicode_Split(py_text, py_space_symbol, -1);
  PyObject *py_entry = NULL;
  PyObject *py_number = NULL;

  // Цикл по элементам списка. PyList_Size - его размер
  for (int i=0; i<PyList_Size(py_tokens); ++i) {
    // list.__getitem__(i) - этому методу соответствует оператор []
    py_entry = PyList_GetItem(py_tokens, i);
    // Попытка создать int из строки, base=10
    // В случае не успеха устанавливается ошибка ValueError
    py_number = PyLong_FromUnicodeObject(py_entry, 10);
    // Проверяем, не возникло ли исключение
    if (! PyErr_Occurred()) {
      // OK - преобразование int(py_entry) выполнено успешно
      PyList_Append(py_result, py_number);
    }
    else {
      // Возникло исключение, оставляем просто текст
      PyList_Append(py_result, py_entry);
      // Убираем флаг ошибки, так как мы её обработали.
      // Если этого не сделать, то это исключение попадет
      // в интерпретатор, как только он будет использован
      PyErr_Clear();
    }
  }
  // Вывод print(repr(py_result))
  // Если последний параметр Py_PRINT_RAW вместо 0,
  // то вместо repr() будет использована функция str() для
  // преобразования произвольного объекта к строковому виду
  PyObject_Print(py_result, stdout, 0);

  Py_Finalize();
}