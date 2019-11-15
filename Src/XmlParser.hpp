#ifndef XML_PARSER
#define XML_PARSER

#include <tinyxml2.h>
#include <string>
#include <optional>
#include <memory>
#include <DeviceInfo.hpp>
#include <vector>
#include <Peripheral.hpp>

struct XmlParser{
    XmlParser(const std::string& inputFile);
    std::optional<std::string> isError() const;
    void parseXml();

private:
    // tinyxml2::XMLElement* getDevice
    void setDeviceInfoAttrib(tinyxml2::XMLElement* deviceRoot, const char* name, std::string &field);
    void setDeviceInfoAttrib(tinyxml2::XMLElement* deviceRoot, const char* name, unsigned int &field);
    void setDeviceInfoAttrib(tinyxml2::XMLElement* deviceRoot, const char* name, EAccess &field);

    Peripheral parsePeripheral(tinyxml2::XMLElement* peripheralRoot);
    AddressBlock parseAddressBlock(tinyxml2::XMLElement* addressBlockRoot);
    Register parseRegister(tinyxml2::XMLElement* registerRoot);
    Field parseField(tinyxml2::XMLElement* fieldRoot);

private:
    tinyxml2::XMLDocument xmlDocument;
    static const inline std::string noValue = "Not found";
    DeviceInfo deviceInfo;
    std::vector<Peripheral> peripherals;
};

#endif