//huffmann.cpp

#include "GenericNode.hpp"
#include "CharNode.hpp"
#include "Huffman.hpp"
#include <set>
#include <map>
#include <fstream>
#include <cctype>


// Used for sorting the set of pointers
struct nodecomp {
	bool operator() (const GenericNode *lnode, const GenericNode *rnode) const {
		return (*lnode) < (*rnode);
	}
};

// Complete
void HuffmannEcnoder::buildHuffmanTree(std::string inFileName) {
	// 1: Count characters
	std::ifstream fileInput(inFileName, std::ifstream::in);

	std::map<char, int> occurence;

	char c;
	while (fileInput.get(c)) {
		if (isprint(c)) {
			if (occurence.find(c) != occurence.end()) {
				occurence[c] = occurence[c] + 1;
			} else {
				occurence.emplace(c, 1);
			}
		}
	}
	fileInput.close();


	// 2. Build Huffman tree according to the occurences
	GenericNode *root = getHuffmanTree(occurence);

	// 3. Query the symbols for all characters (to write to file later)
	addToEncodingTable(root);

	delete root;
}

void HuffmannEcnoder::addToEncodingTable(GenericNode *root) {
	root->getEncodingTable("", &encodingTable);
}

// Complete
GenericNode* HuffmannEcnoder::getHuffmanTree(std::map<char, int> charOccurences) {
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

void HuffmannEcnoder::readHuffmanEncodingFile(std::string huffmanFileName) {
	//
	std::ifstream fileInput(huffmanFileName, std::ifstream::in);

	std::string line;/*
	while ( (line = fileInput.line()) != EOF) {
		char c = line.get(0);
		int i = 0;// Get int from line
		encodingTable.insert(std::pair<char, int>(c, i));
	}*/
	
	fileInput.close();
}

// Complete
void HuffmannEcnoder::encodeFile(std::string inFileName, std::string outFileName) {
	std::ifstream fileInput(inFileName, std::ifstream::in);
	std::ofstream fileOutput(outFileName, std::ofstream::out);

	char c;
	while (fileInput.get(c)) {
		if (isprint(c)) {
			// Write the character's symbol
			fileOutput << encodingTable[c] << " ";
		}
	}

	fileInput.close();
	fileOutput.close();
}

// Complete
void HuffmannEcnoder::writeHuffmanCodeToFile(std::string huffmanFileName) {
	std::ofstream fileOutput(huffmanFileName, std::ofstream::out);

	for (std::pair<char, std::string> pair : encodingTable) {
		fileOutput << pair.first << " " << pair.second << std::endl;
	}

	fileOutput.close();
}
