#ifndef BUILDERS
#define BUILDERS

#include <IBuilder.hpp>
#include <sstream>
#include <Peripheral.hpp>
#include <sstream>

struct ZeroPointerBuilder : public IBuilder{
    void build(std::stringstream& ss) const final;
};

struct PeripheralBuilder : public IBuilder{
    PeripheralBuilder(const Peripheral &peripheral_) : peripheral(peripheral_) {}
    void build(std::stringstream& ss) const final;

private:
    const Peripheral& peripheral;
};

struct RegisterBuilder : public IBuilder{
    RegisterBuilder(const Register& register_, const unsigned int baseAddress_)
        : registe(register_), baseAddress(baseAddress_) {}
    void build(std::stringstream& ss) const final;
    unsigned int getRegisterAddress() const;
private:
    const Register& registe;
    const unsigned int baseAddress;
};

struct FieldBuilder : public IBuilder{
    FieldBuilder(const Field& field_, const unsigned int registerAddress_)
        : field(field_), registerAddress(registerAddress_) {}
    void build(std::stringstream& ss) const final;
    std::string getAddress() const;

private:
    const Field& field;
    const unsigned int registerAddress;
};
#endif
