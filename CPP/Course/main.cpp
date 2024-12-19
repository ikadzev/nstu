#include "Date.cpp"

int main() {
    try {
        Date date1(31, 12, 2023);
        Date date2 = date1 + 1;
        cout << "Date1: " << date1 << endl;
        cout << "Date2: " << date2 << endl;

        date1 += 365;
        cout << "Date1 after 365 days: " << date1 << endl;

        cout << "Comparison (date1 < date2): " << (date1 < date2) << endl;

        cout << "Date1 after increment: " << date1++ << endl;

        cout << "Date1 as string: " << string(date1) << endl;
    } catch (const exception &e) {
        cerr << e.what() << endl;
    }

    return 0;
}
