//BinFileReader.hpp

#ifndef BINFILEREADER_H
#define BINFILEREADER_H

#include <iostream>

#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>

class BinFileReader {
private:
	const unsigned char magicNum = 0xEF;	// Stands for "Eti's Format"

    std::vector<bool> message;

	// Converts the memory to a vector of bools (directly to message)
	void parseMessage(char *mem, size_t lengthInBits) {
		char *currentByte = mem;
		for (unsigned int bits = 0; bits < lengthInBits; ++bits, ++currentByte) {
			// Get bits and add to vector
			for (bool b : parseChar(*currentByte)) {
				message.push_back(b);
			}
		}
	}

	std::vector<bool> parseChar(const char c) const {
		std::vector<bool> vec;
		unsigned char bitMask = pow(2, std::numeric_limits<unsigned char>::digits - 1);

		while (bitMask != 0) {
			vec.push_back(bitMask & c);
			bitMask >>= 1;
		}

		return vec;
	}

public:
    BinFileReader() = delete;
    BinFileReader(std::string fileName) {
		std::ifstream inputFile(fileName, std::ios::in | std::ios::binary);
		inputFile.seekg(0, inputFile.beg);

        // Read and check magic number
        unsigned char magic = 0;
        inputFile.read(reinterpret_cast<char *>(&magic), sizeof(unsigned char));
        if (magicNum != magic) {
			std::cout << (int)magic << " " << sizeof(unsigned char) << std::endl;
			inputFile.close();
			throw "File format not recognized";
		}

        // Read length of message
		size_t lengthOfMessage = 0;
		inputFile.read(reinterpret_cast<char *>(&lengthOfMessage),
					   sizeof(size_t));

        // Read whole message to vector
        char *mem = new char[lengthOfMessage]();
        inputFile.read(mem, lengthOfMessage);
        
        size_t readBytes = inputFile.gcount(); // Check how many bytes actually read
        parseMessage(mem, readBytes);
        delete[] mem;
        
        inputFile.close();
    }

    ~BinFileReader() {
    }


	std::vector<bool> getMessageAsVector() {
		return message;
	}

};


#endif
