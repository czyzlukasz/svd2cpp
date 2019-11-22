#include <Builders.hpp>

void ZeroPointerBuilder::build(std::stringstream& ss){
    ss << "template <unsigned int zero = 0>\n"
          "constexpr unsigned int *zeroVal = reinterpret_cast<unsigned int *>(zero);\n";
}

void PeripheralBuilder::build(std::stringstream& ss){
    ss << "namespace " << peripheral.name.c_str() << "{\n";
    for(auto& registe : peripheral.registers){
        RegisterBuilder(registe).build(ss);
    }
    ss << "}\n";
}

void RegisterBuilder::build(std::stringstream& ss){
    //TODO: fix INVALID: some derived names are not copied
    ss << "    "
       << "namespace " << (registe.name.length() > 100 ? "INVALID" : registe.name) << "{\n";
    for(auto& field : registe.fields){
        FieldBuilder(field).build(ss);
    }
    ss << "    " << "}\n";
}

void FieldBuilder::build(std::stringstream& ss){
    ss << "        " << "struct " << (field.name.length() > 100 ? "INVALID" : field.name) << "{\n";
    
    //TODO: fix INVALID: some derived items are not copied
    ss << "        " << "    " << "constexpr static inline unsigned int bitOffset(){"
       << "return " << field.bitOffset << "}\n";
    
    ss << "        " << "    " << "constexpr static inline unsigned int bitMask(){"
       << "return " << field.bitWidth << "}\n";
    
    ss << "        " << "    " << "constexpr static inline unsigned int address(){"
       << "return " << "TODO" << "}\n";
    ss << "       }\n";
}