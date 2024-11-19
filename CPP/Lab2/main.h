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
Info findInfo(TextInfo, char, int);

#endif //MAIN_H
