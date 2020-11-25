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

	std::vector<char> message;

	GenericNode* getSubTree(const std::vector<bool> prefix) const;
	GenericNode* buildHuffmanTreeFromEncodingTable(const std::map<std::vector<bool>, char> encodingTable) const;

	GenericNode *traverseTree(const bool bit);

	// Reads and parses the file with the huffman code table and writes
	// it to the encodingTable.
	void readHuffmanCodeFile(std::string huffmanCodeFile);

	std::vector<bool> getBitVector(std::string str, unsigned int offset) const;


public:
	HuffmanDecoder() {
		currentNode = nullptr;
		root = nullptr;
	}

	~HuffmanDecoder() {
		currentNode = nullptr;
		if (root != nullptr) {
			delete root;
		}
	}

	/*
	 * Reads the encoding table and decodes the text file accordingly.
	 * huffmanCodeFile		The file with the huffman code
							(<character> <space> <symbol>)
	 * huffmanEncodedFile	The text file that contains the text with
							the huffman code specified in huffmanCodeFile.
	 * outFile				The file to write the original file to.
	 */
	void decode(const std::string huffmanCodeFile,
				const std::string inFileName,
				const std::string outFileName);

};


#endif
