//BinFileWriter.hpp

#ifndef BINFILEWRITER_H
#define BINFILEWRITER_H


#include <fstream>
#include <string>
#include <vector>
#include <limits>



class BinFileWriter {
private:
    const int magicNum = 0xEF;

    std::ofstream outFile;

    std::vector<bool> message;


    void writeToFile() {
		// Write magic number
        outFile.write(reinterpret_cast<const char *>(&magicNum),
					  sizeof(int));

		// Write length of file
		size_t lengthOfMessage = message.size();
		outFile.write(reinterpret_cast<const char *>(&lengthOfMessage),
					  sizeof(size_t));

		// Write memory to file
		size_t numBytes = message.size() / std::numeric_limits<unsigned char>::digits + 1;
		char *mem = new char[numBytes]();
		getMessageAsCharArray(mem);
		
		outFile.write(mem, numBytes);
		
		delete[] mem;
	}

	void getMessageAsCharArray(char *mem) {
		// Fill Memory
		unsigned char counter = 0;
		char *currentChar = mem;
		for (bool b : message) {
			if (counter == std::numeric_limits<unsigned char>::digits) {
				++currentChar;
				counter = 0;
			}
			appendToChar(currentChar, b);
			++counter;
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
		message = std::vector<bool>();
    }

    ~BinFileWriter() {
        writeToFile();
        outFile.close();
    }


    void append(const std::string characterSymbol) {
		std::vector<bool> bits;

		for (char c : characterSymbol) {
			bits.push_back(c == '1'? true : false);
		}

        append(bits);
    }

    void append(const std::vector<bool> bits) {
		for (bool b : bits) {
			message.push_back(b);
		}
    }

};


#endif
