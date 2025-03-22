#include <iostream>
#include "menu.h"
#include "record.h"
#include "termfix.h"
#include "dynarray.h"

#define KEY_ARROW_UP 65
#define KEY_ARROW_DOWN 66
#define KEY_ENTER 10
#define KEY_BACKSPACE 127
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57

int main() {
    // Список опций
    DynamicArray<std::string> options;
    options.push_back("Загрузка из файла");
    options.push_back("Сохранение результатов обработки в файлах");
    options.push_back("Добавление записи");
    options.push_back("Удаление записи");
    options.push_back("Вывод на экран дисплея данных и результатов обработки");
    options.push_back("Алфавитная сортировка по фамилии");
    options.push_back("Сортировка по названию марки автомобиля, а при совпадении марки — по фамилии");
    options.push_back("Числовая сортировка по объему бака автомобиля");
    options.push_back("Перечень марок автомобилей с указанием их числа (результат отсортирован по названию марки автомобиля в алфавитном порядке)");
    options.push_back("Поиск по фамилии владельца (результат отсортирован по маркам в алфавитном порядке)");
    options.push_back("Завершить");

    // Запуск меню
    std::string fileInput;
    std::string fileOutput;
    std::string surname;
    unsigned int sortType;
    bool isRunning = true;
    int key;
    Menu menu(options);
    DynamicArray<Record> records;
    menu.printMenu();

    disableBufferedInput();

    while (isRunning) {
        key = getchar();
        switch (key) {
            case KEY_ARROW_UP:
                menu.previousSelected();
                menu.printMenu();
                break;
            case KEY_ARROW_DOWN:
                menu.nextSelected();
                menu.printMenu();
                break;
            case KEY_ENTER:
                switch (menu.getSelected()) {
                    case 1:  // Загрузка из файла
                        restoreBufferedInput();
                        std::cout << "\033[1mВведите имя файла для загрузки: \033[0m";
                        std::cin >> fileInput;
                        std::cin.ignore();
                        menu.inputFromFile(records, fileInput);
                        disableBufferedInput();
                        break;
                    case 2:  // Сохранение результатов обработки в файлах
                        restoreBufferedInput();
                        std::cout << "\033[1mВведите имя файла для сохранения: \033[0m";
                        std::cin >> fileOutput;
                        std::cin.ignore();
                        menu.outputToFile(records, fileOutput);
                        disableBufferedInput();
                        break;
                    case 3:  // Добавление записи
                        restoreBufferedInput();
                        menu.addRecord(records);
                        std::cin.ignore();
                        disableBufferedInput();
                        break;
                    case 4:  // Удаление записи
                        menu.removeRecord(records);
                        break;
                    case 5:  // Вывод на экран дисплея данных и результатов обработки
                        menu.printTable(records);
                        break;
                    case 6:  // Алфавитная сортировка по фамилии
                        restoreBufferedInput();
                        std::cout << "\033[1m1. По возрастанию/2. По убыванию: \033[0m";
                        std::cin >> sortType;
                        std::cin.ignore();
                        if (sortType == 1) {
                            menu.customSort(records, &Menu::compareByOwnerName, true);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else if (sortType == 2) {
                            menu.customSort(records, &Menu::compareByOwnerName, false);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else {
                            std::cout << "\033[31mТакого варианта нет!\033[0m";
                        }
                        disableBufferedInput();
                        break;
                    case 7:  // Сортировка по названию марки автомобиля, а при совпадении марки — по фамилии
                        restoreBufferedInput();
                        std::cout << "\033[1m1. По возрастанию/2. По убыванию: \033[0m";
                        std::cin >> sortType;
                        std::cin.ignore();
                        if (sortType == 1) {
                            menu.customSort(records, &Menu::compareByCarBrandAndOwnerName, true);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else if (sortType == 2) {
                            menu.customSort(records, &Menu::compareByCarBrandAndOwnerName, false);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else {
                            std::cout << "\033[31mТакого варианта нет!\033[0m";
                        }
                        disableBufferedInput();
                        break;
                    case 8:  // Числовая сортировка по объему бака автомобиля
                        restoreBufferedInput();
                        std::cout << "\033[1m1. По возрастанию/2. По убыванию: \033[0m";
                        std::cin >> sortType;
                        std::cin.ignore();
                        if (sortType == 1) {
                            menu.customSort(records, &Menu::compareByTankCapacity, true);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else if (sortType == 2) {
                            menu.customSort(records, &Menu::compareByTankCapacity, false);
                            std::cout << "\033[32mДанные успешно отсортированы!\033[0m\n";
                        } else {
                            std::cout << "\033[31mТакого варианта нет!\033[0m";
                        }
                        disableBufferedInput();
                        break;
                    case 9:  // Перечень марок автомобилей с указанием их числа (результат отсортирован по названию марки автомобиля в алфавитном порядке)
                        menu.printListOfBrands(records);
                        break;
                    case 10:  // Поиск по фамилии владельца (результат отсортирован по маркам в алфавитном порядке)
                        restoreBufferedInput();
                        std::cout << "\033[1mВведите фамилию владельца автомобиля: \033[0m";
                        std::cin >> surname;
                        std::cin.ignore();
                        menu.findByOwnerName(records, surname);
                        disableBufferedInput();
                        break;
                    case 11:  // Завершить
                        isRunning = false;
                        break;
                }
                break;
            case KEY_BACKSPACE:
                menu.printMenu();
                break;
            case KEY_1:
            case KEY_2:
            case KEY_3:
            case KEY_4:
            case KEY_5:
            case KEY_6:
            case KEY_7:
            case KEY_8:
            case KEY_9:
                menu.setSelected(key - 48);
                menu.printMenu();
                break;
        }
    }

    return 0;
}
