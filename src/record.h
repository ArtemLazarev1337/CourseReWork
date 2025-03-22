#pragma once

#include <ostream>
#include <string>

struct Record {
    std::string carBrand;
    std::string fuelBrand;
    unsigned int enginePower;
    unsigned int tankCapacity;
    std::string ownerName;
    std::string carNumber;
};

std::ostream& operator<<(std::ostream& out, const Record& record) {
    out << "{"
        << record.carBrand << ", "
        << record.fuelBrand << ", "
        << record.enginePower << ", "
        << record.tankCapacity << ", "
        << record.ownerName << ", "
        << record.carNumber
        << "}";
    return out;
}
