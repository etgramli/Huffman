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
#include <cctype>
#include <cmath>


// Used for sorting the set of pointers
struct nodecomp {
	bool operator() (const GenericNode *lnode, const GenericNode *rnode) const {
		return (*lnode) < (*rnode);
	}
};


double HuffmanEncoder::avgCodeWordLenth(const std::unordered_map<char, int> occurences,
										unsigned int totalAmount) {
	// Calculate the average code word length
	double avgCodeWordLenth = 0.0;
	for (std::pair<char, int> pair : occurences) {
		double p = (double) pair.second / totalAmount;
		size_t length = encodingTable[pair.first].size();

		avgCodeWordLenth += p * length;
	}

	return avgCodeWordLenth;
}

double HuffmanEncoder::getEntropy(const std::unordered_map<char, int> occurences,
								  unsigned int totalAmount) const {
	double entropy = 0.0;

	for (std::pair<char, int> pair : occurences) {
		double p = (double)pair.second / totalAmount;
		entropy = entropy + p * log2(p);
	}

	return -entropy;
}


void HuffmanEncoder::buildHuffmanTree(std::string inFileName) {
	// 1: Count characters
	std::ifstream fileInput(inFileName, std::ifstream::in);

	unsigned int totalAmount = 0;
	std::unordered_map<char, int> occurence;

	char c;
	while (fileInput.get(c)) {
		++occurence[c];
		++totalAmount;
	}
	fileInput.close();


	// 2. Build Huffman tree according to the occurences
	GenericNode *root = getHuffmanTree(occurence);

	// 3. Query the symbols for all characters (to write to file later)
	addToEncodingTable(root);

	
	// CALCULATE AVERAGE CODE WORD LENGTH / ENTROPY
	std::cout << "Entropy:\t\t" << getEntropy(occurence, totalAmount) << std::endl;
	std::cout << "Avg Code word length:\t" << avgCodeWordLenth(occurence, totalAmount) << std::endl;

	delete root;
}

void HuffmanEncoder::addToEncodingTable(GenericNode *root) {
	root->getEncodingTable(std::vector<bool>(), &encodingTable);
}

GenericNode* HuffmanEncoder::getHuffmanTree(std::unordered_map<char, int> charOccurences) {
	std::multiset<GenericNode *, nodecomp> forest;

	// Create a (leaf) node for all characters
	for (std::pair<char, int> pair : charOccurences) {
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

// Complete
void HuffmanEncoder::encodeFile(std::string inFileName, std::string outFileName) {
	std::ifstream fileInput(inFileName, std::ifstream::in);
	//std::ofstream fileOutput(outFileName, std::ofstream::out);

	BinFileWriter bfw(outFileName);


	// CALCULATE SAVED SAPCE
	unsigned int originalFileBits = 0;
	unsigned int huffmanFileBits = 0;

	char c;
	while (fileInput.get(c)) {
		// Write the character's symbol
		//fileOutput << encodingTable[c] << " ";
		std::vector<bool> *cBV = &encodingTable[c];
		bfw.append(*cBV);
		
		originalFileBits += std::numeric_limits<unsigned char>::digits;
		huffmanFileBits += (*cBV).size();
	}

	std::cout << "out/in:\t\t\t" << (double)huffmanFileBits/originalFileBits << std::endl;
	std::cout << "in/out:\t\t\t" << (double)originalFileBits/huffmanFileBits << std::endl;

	fileInput.close();
	//fileOutput.close();
}

void HuffmanEncoder::writeHuffmanCodeToFile(std::string huffmanFileName) {
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
