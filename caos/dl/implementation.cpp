#include "interfaces.h"
#include <dlfcn.h>
#include <errno.h>
#include <regex>

struct ClassImpl {
  void* ptr = nullptr;
};

AbstractClass::AbstractClass() {
  pImpl = new ClassImpl;
}

AbstractClass::~AbstractClass() {
  delete pImpl;
}

void* AbstractClass::newInstanceWithSize(size_t sizeofClass) {
  typedef void (* c_t)(void*);
  void* ptr = malloc(sizeofClass);
  auto c = (c_t) pImpl->ptr;
  c(ptr);
  return ptr;
}

struct ClassLoaderImpl {
  ClassLoaderError error;
};

ClassLoader::ClassLoader() {
  pImpl = new ClassLoaderImpl();
  pImpl->error = ClassLoaderError::NoError;
}

ClassLoader::~ClassLoader() {
  delete pImpl;
}

ClassLoaderError ClassLoader::lastError() const {
  return pImpl->error;
}

AbstractClass* ClassLoader::loadClass(const std::string& fullyQualifiedName) {
  std::string class_path = std::getenv("CLASSPATH");
  std::regex from("::");
  std::string tmp = std::regex_replace(fullyQualifiedName, from, "/");
  std::string lib = class_path + "/" + tmp + ".so";
  void* handle;
  handle = dlopen(lib.data(), RTLD_NOW | RTLD_GLOBAL);
  if (handle == nullptr) {
    if (errno == ENOENT) {
      pImpl->error = ClassLoaderError::FileNotFound;
      return nullptr;
    } else {
      pImpl->error = ClassLoaderError::LibraryLoadError;
      return nullptr;
    }
  }
  std::string class_file = "_ZN";
  size_t pos = 0;
  for (size_t i = fullyQualifiedName.find("::", pos); i != std::string::npos; i = fullyQualifiedName.find("::", pos)) {
    class_file += std::to_string(i - pos) + fullyQualifiedName.substr(pos, i - pos);
    pos = i + 2;
  }
  class_file += std::to_string(fullyQualifiedName.size() - pos) + fullyQualifiedName.substr(pos, fullyQualifiedName.size() - pos) + "C1Ev";
  void* constructor = dlsym(handle, class_file.data());
  if (constructor == nullptr) {
    pImpl->error = ClassLoaderError::NoClassInLibrary;
    return nullptr;
  }
  auto* a_class = new AbstractClass();
  a_class->pImpl->ptr = constructor;
  return a_class;
}