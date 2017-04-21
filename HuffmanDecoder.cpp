//HuffmanDecoder.cpp

#include <iostream>
#include <vector>
#include <map>


#include <fstream>
#include <string>

#include "HuffmanDecoder.hpp"
#include "BinFileReader.hpp"

void HuffmanDecoder::readHuffmanCodeFile(std::string huffmanCodeFile) {
	std::ifstream inFile(huffmanCodeFile);

	// Loop through lines
	std::string line;
	while (std::getline(inFile, line)) {
		char c;
		std::vector<bool> bits;

		// NEED SPECIAL BEHAVIOUR FOR NEWLINE
		if (line.empty()) {
			c = '\n';
			if (!std::getline(inFile, line)) {
				break;	// EOF
			}
			bits = getBitVector(line, 1);
		} else {	// Normal behaviour
			c = line[0];
			bits = getBitVector(line, 2);
		}
		encodingTable.emplace(bits, c);
	}
}

std::vector<bool> HuffmanDecoder::getBitVector(std::string str,
											   unsigned int offset) const {
	std::vector<bool> bits;
	for (unsigned int i = offset; i < str.size(); ++i) {
		if (str[i] == '0') {
			bits.push_back(false);
		} else {
			bits.push_back(true);
		}
	}
	return bits;
}

void HuffmanDecoder::decodeFile(std::string huffmanCodeFile, std::string huffmanEncodedFile, std::string outFile) {
	readHuffmanCodeFile(huffmanCodeFile);

	BinFileReader bfr(huffmanEncodedFile);
	std::ofstream outputFile(outFile, std::ios::out);

	for (std::pair<std::vector<bool>, char> p : encodingTable) {
		for (bool b : p.first) {
			std::cout << b;
		}
		std::cout << " " << p.second << std::endl;
	}

	// Loop through the encoded file and print according character
	std::vector<bool> currentHuffCode;
	for (bool b : bfr.getMessageAsVector()) {
		currentHuffCode.push_back(b);

		// Test if vector contains huffman code
		if (encodingTable.find(currentHuffCode) != encodingTable.end()) {
			outputFile << encodingTable[currentHuffCode];
			currentHuffCode = std::vector<bool>();
		}
	}
	
	outputFile.close();
}
