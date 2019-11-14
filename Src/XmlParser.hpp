#ifndef XML_PARSER
#define XML_PARSER

#include <tinyxml2.h>
#include <string>
#include <optional>
#include <memory>

struct XmlParser{
    XmlParser(const std::string& inputFile);
    std::optional<std::string> isError() const;
    void parseXml();

private:
    tinyxml2::XMLDocument xmlDocument;
    tinyxml2::XMLElement* root;
};

#endif