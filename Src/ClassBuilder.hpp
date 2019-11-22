#ifndef CLASS_PRINTER
#define CLASS_PRINTER

#include <cxxopts.hpp>
#include <DeviceInfo.hpp>
#include <Peripheral.hpp>
#include <vector>
#include <IBuilder.hpp>
#include <memory>
#include <sstream>


struct ClassBuilder
{
    ClassBuilder(const cxxopts::ParseResult& results_,
                 const DeviceInfo& deviceInfo_,
                 const std::vector<Peripheral>& peripherals_);
    void setupBuilders();
    void build();

private:
    const cxxopts::ParseResult& results;
    const DeviceInfo& deviceInfo;
    const std::vector<Peripheral>& peripherals;
    std::vector<std::unique_ptr<IBuilder>> builders;
    std::stringstream outputStream;
};

#endif
