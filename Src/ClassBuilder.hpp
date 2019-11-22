#ifndef CLASS_PRINTER
#define CLASS_PRINTER

#include <cxxopts.hpp>
#include <DeviceInfo.hpp>
#include <Peripheral.hpp>
#include <vector>

struct ClassBuilder
{
    ClassBuilder(const cxxopts::ParseResult& results,
                 const DeviceInfo& deviceInfo,
                 const std::vector<Peripheral>& peripherals);

private:
    const cxxopts::ParseResult& results;
    const DeviceInfo& deviceInfo;
    const std::vector<Peripheral>& peripherals;
};


#endif
