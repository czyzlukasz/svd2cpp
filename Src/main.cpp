#include <iostream>
#include <cxxopts.hpp>
#include <XmlParser.hpp>
#include <ClassBuilder.hpp>


int main(int argc, char** argv){
    // Create and configure options for the program
    cxxopts::Options options("svd2cpp", "Parser from svd files to C++ header");
    options.add_options()
        ("i, input", "File to be parsed", cxxopts::value<std::string>())
        ("o, output", "OutputFile", cxxopts::value<std::string>());
    std::string inputFile, outputFile;
    auto result = options.parse(argc, argv);
    try
    {
        if(result.count("input") != 1){
            std::cout << "Missing input file!" << std::endl;
            return 1;
        }
        if(result.count("output") != 1){
            std::cout << "Missing output file!" << std::endl;
            return 1;
        }
        inputFile = result["input"].as<std::string>();
        outputFile = result["output"].as<std::string>();
        std::cout << "Input: " << inputFile << "\tOutput: " << outputFile << std::endl;
    }
    catch(cxxopts::OptionException& ex){
        std::cout << ex.what() << std::endl;
        return 2;
    }
    //Try to parse the file
    XmlParser xmlParser(inputFile);
    if (auto err = xmlParser.isError()){
        std::cout << "There was an error while reading " << inputFile << ":" << std::endl << *err << std::endl;
        return 3;
    }
    xmlParser.parseXml();
    ClassBuilder classBuilder(result, xmlParser.getDeviceInfo(), xmlParser.getPeripherals());
    classBuilder.setupBuilders();
    classBuilder.build();
}