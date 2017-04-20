//BinFileReader.hpp

#ifndef BINFILEREADER_H
#define BINFILEREADER_H

#include <fstream>
#include <string>
#include <vector>
#include <limits>

class BinFileReader {
private:
    std::ifstream inputFile;

    std::vector<bool> message;


public:
    BinFileReader() = delete;
    BinFileReader(std::string fileName) : inputFile(fileName, std::ios::in | std::ios::binary) {
        // Read and check magic number
        // Read length of message
        // Read whole message to vector
    }

    ~BinFileReader() {
        inputFile.close();
    }

};


#endif
