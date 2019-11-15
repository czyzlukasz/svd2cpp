#ifndef PERIPHERAL
#define PERIPHERAL

#include <string>
#include <vector>


enum class EAccess{
    Read_Only,
    Write_Only,
    Read_Write
};

struct IDisplay{
    virtual void display() = 0;
};

struct Field : public IDisplay{
    std::string name;
    std::string description;
    unsigned int bitOffset;
    unsigned int bitWidth;
    EAccess fieldAccess;
    void display() final{
        std::cout << std::endl
                  << "\t\tname: " << name << std::endl
                  << "\t\tdescription: " << description << std::endl
                  << "\t\tbitOffset: " << bitOffset << std::endl
                  << "\t\tbitWidth: " << bitWidth << std::endl
                  << "\t\tfieldAccess: " << (int)fieldAccess << std::endl;
    }
};

struct Register : public IDisplay{
    std::string name;
    std::string description;
    unsigned int addressOffset;
    unsigned int size;
    EAccess registerAccess;
    unsigned int resetValue;
    std::vector<Field> fields;
    
    void display() final{
        std::cout << std::endl
                  << "\tname: " << name << std::endl
                  << "\tdescription: " << description << std::endl
                  << "\taddressOffset: " << addressOffset << std::endl
                  << "\tsize: " << size << std::endl
                  << "\tregisterAccess: " << (int)registerAccess << std::endl
                  << "\tresetValue: " << resetValue << std::endl;
                  
        std::cout << std::endl << "\tfields: " << std::endl;
        for(auto& i : fields){
            i.display();
        }
    }
};

struct AddressBlock : public IDisplay{
    unsigned int offset;
    unsigned int size;
    void display() final{
        std::cout << std::endl
                  << "\toffset: " << offset << std::endl
                  << "\tsize: " << size << std::endl;
    }
};

struct Peripheral : public IDisplay{
    std::string name;
    std::string description;
    std::string groupName;
    unsigned int baseAddress;
    AddressBlock addressBlock;
    std::vector<Register> registers;
    void display() final{
        std::cout << std::endl
                  << "name: " << name << std::endl
                  << "description: " << description << std::endl
                  << "groupName: " << groupName << std::endl
                  << "baseAddress: " << baseAddress << std::endl
                  << "addressBlock: ";
        addressBlock.display();
        std::cout << std::endl << "registers: " << std::endl;
        for(auto& i : registers){
            i.display();
        }
    }
};

#endif
