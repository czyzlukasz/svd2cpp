#include <ClassBuilder.hpp>

ClassBuilder::ClassBuilder(const cxxopts::ParseResult& results,
                           const DeviceInfo& deviceInfo,
                           const std::vector<Peripheral>& peripherals) :
        results(results),
        deviceInfo(deviceInfo),
        peripherals(peripherals){
        }
