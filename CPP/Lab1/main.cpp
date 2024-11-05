#include <iostream>
#include <stdio.h>

using namespace std;

string txtRm(const char* fileName) {
  string name = fileName;
  name.erase(name.rfind('.'));
  return name;
}

string binAdd(string inFile) {
  inFile += ".bin";
  return inFile;
}

int keyGen(string fileName) {
  int key = 0;
  const auto len = fileName.length();
  for (int i = 1; i <= len; i++) {
    key += fileName[i] * i;
  }
  return key % 256;
}

void txt2bin(FILE* inFile, FILE* outFile) {
  string line;
  for (char token = fgetc(inFile); token != EOF; token = fgetc(inFile)) {
    line += token;
    if (token == '\n') {
      auto l = (unsigned char) line.length();
      fwrite(&l, sizeof(unsigned char), 1, outFile);
      fwrite(line.c_str(), 1, line.length(), outFile);
      line.clear();
    }
  }
  fwrite(line.c_str(), 1, line.length(), outFile);
}

void bin2txt(FILE* inFile) {
  unsigned char token;
  while (fread(&token, sizeof(unsigned char), 1, inFile) != 0) {
    auto line = new unsigned char[token];
    fread(line, 1, token, inFile);
    line[token] = 0;
    cout << line;
    delete[] line;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Wrong arguments!" << endl;
    return 1;
  }

  FILE* ptr = fopen(argv[1], "rt");
  if (ptr == nullptr) {
    cout << "Error while opening!" << endl;
    return 2;
  }

  const string fileName = txtRm(argv[1]);
  const string binFile = binAdd(fileName);
  FILE* bin = fopen(binFile.c_str(), "wb+");
  const auto key = keyGen(fileName);
  txt2bin(ptr, bin);
  rewind(bin);
  fclose(ptr);
  bin2txt(bin);
  fclose(bin);
  return 0;
}
