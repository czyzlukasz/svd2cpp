#include <XmlParser.hpp>
#include <iostream>


XmlParser::XmlParser(const std::string& inputFile){
    xmlDocument.LoadFile(inputFile.c_str());
}
std::optional<std::string> XmlParser::isError() const{
    return xmlDocument.Error() ? std::optional<std::string>(xmlDocument.ErrorStr()) : std::nullopt;
}

void XmlParser::parseXml(){
    tinyxml2::XMLElement* deviceRoot = xmlDocument.FirstChildElement("device");
    if(deviceRoot == nullptr)
        return;
    //Set Schema Version
    deviceInfo.schemaVersion = deviceRoot->Attribute("schemaVersion");

    //Set attributes
    setDeviceInfoAttrib(deviceRoot, "name", deviceInfo.name);
    setDeviceInfoAttrib(deviceRoot, "version", deviceInfo.version);
    setDeviceInfoAttrib(deviceRoot, "resetValue", deviceInfo.resetValue);

    deviceInfo.printDeviceInfo();

    //Iterate over all peripherals and append them to peripherals
    tinyxml2::XMLElement *peripheralsRoot = deviceRoot->FirstChildElement("peripherals");
    if(peripheralsRoot != nullptr){
        for (tinyxml2::XMLNode* peripheralRoot = peripheralsRoot->FirstChild();
             peripheralRoot;
             peripheralRoot = peripheralRoot->NextSibling()){
                 //Parse only "peripheral" node
                 if(std::string(peripheralRoot->Value()) != "peripheral"){
                     std::cout << "Register node has value " << peripheralRoot->Value();
                     continue;
                 }
                 peripherals.push_back(parsePeripheral(peripheralRoot->ToElement()));
             }
    }
}

void XmlParser::setDeviceInfoAttrib(tinyxml2::XMLElement* deviceRoot, const char* name, std::string &field){
    tinyxml2::XMLElement* deviceEntry = deviceRoot->FirstChildElement(name);
    field = deviceEntry != nullptr ? deviceEntry->GetText() : noValue;
}

void XmlParser::setDeviceInfoAttrib(tinyxml2::XMLElement* deviceRoot, const char* name, unsigned int &field){
    tinyxml2::XMLElement* deviceEntry = deviceRoot->FirstChildElement(name);
    field = deviceEntry != nullptr ? std::stol(deviceEntry->GetText(), 0, 16) : 0;
}
void XmlParser::setDeviceInfoAttrib(tinyxml2::XMLElement* deviceRoot, const char* name, EAccess &field){
    tinyxml2::XMLElement* deviceEntry = deviceRoot->FirstChildElement(name);
    if(deviceEntry == nullptr){
        field = EAccess::Read_Write;
        return;
    }
    const std::string text = deviceEntry->GetText();
    if(text == "read-only"){
        field = EAccess::Read_Only;
    }
    else if(text == "write-only"){
        field = EAccess::Write_Only;
    }
    else if(text == "read-write"){
        field = EAccess::Read_Write;
    }
    else{
        std::cout << "Wrong field for access: " << text << std::endl;
    }
}
unsigned int peripheralCount = 0;
Peripheral XmlParser::parsePeripheral(tinyxml2::XMLElement* peripheralRoot){
    std::cout << "Peripheral: " << peripheralCount++ << std::endl;
    Peripheral peripheral;
    setDeviceInfoAttrib(peripheralRoot, "name", peripheral.name);
    setDeviceInfoAttrib(peripheralRoot, "description", peripheral.description);
    setDeviceInfoAttrib(peripheralRoot, "groupName", peripheral.groupName);
    setDeviceInfoAttrib(peripheralRoot, "baseAddress", peripheral.baseAddress);

    peripheral.addressBlock = parseAddressBlock(peripheralRoot->FirstChildElement("addressBlock"));

    //Iterate over all registers and append them to peripheral
    tinyxml2::XMLElement *registersRoot = peripheralRoot->FirstChildElement("registers");
    if(registersRoot != nullptr){
        for (tinyxml2::XMLNode* registerRoot = registersRoot->FirstChild();
             registerRoot;
             registerRoot = registerRoot->NextSibling()){
                 //Parse only "register" node
                 if(std::string(registerRoot->Value()) != "register"){
                     std::cout << "Register node has value " << registerRoot->Value();
                     continue;
                 }
                 peripheral.registers.push_back(parseRegister(registerRoot->ToElement()));
             }
    }
    return peripheral;
}

AddressBlock XmlParser::parseAddressBlock(tinyxml2::XMLElement* addressBlockRoot){
    AddressBlock addressBlock;
    if(addressBlockRoot){
        setDeviceInfoAttrib(addressBlockRoot, "offset", addressBlock.offset);
        setDeviceInfoAttrib(addressBlockRoot, "size", addressBlock.size);
    }
    else
        std::cout << "parseAddressBlock is nullptr!" << std::endl;
    return addressBlock;
}

Register XmlParser::parseRegister(tinyxml2::XMLElement* registerRoot){
    Register registe;
    setDeviceInfoAttrib(registerRoot, "name", registe.name);
    setDeviceInfoAttrib(registerRoot, "description", registe.description);
    setDeviceInfoAttrib(registerRoot, "addressOffset", registe.addressOffset);
    setDeviceInfoAttrib(registerRoot, "size", registe.size);
    setDeviceInfoAttrib(registerRoot, "access", registe.registerAccess);
    setDeviceInfoAttrib(registerRoot, "resetValue", registe.resetValue);

    //Iterate over all fields and append them to registe
    tinyxml2::XMLElement* fieldsRoot = registerRoot->FirstChildElement("fields");
    if(fieldsRoot != nullptr){
        for (tinyxml2::XMLNode *fieldRoot = fieldsRoot->FirstChild();
             fieldRoot;
             fieldRoot = fieldRoot->NextSibling()){
                 //Parse only "field" node
                 if(std::string(fieldRoot->Value()) != "field"){
                     std::cout << "Field node has value " << fieldRoot->Value();
                     continue;
                 }
                 registe.fields.push_back(parseField(fieldRoot->ToElement()));
             }
    }
    return registe;
}
Field XmlParser::parseField(tinyxml2::XMLElement* fieldRoot){
    Field field;
    setDeviceInfoAttrib(fieldRoot, "name", field.name);
    setDeviceInfoAttrib(fieldRoot, "description", field.description);
    setDeviceInfoAttrib(fieldRoot, "bitOffset", field.bitOffset);
    setDeviceInfoAttrib(fieldRoot, "bitWidth", field.bitWidth);
    setDeviceInfoAttrib(fieldRoot, "access", field.fieldAccess);
    return field;
}