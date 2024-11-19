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

typedef std::multimap<int,int>	Info;
std::map< char, Info> TextInfo;

Проиндексировать входной текстовый файл, собирая информацию в указанную структуру данных
(сами строки не загружаются, запоминается только их позиция и служебная информация).
Строки вначале  сортируются по первому символу. То есть данные о строках, начинающихся с буквы ‘a’,
должны быть в одном внутреннем контейнере, с буквы ‘b’ в другом и так далее.
Внутренние контейнеры содержат связанную пару – длина строки и позиция ее начала в файле (смещение в байтах от начала).
Вывести на экран все строки входного файла, которые начинаются с заданной буквы и имеют заданную длину.
*/

#include "main.h"

int main(int argc, char *argv[]) {
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
    char inChar = argv[1][0];
    int length = atoi(argv[3]);
    Info outInfo = findInfo(ti, inChar, length);
    
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
        // Info tInfo;
        // tInfo.insert({++linesCount, current.length()});
        ti[current[0]].insert({++linesCount, current.length()});
    }
    return ti;
}

Info findInfo(TextInfo ti, char inChar, int length) {
    Info outInfo;
    for (auto inf : ti[inChar]) {
        if (inf.second() == length) { outInfo.insert(inf); }
    }
}