#include "time.h"
#include <iostream>
#include <iomanip>
#include <locale>

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        // 1. Тестирование конструкторов
        std::cout << "1. Тестирование конструкторов:\n";
        Time t1;
        std::cout << "Конструктор по умолчанию: " << t1 << "\n";

        Time t2 = inputTime("Введите время для конструктора с параметрами:\n");
        std::cout << "Конструктор с параметрами: " << t2 << "\n";

        Time t3(t2);
        std::cout << "Конструктор копирования: " << t3 << "\n\n";

        // 2. Тестирование геттеров и сеттеров
        std::cout << "2. Тестирование геттеров и сеттеров:\n";
        Time t4;

        short int hours = inputNumber("Введите часы для setHours (0-23): ", 0, 23);
        t4.setHours(hours);

        short int minutes = inputNumber("Введите минуты для setMinutes (0-59): ", 0, 59);
        t4.setMinutes(minutes);

        std::cout << "setHours(" << hours << "), setMinutes(" << minutes << "): " << t4 << "\n";
        std::cout << "getHours(): " << t4.getHours() << "\n";
        std::cout << "getMinutes(): " << t4.getMinutes() << "\n\n";

        // 3. Тестирование оператора вывода
        std::cout << "3. Тестирование оператора вывода:\n";
        Time t5(5, 7);
        std::cout << "Время: " << t5 << " (форматированный вывод)\n\n";

        // 4. Тестирование метода вычитания
        std::cout << "4. Тестирование метода вычитания:\n";
        Time t6 = inputTime("Введите первое время для вычитания:\n");
        Time t7 = inputTime("Введите второе время для вычитания:\n");
        Time result1 = t6.subtract(t7);
        std::cout << t6 << " - " << t7 << " = " << result1 << "\n\n";

        // 5. Тестирование унарных операций
        std::cout << "5. Тестирование унарных операций (++, --):\n";
        Time t8 = inputTime("Введите время для тестирования ++ и --:\n");
        std::cout << "Исходное время: " << t8 << "\n";

        std::cout << "Префиксный инкремент (++t): " << ++t8 << "\n";
        std::cout << "Постфиксный инкремент (t++): " << t8++ << "\n";
        std::cout << "После постфиксного инкремента: " << t8 << "\n";

        std::cout << "Префиксный декремент (--t): " << --t8 << "\n";
        std::cout << "Постфиксный декремент (t--): " << t8-- << "\n";
        std::cout << "После постфиксного декремента: " << t8 << "\n\n";

        // 6. Тестирование операций приведения
        std::cout << "6. Тестирование операций приведения типа:\n";
        Time t11 = inputTime("Введите время для тестирования приведений:\n");

        // Неявное приведение к int
        int minutes_total = t11;
        std::cout << "Неявное приведение к int: " << minutes_total << " минут\n";

        // Явное приведение к bool
        bool isNonZero = static_cast<bool>(t11);
        std::cout << "Явное приведение к bool: " << std::boolalpha << isNonZero << "\n\n";

        if (t11) {
            std::cout << "Время " << t11 << " не равно 00:00\n";
            std::cout << "Оно равно " << (int)t11 << " минутам\n";
        }
        else {
            std::cout << "Время равно 00:00\n";
        }
        std::cout << "\n";

        // 7. Тестирование бинарных операций
        std::cout << "7. Тестирование бинарных операций (<, >):\n";
        Time t12 = inputTime("Введите первое время для сравнения:\n");
        Time t13 = inputTime("Введите второе время для сравнения:\n");

        std::cout << "\nСравнение:\n";
        std::cout << "t1 = " << t12 << " (" << (int)t12 << " минут)\n";
        std::cout << "t2 = " << t13 << " (" << (int)t13 << " минут)\n\n";

        std::cout << "t1 < t2: " << std::boolalpha << (t12 < t13) << "\n";
        std::cout << "t1 > t2: " << std::boolalpha << (t12 > t13) << "\n";
        std::cout << "t1 == t2: " << std::boolalpha << (t12 == t13) << "\n";
        std::cout << "t1 != t2: " << std::boolalpha << (t12 != t13) << "\n\n";

        if (t12 < t13) {
            std::cout << t12 << " раньше, чем " << t13 << "\n";
        }
        else if (t12 > t13) {
            std::cout << t12 << " позже, чем " << t13 << "\n";
        }
        else {
            std::cout << t12 << " и " << t13 << " равны\n";
        }

    }
    catch (const std::exception& e) {
        std::cout << "Произошла ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
