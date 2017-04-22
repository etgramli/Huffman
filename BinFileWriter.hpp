//BinFileWriter.hpp

#ifndef BINFILEWRITER_H
#define BINFILEWRITER_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cmath>



class BinFileWriter {
private:
    const unsigned char magicNum = 0xEF;	// Stands for "Eti's Format"

    std::ofstream outFile;

    std::vector<std::vector<bool> *> messagePtr;


    void writeToFile() {
		// Write magic number
        outFile.write(reinterpret_cast<const char *>(&magicNum),
					  sizeof(unsigned char));

		size_t numBits = 0;
		for (std::vector<bool> *codeWord : messagePtr) {
			numBits += codeWord->size();
		}

		// Write length of file
		outFile.write(reinterpret_cast<const char *>(&numBits),
					  sizeof(size_t));

		size_t numBytes = std::ceil((float) numBits / std::numeric_limits<unsigned char>::digits);

		// Write memory to file
		char *mem = new char[numBytes]();
		getMessageAsCharArray(mem);
		
		outFile.write(mem, numBytes);
		
		delete[] mem;
	}


	void getMessageAsCharArray(char *mem) {
		unsigned int counter = 0;
		char *currentChar = mem;

		for (std::vector<bool> *codeWord : messagePtr) {
			for (bool b : *codeWord) {
				if (counter == std::numeric_limits<unsigned char>::digits) {
					++currentChar;
					counter = 0;
				}
				appendToChar(currentChar, b);
				++counter;
			}
		}

		if (counter < std::numeric_limits<unsigned char>::digits) {
			unsigned char bitsToShift
				= std::numeric_limits<unsigned char>::digits - counter;
			(*currentChar) <<= bitsToShift;
		}
	}

    void appendToChar(char *c, const bool bit) {
		(*c) <<= 1;
		if (bit) {
			++(*c);
		}
	}


public:
    BinFileWriter() = delete;

    BinFileWriter(std::string fileName)
            : outFile(fileName, std::ios::out | std::ios::binary) {
		messagePtr = std::vector<std::vector<bool> *>();
    }

    ~BinFileWriter() {
        writeToFile();
        outFile.close();
    }


	void append(std::vector<bool> *bits) {
		messagePtr.push_back(bits);
	}
};


#endif
