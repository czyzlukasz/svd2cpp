#include <Builders.hpp>
#include <iostream>


void ZeroPointerBuilder::build(std::stringstream& ss) const{
    ss << "template <unsigned int zero = 0>\n"
          "constexpr unsigned int *zeroVal = reinterpret_cast<unsigned int *>(zero);\n";
}

void PeripheralBuilder::build(std::stringstream& ss) const{
    ss << "namespace " << peripheral.name << "{\n";
    for(auto& registe : peripheral.registers){
        RegisterBuilder(registe, peripheral.baseAddress).build(ss);
    }
    ss << "}\n";
}

void RegisterBuilder::build(std::stringstream& ss) const{
    ss << "    "
       << "namespace " << registe.name << "{\n";
    for(auto& field : registe.fields){
        FieldBuilder(field, getRegisterAddress()).build(ss);
    }
    ss << "    " << "}\n";
}

unsigned int RegisterBuilder::getRegisterAddress() const{
    return baseAddress + registe.addressOffset;
}

void FieldBuilder::build(std::stringstream& ss) const{
    ss << "        " << "struct " << field.name << "{\n";
    
    ss << "        " << "    " << "constexpr static inline unsigned int bitOffset(){"
       << "return " << field.bitOffset << ";}\n";

    ss << "        " << "    " << "constexpr static inline unsigned int bitMask(){"
       << "return " << field.bitWidth << ";}\n";

    ss << "        " << "    " << "constexpr static inline unsigned int* address(){"
       << "return zeroVal<> + " << getAddress() << ";}\n";
    ss << "       };\n";
}

std::string FieldBuilder::getAddress() const{
    return std::to_string(registerAddress);
}
