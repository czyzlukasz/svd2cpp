#include <XmlParser.hpp>
#include <iostream>
#include <algorithm>

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

    // deviceInfo.printDeviceInfo();

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

void XmlParser::setDeviceInfoAttrib(tinyxml2::XMLElement* deviceRoot, const char* name, std::string &field) const{
    tinyxml2::XMLElement* deviceEntry = deviceRoot->FirstChildElement(name);
    field = deviceEntry != nullptr ? deviceEntry->GetText() : noValue;
}

void XmlParser::setDeviceInfoAttrib(tinyxml2::XMLElement* deviceRoot, const char* name, unsigned int &field) const{
    tinyxml2::XMLElement* deviceEntry = deviceRoot->FirstChildElement(name);
    field = deviceEntry != nullptr ? std::stol(deviceEntry->GetText(), 0, 16) : 0;
}
void XmlParser::setDeviceInfoAttrib(tinyxml2::XMLElement* deviceRoot, const char* name, EAccess &field) const{
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
Peripheral XmlParser::parsePeripheral(tinyxml2::XMLElement* peripheralRoot) const{
    //Check if peripheral is derived from previous one
    const char* attribute = peripheralRoot->Attribute("derivedFrom");
    const bool isDerived = attribute != nullptr;
    const std::string derivedFrom = isDerived ? attribute : "";

    Peripheral peripheral;
    if(isDerived == true){
        //Find the base peripheral and copy it to the new one
        auto crit = [&](auto &periph) { return periph.name == derivedFrom; };
        auto resultIt = std::find_if(peripherals.begin(), peripherals.end(), crit);
        if(resultIt < peripherals.end()){
            peripheral = *resultIt;
        }
        else{
            std::cout << "Couldn't find peripheral " << derivedFrom << std::endl;
        }
    }
    setDeviceInfoAttrib(peripheralRoot, "name", peripheral.name);
    setDeviceInfoAttrib(peripheralRoot, "baseAddress", peripheral.baseAddress);
    if(isDerived == false){
        setDeviceInfoAttrib(peripheralRoot, "description", peripheral.description);
        setDeviceInfoAttrib(peripheralRoot, "groupName", peripheral.groupName);
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
    }
    // peripheral.display();
    return peripheral;
}

AddressBlock XmlParser::parseAddressBlock(tinyxml2::XMLElement* addressBlockRoot) const{
    AddressBlock addressBlock;
    if(addressBlockRoot != nullptr){
        setDeviceInfoAttrib(addressBlockRoot, "offset", addressBlock.offset);
        setDeviceInfoAttrib(addressBlockRoot, "size", addressBlock.size);
    }
    else{
        std::cout << "addressBlockRoot is nullptr" << std::endl;
    }
    return addressBlock;
}

Register XmlParser::parseRegister(tinyxml2::XMLElement* registerRoot) const{
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
Field XmlParser::parseField(tinyxml2::XMLElement* fieldRoot) const{
    Field field;
    setDeviceInfoAttrib(fieldRoot, "name", field.name);
    setDeviceInfoAttrib(fieldRoot, "description", field.description);
    setDeviceInfoAttrib(fieldRoot, "bitOffset", field.bitOffset);
    setDeviceInfoAttrib(fieldRoot, "bitWidth", field.bitWidth);
    setDeviceInfoAttrib(fieldRoot, "access", field.fieldAccess);
    return field;
}