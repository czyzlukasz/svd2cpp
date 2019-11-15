#ifndef PERIPHERAL
#define PERIPHERAL

#include <string>
#include <vector>


enum class EAccess{
    Read_Only,
    Write_Only,
    Read_Write
};

struct Field{
    std::string name;
    std::string description;
    unsigned int bitOffset;
    unsigned int bitWidth;
    EAccess fieldAccess;
};

struct Register{
    std::string name;
    std::string description;
    unsigned int addressOffset;
    unsigned int size;
    EAccess registerAccess;
    unsigned int resetValue;
    std::vector<Field> fields;
};

struct AddressBlock{
    unsigned int offset;
    unsigned int size;
};

struct Peripheral{
    std::string name;
    std::string description;
    std::string groupName;
    unsigned int baseAddress;
    AddressBlock addressBlock;
    std::vector<Register> registers;
};

#endif
