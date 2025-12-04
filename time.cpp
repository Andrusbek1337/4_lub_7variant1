#include "time.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <string>
#include <cctype>

// Метод для нормализации времени
void Time::normalize() {
    if (minutes >= 60) {
        hours += minutes / 60;
        minutes %= 60;
    }
    else if (minutes < 0) {
        hours -= (-minutes + 59) / 60;
        minutes = (minutes % 60 + 60) % 60;
    }

    if (hours >= 24) {
        hours %= 24;
    }
    else if (hours < 0) {
        hours = (hours % 24 + 24) % 24;
    }
}

// Конструктор по умолчанию
Time::Time() : hours(0), minutes(0) {}

// Конструктор с параметрами
Time::Time(short int h, short int m) : hours(h), minutes(m) {
    if (!isValidTime(h, m)) {
        throw std::invalid_argument("Некорректное время: часы должны быть от 0 до 23, минуты от 0 до 59");
    }
    normalize(); // Если минуты > 59
}

// Конструктор копирования
Time::Time(const Time& other) : hours(other.hours), minutes(other.minutes) {}

// Геттеры
short int Time::getHours() const { return hours; }
short int Time::getMinutes() const { return minutes; }

// Сеттеры
void Time::setHours(short int h) {
    if (h < 0 || h > 23) {
        throw std::invalid_argument("Часы должны быть от 0 до 23");
    }
    hours = h;
}

void Time::setMinutes(short int m) {
    if (m < 0 || m > 59) {
        throw std::invalid_argument("Минуты должны быть от 0 до 59");
    }
    minutes = m;
}

// Проверка корректности времени
bool Time::isValidTime(short int h, short int m) {
    return (h >= 0 && h <= 23) && (m >= 0 && m <= 59);
}

// Метод вычитания переменной типа Time
Time Time::subtract(const Time& other) const {
    int totalMinutes1 = hours * 60 + minutes;
    int totalMinutes2 = other.hours * 60 + other.minutes;
    int diffMinutes = totalMinutes1 - totalMinutes2;

    // Обработка перехода через сутки
    if (diffMinutes < 0) {
        diffMinutes += 24 * 60;
    }

    short int resultHours = diffMinutes / 60;
    short int resultMinutes = diffMinutes % 60;

    // Нормализация результата
    if (resultHours >= 24) {
        resultHours %= 24;
    }

    return Time(resultHours, resultMinutes);
}

// Унарные операции

// Добавляет минуту
Time& Time::operator++() {
    minutes++;
    normalize();
    return *this;
}

// Добавляет минуту
Time Time::operator++(int) {
    Time temp = *this;
    minutes++;
    normalize();
    return temp;
}

// Вычитает минуту
Time& Time::operator--() {
    minutes--;
    normalize();
    return *this;
}

// Вычитает минуту
Time Time::operator--(int) {
    Time temp = *this;
    minutes--;
    normalize();
    return temp;
}

// Неявное приведение к int (количество минут)
Time::operator int() const {
    return hours * 60 + minutes;
}

// Явное приведение к bool 
Time::operator bool() const {
    return (hours != 0 || minutes != 0);
}

// Оператор меньше
bool Time::operator<(const Time& other) const {
    return (hours * 60 + minutes) < (other.hours * 60 + other.minutes);
}

// Оператор больше
bool Time::operator>(const Time& other) const {
    return (hours * 60 + minutes) > (other.hours * 60 + other.minutes);
}

// Оператор равенства
bool Time::operator==(const Time& other) const {
    return (hours == other.hours) && (minutes == other.minutes);
}

// Оператор неравенства
bool Time::operator!=(const Time& other) const {
    return !(*this == other);
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const Time& time) {
    os << std::setw(2) << std::setfill('0') << time.hours << ":"
       << std::setw(2) << std::setfill('0') << time.minutes;
    return os;
}

// Проверкой на не числа
short int inputNumber(const std::string& prompt, short int min, short int max) {
    short int value;
    std::string input;

    while (true) {
        std::cout << prompt;
        std::cin >> input;

        // Проверяем, что ввод состоит только из цифр
        bool isNumber = true;
        for (char c : input) {
            if (!std::isdigit(c) && !(c == '-' && &c == &input[0])) {
                isNumber = false;
                break;
            }
        }

        if (!isNumber) {
            std::cout << "Вы ввели число, а не текст.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Преобразуем строку в число
        try {
            value = std::stoi(input);

            // Проверяем диапазон
            if (value >= min && value <= max) {
                break;
            }
            else {
                std::cout << "Число должно быть от " << min << " до " << max << ".\n";
            }
        }
        catch (const std::exception&) {
            std::cout << "Неверное число.\n";
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return value;
}

// Функция для ввода времени
Time inputTime(const std::string& prompt) {
    std::cout << prompt;

    short int h = inputNumber("Введите часы (0-23): ", 0, 23);
    short int m = inputNumber("Введите минуты (0-59): ", 0, 59);

    return Time(h, m);
}
