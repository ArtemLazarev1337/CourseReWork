#pragma once

#include "dynarray.h"
#include "menu.h"
#include "record.h"

class Aggregated {
public:
    Menu menu;
    DynamicArray<Record> records;

    Aggregated(const Menu& menu, const DynamicArray<Record> records) : menu(menu), records(records) {}

    Aggregated(const Aggregated& other)
        : menu(other.menu), records(other.records)
    {}

    Aggregated& operator=(const Aggregated& other) {
        if (this != &other) {
            menu = other.menu;
            records = other.records;
        }
        return *this;
    }

    // оператор вывода в поток
    friend std::ostream& operator<<(std::ostream& os, Aggregated& a) {
        os << "Menu:\n" << a.menu;
        os << "Records:\n" << a.records;
        return os;
    }
};
