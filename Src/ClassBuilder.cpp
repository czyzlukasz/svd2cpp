#include <ClassBuilder.hpp>
#include <Builders.hpp>


ClassBuilder::ClassBuilder(const cxxopts::ParseResult& results,
                           const DeviceInfo& deviceInfo,
                           const std::vector<Peripheral>& peripherals) :
        results(results),
        deviceInfo(deviceInfo),
        peripherals(peripherals){
        }

void ClassBuilder::setupBuilders(){
    builders.push_back(std::make_unique<ZeroPointerBuilder>());
    for(auto& peripheral : peripherals){
        builders.push_back(std::make_unique<PeripheralBuilder>(peripheral));
    }
}

void ClassBuilder::build(){
    for(auto& builder : builders){
        builder->build(outputStream);
    }
    std::cout << outputStream.str();
}
