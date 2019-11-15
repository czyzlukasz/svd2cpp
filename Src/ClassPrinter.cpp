#include <ClassPrinter.hpp>

ClassPrinter::ClassPrinter(const cxxopts::ParseResult& results,
                           const DeviceInfo& deviceInfo,
                           const std::vector<Peripheral>& peripherals) :
        results(results),
        deviceInfo(deviceInfo),
        peripherals(peripherals){
        }
