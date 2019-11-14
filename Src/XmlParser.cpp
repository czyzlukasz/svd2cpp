#include <XmlParser.hpp>
#include <iostream>

XmlParser::XmlParser(const std::string& inputFile){
    xmlDocument.LoadFile(inputFile.c_str());
}
std::optional<std::string> XmlParser::isError() const{
    return xmlDocument.Error() ? std::optional<std::string>(xmlDocument.ErrorStr()) : std::nullopt;
}

void XmlParser::parseXml(){
    root = xmlDocument.FirstChildElement();
    if(root == nullptr)
        return;
    std::cout << root->GetText();
}