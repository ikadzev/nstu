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

Вариант 10.

typedef std::multimap<int[длина],int[позиция]>	Info;
std::map< char, Info> TextInfo;

Проиндексировать входной текстовый файл, собирая информацию в указанную структуру данных
(сами строки не загружаются, запоминается только их позиция и служебная информация).
Строки вначале  сортируются по первому символу. То есть данные о строках, начинающихся с буквы ‘a’,
должны быть в одном внутреннем контейнере, с буквы ‘b’ в другом и так далее.
Внутренние контейнеры содержат связанную пару – длина строки и позиция ее начала в файле (смещение в байтах от начала).
Вывести на экран все строки входного файла, которые начинаются с заданной буквы и имеют заданную длину.
*/

#include "main.h"

int main(const int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Usage: ./main <filename> <char> <length>\n" << std::endl;
        return 1;
    }
    TextInfo ti;
    try {
        ti = readTextInfo(argv[1]);
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return 2;
    }
    const char inChar = argv[2][0];
    const int length = atoi(argv[3]);
    printInfo(ti, argv[1], inChar, length);
    
}

TextInfo readTextInfo(char* filename) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        throw std::runtime_error("File cannot be opened: " + std::string(filename));
    }
    int linesCount = 0;
    TextInfo ti;
    std::string current;
    while (std::getline(f, current)) {
        ti[current[0]].insert({static_cast<int>(current.length()), ++linesCount});
    }
    return ti;
}

void printInfo(TextInfo& ti, const char* fn, const char ch, const int nm) {
    Info in_info = ti[ch];
    const auto rg = in_info.equal_range(nm);
    for (auto it = rg.first; it != rg.second; ++it) {
        const int li = it->second;
        printLine(fn, li);
    }
}

void printLine(const char* fn, const int ln) {
    std::ifstream fo(fn);
    std::string buff;
    for (int cnt = 0; cnt < ln - 1; cnt++) {
        std::getline(fo, buff);
    }
    buff.clear();
    std::getline(fo, buff);
    std::cout << ln << "::" << buff << std::endl;
}