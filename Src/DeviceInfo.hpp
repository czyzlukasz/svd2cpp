#ifndef DEVICE_INFO
#define DEVICE_INFO

#include <iostream>


struct DeviceInfo{
    std::string schemaVersion;
    std::string name;
    std::string version;
    unsigned int resetValue;

    void printDeviceInfo() const{
        std::cout << "schemaVersion " << schemaVersion << std::endl
                  << "name " << name << std::endl
                  << "version " << version << std::endl
                  << "resetValue 0x" << std::hex << resetValue << std::dec << std::endl;
    }
};

#endif
