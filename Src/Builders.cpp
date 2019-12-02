#include <Builders.hpp>
#include <iostream>
#include <bitset>

void ZeroPointerBuilder::build(std::stringstream& ss) const{
    ss << "template <unsigned int zero = 0>\n"
          "constexpr unsigned int *zeroVal = reinterpret_cast<unsigned int *>(zero);\n\n";
}

void FieldDefineBuilder::build(std::stringstream& ss) const{
    ss << "#define __FIELD(_FieldName, _bitOffset, _bitMask, _address)                          \\\n"
          "struct _FieldName                                                                    \\\n"
          "{                                                                                    \\\n"
          "    constexpr static inline unsigned int bitOffset() { return _bitOffset; }          \\\n"
          "    constexpr static inline unsigned int bitMask() { return _bitMask; }              \\\n"
          "    constexpr static inline unsigned int *address() { return zeroVal<> + _address; } \\\n"
          "};\n\n";
}

void PeripheralBuilder::build(std::stringstream& ss) const{
    ss << "namespace " << peripheral.name << "{\n";
    for(auto& registe : peripheral.registers){
        RegisterBuilder(registe, peripheral.baseAddress).build(ss);
    }
    ss << "}\n\n";
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
    ss << "        " << "__FIELD(" << field.name << ", "
       << field.bitOffset << ", "
       << field.bitWidth << ", "
       << std::hex << "0x" << getAddress() << std::dec << ")\n";
}

unsigned int FieldBuilder::getAddress() const{
    return registerAddress;
}

void FunctionsBuilder::build(std::stringstream& ss) const{
    ss << "template<class FIELD>\n"
          "constexpr inline void set(){\n"
          "    *FIELD::address() |= 1 << FIELD::bitOffset();\n"
          "}\n"
          "\n"
          "template<class FIELD, unsigned int VAL>\n"
          "constexpr inline void set(){\n"
          "    static_assert(VAL & (FIELD::bitMask() >> FIELD::bitOffset()), \"Value is too big\");\n"
          "    *FIELD::address() = *FIELD::address() & ~FIELD::bitMask() | VAL << FIELD::bitOffset();\n"
          "}\n"
          "\n"
          "template<class FIELD>\n"
          "constexpr inline void reset(){\n"
          "    *FIELD::address() &= ~(1 << FIELD::bitOffset());\n"
          "}\n"
          "\n"
          "template<class FIELD>\n"
          "constexpr inline unsigned int read(){\n"
          "    return (*FIELD::address() & FIELD::bitMask()) >> FIELD::bitOffset();\n"
          "}"
          "\n\n";
}