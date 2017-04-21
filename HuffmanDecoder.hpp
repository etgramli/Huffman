//HuffmanDecoder.hpp

#ifndef HUFFMANDECODER_H
#define HUFFMANDECODER_H


#include <map>
#include <vector>
#include <string>

#include "GenericNode.hpp"


class HuffmanDecoder {
private:
	std::map<std::vector<bool>, char> encodingTable;

	// Reads and parses the file with the huffman code table and writes
	// it to the encodingTable.
	void readHuffmanCodeFile(std::string huffmanCodeFile);

	std::vector<bool> getBitVector(std::string str, unsigned int offset) const;


public:
	/*
	 * Reads the encoding table and decodes the text file accordingly.
	 * huffmanCodeFile		The file with the huffman code
							(<character> <space> <symbol>)
	 * huffmanEncodedFile	The text file that contains the text with
							the huffman code specified in huffmanCodeFile.
	 * outFile				The file to write the original file to.
	 */
	void decodeFile(std::string huffmanCodeFile, std::string huffmanEncodedFile, std::string outFile);

};


#endif
