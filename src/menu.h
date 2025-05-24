#pragma once

#include "dynarray.h"
#include "menufunc.h"

class Menu : public FunctionalMenu {
public:
    Menu(const DynamicArray<std::string>& options) : FunctionalMenu(options) {}

    const DynamicArray<std::string>& getOptions() {
        return options;
    }
};

std::ostream& operator<<(std::ostream& out, Menu& menu) {
    const auto& opts = menu.getOptions();
    out << "Menu options:\n";
    for (size_t i = 0; i < opts.getSize(); ++i) {
        out << opts[i] << '\n';
    }
    return out;
}
