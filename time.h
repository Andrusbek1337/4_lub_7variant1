#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <stdexcept>

class Time {
private:
    short int hours;
    short int minutes;

    // Метод для нормализации времени
    void normalize();

public:
    // Конструктор по умолчанию
    Time();

    // Конструктор с параметрами
    Time(short int h, short int m);

    // Конструктор копирования
    Time(const Time& other);

    // Геттеры
    short int getHours() const;
    short int getMinutes() const;

    // Сеттеры
    void setHours(short int h);
    void setMinutes(short int m);

    // Проверка корректности времени
    static bool isValidTime(short int h, short int m);

    // Метод вычитания переменной типа Time
    Time subtract(const Time& other) const;

    // Унарные операции
    Time& operator++();        
    Time operator++(int);     
    Time& operator--();      
    Time operator--(int);      

    // Операции приведения
    operator int() const;              // Неявное приведение к int
    explicit operator bool() const;    // Явное приведение к bool

    // Бинарные операции
    bool operator<(const Time& other) const;
    bool operator>(const Time& other) const;
    bool operator==(const Time& other) const;
    bool operator!=(const Time& other) const;

    // Дружественные функции
    friend std::ostream& operator<<(std::ostream& os, const Time& time);
};


short int inputNumber(const std::string& prompt, short int min, short int max);
Time inputTime(const std::string& prompt);

#endif // TIME_H
