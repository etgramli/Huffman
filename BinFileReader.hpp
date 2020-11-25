//BinFileReader.hpp

#ifndef BINFILEREADER_H
#define BINFILEREADER_H


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
		unsigned int bits = 0;

		while (bits < lengthInBits) {
			unsigned int bitsToRead = std::min((unsigned long int) std::numeric_limits<unsigned char>::digits, lengthInBits-bits);

			for (bool b : parseChar(*currentByte, bitsToRead)) {
				message.push_back(b);
			}

			bits += bitsToRead;
			++currentByte;
		}
	}

	std::vector<bool> parseChar(const char c, const size_t numBits) const {
		std::vector<bool> vec;
		unsigned char bitMask = pow(2, std::numeric_limits<unsigned char>::digits - 1);

		size_t counter = 0;
		while (bitMask != 0 && counter < numBits) {
			vec.push_back(bitMask & c);
			bitMask >>= 1;
			++counter;
		}

		return vec;
	}

public:
    BinFileReader() = delete;
    BinFileReader(const std::string fileName) {
		std::ifstream inputFile(fileName, std::ios::in | std::ios::binary);
		inputFile.seekg(0, inputFile.beg);

        // Read and check magic number
        unsigned char magic = 0;
        inputFile.read(reinterpret_cast<char *>(&magic), sizeof(unsigned char));
        if (magicNum != magic) {
			inputFile.close();
			throw "File format not recognized";
		}

        // Read length of message
		size_t lengthOfMessage = 0;
		inputFile.read(reinterpret_cast<char *>(&lengthOfMessage),
					   sizeof(size_t));

        // Read whole message to vector
        size_t bytesToRead = std::ceil((float)lengthOfMessage / std::numeric_limits<unsigned char>::digits);
        char *mem = new char[bytesToRead]();
        inputFile.read(mem, bytesToRead);
        
        size_t readBytes = inputFile.gcount(); // Check how many bytes actually read
        size_t actualBitsOfMessage = std::min(lengthOfMessage, readBytes * 8);
        parseMessage(mem, actualBitsOfMessage);
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
