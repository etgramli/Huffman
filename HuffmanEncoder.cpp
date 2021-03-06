//HuffmannEncoder.cpp

#include "GenericNode.hpp"
#include "CharNode.hpp"
#include "HuffmanEncoder.hpp"
#include "BinFileWriter.hpp"
#include <set>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <limits>
#include <cmath>


// Used for sorting the set of pointers
struct nodecomp {
	bool operator() (const GenericNode *lnode, const GenericNode *rnode) const {
		return (*lnode) < (*rnode);
	}
};


double HuffmanEncoder::avgCodeWordLenth(const std::unordered_map<char, unsigned int> occurences,
										unsigned int totalAmount) {
	// Calculate the average code word length
	double avgCodeWordLenth = 0.0;
	for (std::pair<char, unsigned int> pair : occurences) {
		double p = (double) pair.second / totalAmount;
		size_t length = encodingTable[pair.first].size();

		avgCodeWordLenth += p * length;
	}

	return avgCodeWordLenth;
}

double HuffmanEncoder::getEntropy(const std::unordered_map<char, unsigned int> occurrences,
								  unsigned int totalAmount) const {
	double entropy = 0.0;

	for (std::pair<char, unsigned int> pair : occurrences) {
		double p = (double)pair.second / totalAmount;
		entropy += p * log2(p);
	}

	return -entropy;
}


void HuffmanEncoder::buildHuffmanTree(const std::string inFileName) {
	std::ifstream fileInput(inFileName, std::ifstream::in);

	unsigned int totalAmount = 0;
	std::unordered_map<char, unsigned int> occurrence;

    // 1: Count characters
	char c;
	while (fileInput.get(c)) {
		++occurrence[c];
		++totalAmount;
	}
	fileInput.close();


	// 2. Build Huffman tree according to the occurences
	GenericNode *root = getHuffmanTree(occurrence);

	// 3. Query the symbols for all characters (to write to file later)
	addToEncodingTable(root);

	
	// CALCULATE AVERAGE CODE WORD LENGTH / ENTROPY
	std::cout << "Entropy:\t\t" << getEntropy(occurrence, totalAmount) << std::endl;
	std::cout << "Avg Code word length:\t" << avgCodeWordLenth(occurrence, totalAmount) << std::endl;

	delete root;
}

void HuffmanEncoder::addToEncodingTable(GenericNode *const root) {
	root->getEncodingTable(std::vector<bool>(), &encodingTable);
}

GenericNode* HuffmanEncoder::getHuffmanTree(const std::unordered_map<char, unsigned int> charOccurrences) {
	std::multiset<GenericNode *, nodecomp> forest;

	// Create a (leaf) node for all characters
	for (std::pair<char, unsigned int> pair : charOccurrences) {
		forest.insert(new CharNode(pair.first, pair.second));
	}

	// Combine two nodes with the least occurences until one remains
	while (forest.size() > 1) {
		GenericNode *lchild = *forest.begin();
		forest.erase(forest.begin());
		GenericNode *rchild = *(forest.begin());
		forest.erase(forest.begin());

		forest.insert(new ConnectionNode(lchild, rchild));
	}

	return *forest.begin(); // Return last Node = Root node
}

void HuffmanEncoder::encodeFile(const std::string inFileName, const std::string outFileName) {
	std::ifstream fileInput(inFileName, std::ifstream::in);

	BinFileWriter bfw(outFileName);


	// CALCULATE SAVED SPACE
	unsigned int originalFileBits = 0;
	unsigned int huffmanFileBits = 0;

	char c;
	while (fileInput.get(c)) {
		// Write the character's symbol
		std::vector<bool> *cBV = &encodingTable[c];
		bfw.append(cBV);
		
		originalFileBits += std::numeric_limits<unsigned char>::digits;
		huffmanFileBits += (*cBV).size();
	}

	std::cout << "out/in:\t\t\t" << (double)huffmanFileBits/originalFileBits << std::endl;
	std::cout << "in/out:\t\t\t" << (double)originalFileBits/huffmanFileBits << std::endl;

	fileInput.close();
}

void HuffmanEncoder::writeHuffmanCodeToFile(const std::string huffmanFileName) {
	std::ofstream fileOutput(huffmanFileName, std::ofstream::out);

	for (std::pair<char, std::vector<bool>> pair : encodingTable) {
		fileOutput << pair.first << " ";
		for (bool b : pair.second) {
			fileOutput << b;
		}
		fileOutput << std::endl;
	}

	fileOutput.close();
}
