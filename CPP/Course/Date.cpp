#include <iostream>
#include <stdexcept>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

    bool isValidDate(int d, int m, int y) {
        if (y < 0 || m < 1 || m > 12 || d < 1) return false;
        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) daysInMonth[1] = 29; // Leap year
        return d <= daysInMonth[m - 1];
    }

public:
    // Конструкторы
    Date() : day(1), month(1), year(2000) {}
    Date(int d, int m, int y) {
        if (!isValidDate(d, m, y)) throw invalid_argument("Invalid date");
        day = d;
        month = m;
        year = y;
    }
    Date(const Date &other) : day(other.day), month(other.month), year(other.year) {}

    // Деструктор
    ~Date() {}

    // Оператор присваивания
    Date &operator=(const Date &other) {
        if (this != &other) {
            day = other.day;
            month = other.month;
            year = other.year;
        }
        return *this;
    }

    // Бинарные арифметические операторы
    Date operator+(int days) const {
        Date result(*this);
        while (days > 0) {
            int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if ((result.year % 4 == 0 && result.year % 100 != 0) || (result.year % 400 == 0)) {
                daysInMonth[1] = 29; // Leap year
            }
            int remainingDays = daysInMonth[result.month - 1] - result.day;
            if (days <= remainingDays) {
                result.day += days;
                break;
            } else {
                days -= (remainingDays + 1);
                result.day = 1;
                result.month++;
                if (result.month > 12) {
                    result.month = 1;
                    result.year++;
                }
            }
        }
        return result;
    }

    // Арифметика с накоплением
    Date &operator+=(int days) {
        *this = *this + days;
        return *this;
    }

    // Унарные операторы
    Date &operator++() { // Префиксный
        *this += 1;
        return *this;
    }

    Date operator++(int) { // Постфиксный
        Date temp(*this);
        ++(*this);
        return temp;
    }

    // Логические операторы
    bool operator<(const Date &other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator==(const Date &other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    bool operator!=(const Date &other) const {
        return !(*this == other);
    }

    // Функция вывода на экран
    friend ostream &operator<<(ostream &os, const Date &date) {
        os << (date.day < 10 ? "0" : "") << date.day << "/"
           << (date.month < 10 ? "0" : "") << date.month << "/" << date.year;
        return os;
    }

    // Оператор преобразования типа
    operator string() const {
        return (day < 10 ? "0" : "") + to_string(day) + "/" +
               (month < 10 ? "0" : "") + to_string(month) + "/" + to_string(year);
    }
};
