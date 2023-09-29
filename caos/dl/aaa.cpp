#include <iostream>
#include <string>
#include <regex>


int main() {
  //std::string class_path = std::getenv("CLASSPATH");

  std::string fullyQualifiedName = "some::package::ClassInPackage";
  std::regex from("::");
  std::string tmp = std::regex_replace(fullyQualifiedName, from, "/" );
  std::string lib = "$CLASSPATH";
  lib += "/" + fullyQualifiedName + ".so";
  std::string className = fullyQualifiedName;
  std::string name = "_ZN";
  for (int i = 0; i < className.size(); ++i) {
    char c = className[i];
    int name_len = 0;
    if (c != ':') {
      while (i < className.size() && className[i] != ':') {
        ++name_len, ++i;
      }
      name += std::to_string(name_len);
      name += className.substr(i - name_len, name_len);
    }
  }
  name += "C1Ev";
  std::cout <<tmp << "\n" << lib << "\n" << name;
}