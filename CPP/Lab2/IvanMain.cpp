/*
Цель: освоить стандартную библиотеку шаблонов (STL).
Общие требования:
    • Исходные данные из входного файла загружается в контейнер целиком.
Вся обработка и фильтрация должна выполняться в контейнере, а не на этапе
загрузки данных. • Для обращения к элементам заданного контейнера обязательно
использовать соответствующие итераторы. • При выполнении задания нужно
максимально задействовать алгоритмы STL (сортировка, поиск, обход контейнера и
т.д.). • Обработка ошибок должна быть реализована с помощью выбрасывания
исключений –объектов классов, унаследованных от std::exception (допускается
использовать std::runtime_error). • Алгоритм работы должен быть эффективен.
Работу программы проверить на файлах очень большого размера.

 typedef std::vector<std::string >	Strings;
std::map< char, Strings > Text;

Считать все строки заданного входного файла в указанную структуру данных,
сортируя строки при загрузке по первому символу. То есть все строки,
начинающиеся с буквы ‘a’, должны быть в одном векторе, с буквы ‘b’ в другом и
так далее. Векторы строк хранятся в контейнере map.

Вывести на экран (в файл) содержимое вектора с наибольшим количеством строк
*/

// the next is 6
#include "algorithm"
#include "fstream"
#include "iostream"
#include "map"
#include "vector"

typedef std::vector<std::string> Strings;
typedef std::map<char, Strings> Text;
Text read_from_file(const char *file_name);
Strings findLargestVector(const Text& text);
void print_Strings(Strings strings);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "incorrect number of args";
    return 42;
  }
  Text text;
  try {
    text = read_from_file(argv[1]);
  } catch (char *error) {
    std::cout << error;
    return 52;
  }

  Strings strings = findLargestVector(text);

  print_Strings(strings);

  return 0;
}

Text read_from_file(const char *file_name) {
  std::ifstream file(file_name);
  if (!file.is_open()) {
    throw std::runtime_error("can`t open file to read:"+std::string (file_name));
  }
  Text text;
  std::string str_read;
  while (std::getline(file, str_read)) {
    text[str_read[0]].push_back(str_read);
  }
  if (text.empty()){
    throw std::runtime_error("file is empty");
  }

  for (std::pair<const char, Strings>& lines : text) {
    std::sort(lines.second.begin(), lines.second.end());
  }
  return text;
}

Strings findLargestVector(const Text& text) {

  std::_Rb_tree_const_iterator<std::pair<const char, Strings>> maxElement =
      std::max_element(text.begin(), text.end(),
          [](const std::pair<const char, Strings> &c,
             const std::pair<const char, Strings> &b) { return c.second.size() < b.second.size(); });

  return maxElement->second;
}

void print_Strings(Strings string){
  for (const std::string &str : string) {
    std::cout << str<<std::endl;
  }
}