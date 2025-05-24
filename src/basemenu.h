#include <string>
#include "dynarray.h"
#include "record.h"

class BaseMenu {
    protected:
        DynamicArray<std::string> options;
        size_t selected;
    public:
        BaseMenu(const DynamicArray<std::string>& options) {
            this->options = options;
            selected = 1;
        }
};
