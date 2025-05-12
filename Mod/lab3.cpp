#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

string filepath = "C:\\C++\\Furioso.txt";

char input_str[] = "Поставьте 10 баллов, пожалуйста";
bool isWriting = false;
const int input_str_len = sizeof(input_str) - 1;

class ReaderPr {
public:
    int priority;
    vector<char> buffer;
    int position;
    int read_count;

    ReaderPr(int priority) : priority(priority), position(0), read_count(0) {}

    bool read(const string& filename) {
        if (isWriting) return false;

        ifstream file(filename, ios::in | ios::binary);
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла для чтения: " << filename << endl;
            return false;
        }

        file.seekg(position);
        char ch;
        file.get(ch);

        if (file.eof()) {
            file.close();
            return false;
        }

        buffer.push_back(ch);
        position++;
        read_count++;

        file.close();
        return true;
    }
};

class WriterPr {
public:
    int priority;
    int position;
    int write_count;

    WriterPr() : priority(1), position(0), write_count(0) {}

    bool write(const string& filename) {
        isWriting = true;

        ofstream file(filename, ios::app | ios::binary);
        if (!file.is_open()) {
            cerr << "Ошибка открытия файла для записи: " << filename << endl;
            isWriting = false;
            return false;
        }

        if (position < input_str_len) {
            file.put(input_str[position]);
            write_count++;
            position++;
        }

        file.close();
        isWriting = false;
        return true;
    }
};

int choose_process() {
    int x = rand() % 16; // from 0 to 15
    if (x < 1) return 3;    // 0
    if (x < 3) return 2;    // 1-2
    if (x < 6) return 1;    // 3-5
    return -1;              // 6-15
}

void print_reader_info(const string& name, const ReaderPr& reader) {
    cout << "\n" << name << " записал: " << reader.read_count << " символов\n";
    for (char c : reader.buffer) cout << c;
    cout << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(0)));

    WriterPr writer;
    ReaderPr reader1(2);
    ReaderPr reader2(3);
    ReaderPr reader3(4);

    int num_iterations = 100;

    for (int i = 0; i < num_iterations; ++i) {
        int chosen = choose_process();

        switch (chosen) {
        case -1: // Writer
            cout << "Писатель\n";
            writer.write(filepath);
            break;

        case 1: // Reader 1
            cout << "Первый чтец\n";
            reader1.read(filepath);
            break;

        case 2: // Reader 1 + Reader 2
            cout << "Первый чтец\n";
            reader1.read(filepath);
            cout << "Второй чтец\n";
            reader2.read(filepath);
            break;

        case 3: // Reader 1 + Reader 2 + Reader 3
            cout << "Первый чтец\n";
            reader1.read(filepath);
            cout << "Второй чтец\n";
            reader2.read(filepath);
            cout << "Третий чтец\n";
            reader3.read(filepath);
            break;
        }
    }

    cout << "\nИтог:\n";
    cout << "Писатель получал управление " << writer.write_count << " раз\n";
    cout << "Первый чтец получал управление " << reader1.read_count << " раз\n";
    cout << "Второй чтец получал управление " << reader2.read_count << " раз\n";
    cout << "Третий чтец получал управление " << reader3.read_count << " раз\n";

    print_reader_info("Первый чтец", reader1);
    print_reader_info("Второй чтец", reader2);
    print_reader_info("Третий чтец", reader3);

    ofstream clear_file(filepath, ios::trunc);
    if (clear_file.is_open()) {
        cout << "\nФайл очищен\n";
        clear_file.close();
    } else {
        cerr << "Ошибка при очистке файла\n";
    }

    return 0;
}
