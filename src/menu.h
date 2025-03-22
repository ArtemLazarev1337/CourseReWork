#pragma once

#include "dynarray.h"
#include <fstream>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include "record.h"
#include <map>

#define KEY_ARROW_UP 65
#define KEY_ARROW_DOWN 66
#define KEY_ENTER 10
#define KEY_BACKSPACE 127

class Menu {
    private:
        DynamicArray<std::string> options;
        size_t selected;
    public:
        Menu(const DynamicArray<std::string>& options) {
            this->options = options;
            selected = 1;
        }

        void printMenu() {
            std::system("clear");
            std::cout << "\033[0;1m↑/↓ — перемещение ↵ — выполнить ⌫ — очистить\033[0m\n\n";
            for (size_t opt = 1; opt <= options.getSize(); ++opt) {
                if (opt == selected) std::cout << "\033[30;47m";
                std::cout << opt << ". " << options[opt - 1] << std::endl << "\033[0m";
            }
        }

        void nextSelected() {
            selected = selected < options.getSize() ? ++selected : selected -= (options.getSize() - 1);
        }

        void previousSelected() {
            selected = selected > 1 ? --selected : selected = options.getSize();
        }

        size_t getSelected() {
            return selected;
        }

        void setSelected(size_t s) {
            if (s >= 1 && s <= options.getSize()) selected = s;
        }

        std::string centerText(const std::string& text, int width) {
            int padding = width - text.size();
            if (padding <= 0) return text;
            int leftPadding = padding / 2;
            int rightPadding = padding - leftPadding;
            return std::string(leftPadding, ' ') + text + std::string(rightPadding, ' ');
        }

        void inputFromFile(DynamicArray<Record>& records, const std::string& fileName) {
            std::ifstream fin(fileName);

            if (!fin.is_open()) {
                std::cerr << "\033[31mНе удалось открыть файл: \033[0;33m" << fileName << "\033[0m\n";
                return;
            }

            records.clear();

            Record record;
            while (fin >> record.carBrand >> record.fuelBrand >> record.enginePower >>
                         record.tankCapacity) {
                std::string surname, initials;
                fin >> surname >> initials;
                record.ownerName = surname + " " + initials;

                fin >> record.carNumber;
                records.push_back(record);
            }

            fin.close();

            std::cout << "\033[32mДанные успешно загружены!\033[0m";
        }

        void outputToFile(DynamicArray<Record>& records, const std::string& fileName) {
            std::ofstream fout(fileName);

            for (size_t i = 0; i < records.getSize(); ++i) {
                fout << records[i].carBrand << " ";
                fout << records[i].fuelBrand << " ";
                fout << records[i].enginePower << " ";
                fout << records[i].tankCapacity << " ";
                fout << records[i].ownerName << " ";
                fout << records[i].carNumber << " ";
                fout << "\n";
            }

            std::cout << "\033[32mДанные успешно сохранены!\033[0m";
        }

        void addRecord(DynamicArray<Record>& records) {
            Record record;

            std::cout << "\033[1mВведите марку автомобиля: \033[0m";
            std::string carBrand;
            std::getline(std::cin, carBrand);
            record.carBrand = carBrand;

            std::cout << "\033[1mВведите марку топлива: \033[0m";
            std::string fuelBrand;
            std::getline(std::cin, fuelBrand);
            record.fuelBrand = fuelBrand;

            std::cout << "\033[1mВведите имя владельца: \033[0m";
            std::string ownerName;
            std::getline(std::cin, ownerName);
            record.ownerName = ownerName;

            std::cout << "\033[1mВведите номер автомобиля: \033[0m";
            std::string carNumber;
            std::getline(std::cin, carNumber);
            record.carNumber = carNumber;

            std::cout << "\033[1mВведите мощность двигателя (число): \033[0m";
            std::cin >> record.enginePower;

            std::cout << "\033[1mВведите объём бака (число): \033[0m";
            std::cin >> record.tankCapacity;

            records.push_back(record);

            std::cout << "\033[0;32mЗапись добавлена!\033[0m";
        }

        void removeRecord(DynamicArray<Record>& records) {
            if (records.empty()) {
                printMenu();
                std::cout << "\033[1mНет записей для удаления!\033[0m" << std::endl;
                return;
            }

            unsigned int selected = 1;

            bool isRunning = true;

            int key;
            while (isRunning) {
                std::system("clear");

                const int colWidths[] = {4, 15, 12, 14, 15, 16, 12};
                std::cout << "\033[0;1m↑/↓ — перемещение ↵ — удалить ⌫ — выйти\033[0m\n\n"
                          << "┌────┬───────────────┬────────────┬──────────────┬───────────────┬────────────────┬────────────┐\n"
                          << "│\e[1m" << centerText("ID", colWidths[0]) << "\e[0m│\e[1m"
                          << centerText("Brand", colWidths[1]) << "\e[0m│\e[1m"
                          << centerText("Fuel Brand", colWidths[2]) << "\e[0m│\e[1m"
                          << centerText("Engine Power", colWidths[3]) << "\e[0m│\e[1m"
                          << centerText("Tank Capacity", colWidths[4]) << "\e[0m│\e[1m"
                          << centerText("Owner Name", colWidths[5]) << "\e[0m│\e[1m"
                          << centerText("Car Number", colWidths[6]) << "\e[0m│\n"
                          << "├────┼───────────────┼────────────┼──────────────┼───────────────┼────────────────┼────────────┤\n";
                for (size_t i = 0; i < records.getSize(); ++i) {
                    std::cout << "│\e[1m" << centerText(selected == i + 1 ? " \xE2\x9D\x8C " : std::to_string(i + 1), colWidths[0]) << "\e[0m│"
                              << centerText(records[i].carBrand, colWidths[1]) << "│"
                              << centerText(records[i].fuelBrand, colWidths[2]) << "│"
                              << centerText(std::to_string(records[i].enginePower), colWidths[3]) << "│"
                              << centerText(std::to_string(records[i].tankCapacity), colWidths[4]) << "│"
                              << centerText(records[i].ownerName, colWidths[5]) << "│"
                              << centerText(records[i].carNumber, colWidths[6]) << "│\n";
                    if (i < records.getSize() - 1)
                        std::cout << "├────┼───────────────┼────────────┼──────────────┼───────────────┼────────────────┼────────────┤\n";
                }
                std::cout << "└────┴───────────────┴────────────┴──────────────┴───────────────┴────────────────┴────────────┘\n";

                key = getchar();
                switch (key) {
                    case KEY_ARROW_UP:
                        selected = (selected > 1) ? (selected - 1) : records.getSize();
                        break;
                    case KEY_ARROW_DOWN:
                        selected = (selected < records.getSize()) ? (selected + 1) : 1;
                        break;
                    case KEY_ENTER:
                        records.removeAt(selected - 1);
                        if (records.empty()) {
                            isRunning = false;
                        } else {
                            selected = (selected > records.getSize()) ? records.getSize() : selected;
                        }
                        break;
                    case KEY_BACKSPACE:
                        isRunning = false; // Выход
                        break;
                }
            }
            printMenu();
        }

        void printTable(DynamicArray<Record>& records) {
            const int colWidths[] = {4, 15, 12, 14, 15, 18, 12};

            std::cout << "┌────┬───────────────┬────────────┬──────────────┬───────────────┬──────────────────┬────────────┐\n"
                      << "│\033[1m" << centerText("ID", colWidths[0]) << "\033[0m"
                      << "│\033[1m"<< centerText("Brand", colWidths[1]) << "\033[0m"
                      << "│\033[1m"<< centerText("Fuel Brand", colWidths[2]) << "\033[0m"
                      << "│\033[1m"<< centerText("Engine Power", colWidths[3]) << "\033[0m"
                      << "│\033[1m"<< centerText("Tank Capacity", colWidths[4]) << "\033[0m"
                      << "│\033[1m"<< centerText("Owner Name", colWidths[5]) << "\033[0m"
                      << "│\033[1m"<< centerText("Car Number", colWidths[6]) << "\033[0m│\n"
                      << "├────┼───────────────┼────────────┼──────────────┼───────────────┼──────────────────┼────────────┤\n";

            for (size_t i = 0; i < records.getSize(); ++i) {
                std::cout << "│\e[1m" << centerText(std::to_string(i + 1), colWidths[0]) << "\e[0m│"
                          << centerText(records[i].carBrand, colWidths[1]) << "│"
                          << centerText(records[i].fuelBrand, colWidths[2]) << "│"
                          << centerText(std::to_string(records[i].enginePower), colWidths[3]) << "│"
                          << centerText(std::to_string(records[i].tankCapacity), colWidths[4]) << "│"
                          << centerText(records[i].ownerName, colWidths[5]) << "│"
                          << centerText(records[i].carNumber, colWidths[6]) << "│\n";
                if (i < records.getSize() - 1)
                    std::cout << "├────┼───────────────┼────────────┼──────────────┼───────────────┼──────────────────┼────────────┤\n";
            }
            std::cout << "└────┴───────────────┴────────────┴──────────────┴───────────────┴──────────────────┴────────────┘\n";
            std::cout << "\033[1mРезультатов: \033[0;33m" << records.getSize() << "\033[0m\n";
        }

        void customSort(DynamicArray<Record>& records, bool (*compare)(const Record&, const Record&, bool ascending), bool ascending = true) {
            bool isSorted = false;
            while (!isSorted) {
                isSorted = true;
                for (size_t i = 1; i < records.getSize(); ++i) {
                    if (compare(records[i - 1], records[i], ascending)) {
                        std::swap(records[i - 1], records[i]);
                        isSorted = false;
                    }
                }
            }
        }

        static bool compareByOwnerName(const Record& a, const Record& b, bool ascending) {
            return ascending ? a.ownerName > b.ownerName : a.ownerName < b.ownerName;
        }

        static bool compareByCarBrandAndOwnerName(const Record& a, const Record& b, bool ascending) {
            if (a.carBrand == b.carBrand) return ascending ? a.ownerName > b.ownerName : a.ownerName < b.ownerName;
            return ascending ? a.carBrand > b.carBrand : a.carBrand < b.carBrand;
        }

        static bool compareByTankCapacity(const Record& a, const Record& b, bool ascending) {
            return ascending ? a.tankCapacity > b.tankCapacity : a.tankCapacity < b.tankCapacity;
        }

        void printListOfBrands(DynamicArray<Record>& records) {
            std::map<std::string, int> brandCounts;

            for (size_t i = 0; i < records.getSize(); ++i)
                ++brandCounts[records[i].carBrand];

            const int colWidths[] = {4, 15, 7};

            unsigned int id = 1;
            std::cout << "┌────┬───────────────┬───────┐\n"
                      << "│\e[1m" <<  centerText("ID", colWidths[0]) << "\e[0m│\e[1m"
                      << centerText("Brand", colWidths[1]) << "\e[0m│\e[1m"
                      << centerText("Count", colWidths[2]) << "\e[0m│\n"
                      << "├────┼───────────────┼───────┤\n";;
            for (std::pair<std::string, int> pair : brandCounts) {
                std::cout << "│\e[1m" << centerText(std::to_string(id), colWidths[0]) << "\e[0m│"
                          << centerText(pair.first, colWidths[1]) << "│"
                          << centerText(std::to_string(pair.second), colWidths[2]) << "│\n";
                if (id < brandCounts.size())
                    std::cout << "├────┼───────────────┼───────┤\n";
                id += 1;
            }
            std::cout << "└────┴───────────────┴───────┘\n";
            std::cout << "\e[1mВсего различных марок: \e[0;33m" << brandCounts.size() << "\e[0m\n";
        }

        void findByOwnerName(DynamicArray<Record>& records, const std::string& ownerSurname) {
            DynamicArray<Record> result;
            for (size_t i = 0; i < records.getSize(); ++i) {
                std::string surname = records[i].ownerName.substr(0, records[i].ownerName.find(' '));
                if (ownerSurname == surname) result.push_back(records[i]);
            }
            customSort(result, compareByCarBrandAndOwnerName);
            printTable(result);
        }
};
