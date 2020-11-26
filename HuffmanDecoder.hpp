//HuffmanDecoder.hpp

#ifndef HUFFMANDECODER_H
#define HUFFMANDECODER_H


#include <map>
#include <vector>
#include <string>

#include "GenericNode.hpp"


class HuffmanDecoder {
private:

	GenericNode *root;
	GenericNode *currentNode;
	std::map<std::vector<bool>, char> encodingTable;

	GenericNode* getSubTree(const std::vector<bool>& prefix) const;
	GenericNode* buildHuffmanTreeFromEncodingTable(const std::map<std::vector<bool>, char>& encodingTable) const;

	GenericNode *traverseTree(bool bit);

	// Reads and parses the file with the huffman code table and writes
	// it to the encodingTable.
	void readHuffmanCodeFile(const std::string& huffmanCodeFile);

	static std::vector<bool> getBitVector(const std::string& str, unsigned int offset) ;


public:
	HuffmanDecoder() {
		currentNode = nullptr;
		root = nullptr;
	}

	~HuffmanDecoder() {
		currentNode = nullptr;
		delete root;
	}

	/*
	 * Reads the encoding table and decodes the text file accordingly.
	 * huffmanCodeFile		The file with the huffman code
							(<character> <space> <symbol>)
	 * huffmanEncodedFile	The text file that contains the text with
							the huffman code specified in huffmanCodeFile.
	 * outFile				The file to write the original file to.
	 */
	void decode(const std::string& huffmanCodeFile, const std::string& inFileName, const std::string& outFileName);

};


#endif
