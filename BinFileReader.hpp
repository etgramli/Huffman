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

	// Converts the memory to a vector of booleans (directly to message)
	void parseMessage(char *mem, size_t lengthInBits) {
		char *currentByte = mem;
		unsigned int bits = 0;

		while (bits < lengthInBits) {
			size_t bitsToRead = std::min((unsigned long int) std::numeric_limits<unsigned char>::digits, lengthInBits-bits);

			for (bool b : parseChar(*currentByte, bitsToRead)) {
				message.push_back(b);
			}

			bits += bitsToRead;
			++currentByte;
		}
	}

	static std::vector<bool> parseChar(const char c, const size_t numBits) {
		const double bitMaskDouble = pow(2, std::numeric_limits<unsigned char>::digits - 1);
		unsigned char bitMask = bitMaskDouble > std::numeric_limits<unsigned char>::max() ?
		        std::numeric_limits<unsigned char>::max() : (unsigned char) bitMaskDouble;

        std::vector<bool> vec;
        for (size_t counter = 0; bitMask != 0 && counter < numBits; ++counter, bitMask >>= 1u) {
            vec.push_back(bitMask & c);
        }

		return vec;
	}

public:
    BinFileReader() = delete;
    explicit BinFileReader(const std::string& fileName) {
		std::ifstream inputFile(fileName, std::ios::in | std::ios::binary);
		inputFile.seekg(0, std::ifstream::beg);

        // Read and check magic number
        unsigned char magic = 0;
        inputFile.read(reinterpret_cast<char *>(&magic), sizeof(unsigned char));
        if (magicNum != magic) {
			inputFile.close();
			throw std::runtime_error("File format not recognized");
		}

        // Read length of message
		size_t lengthOfMessage = 0;
		inputFile.read(reinterpret_cast<char *>(&lengthOfMessage),
					   sizeof(size_t));

        // Read whole message to vector
        const auto bytesToRead = (size_t) std::ceil((float) lengthOfMessage / std::numeric_limits<unsigned char>::digits);
        char *mem = new char[bytesToRead]();
        inputFile.read(mem, bytesToRead);
        
        const long readBytesE = inputFile.gcount(); // Check how many bytes actually read
        if (readBytesE < 0) {
            throw std::runtime_error("Error determining read bytes!");
        }
        const size_t readBytes = (size_t) readBytesE;
        const size_t actualBitsOfMessage = std::min(lengthOfMessage, readBytes * 8);
        parseMessage(mem, actualBitsOfMessage);
        delete[] mem;
        
        inputFile.close();
    }

    ~BinFileReader() = default;


	std::vector<bool> getMessageAsVector() {
		return message;
	}

};


#endif
