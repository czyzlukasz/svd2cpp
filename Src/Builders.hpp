#ifndef BUILDERS
#define BUILDERS

#include <IBuilder.hpp>
#include <sstream>
#include <Peripheral.hpp>
#include <sstream>

struct ZeroPointerBuilder : public IBuilder{
    void build(std::stringstream& ss) final;
};

struct PeripheralBuilder : public IBuilder{
    PeripheralBuilder(const Peripheral& peripheral_) : peripheral(peripheral_){}
    void build(std::stringstream& ss) final;

private:
    const Peripheral& peripheral;
};

struct RegisterBuilder : public IBuilder{
    RegisterBuilder(const Register& register_) : registe(register_){}
    void build(std::stringstream& ss) final;

private:
    const Register& registe;
};

struct FieldBuilder : public IBuilder{
    FieldBuilder(const Field& field_) : field(field_){}
    void build(std::stringstream& ss) final;

private:
    const Field& field;
};
#endif
