//
// Created by ikadzev on 11.11.24.
//

#ifndef MAIN_H
#define MAIN_H
#include "algorithm"
#include "iostream"
#include "fstream"
#include "vector"
#include "map"

typedef std::multimap<int,int>	Info;
typedef std::map<char, Info> TextInfo;
TextInfo readTextInfo(char*);
void printInfo(TextInfo& ti, const char* fn, const char ch, const int nm);
void printLine(const char* fn, const int ln);

#endif //MAIN_H
