//HuffmanDecoder.cpp

#include <vector>
#include <map>


#include <iterator>
#include <string>

#include "HuffmanDecoder.hpp"
#include "BinFileReader.hpp"
#include "GenericNode.hpp"
#include "ConnectionNode.hpp"
#include "CharNode.hpp"


template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

// Generates the subtree that begins with the specified prefix
// Can be called recursively by adding a bit and generating subtrees for that
GenericNode* HuffmanDecoder::getSubTree(const std::vector<bool>& prefix) const {
	const auto low = encodingTable.lower_bound(prefix);
	const auto upper = encodingTable.upper_bound(prefix);
	if (std::distance(low, upper) == 1) {
		return new CharNode(low->second, 0);    // Occurrence does not matter here
	}
	std::vector<bool> lowerPrefix = prefix;
	lowerPrefix.push_back(false);
	
	std::vector<bool> upperPrefix = prefix;
	upperPrefix.push_back(true);

	GenericNode *leftSubtree = getSubTree(lowerPrefix);
	GenericNode *rightSubtree = getSubTree(upperPrefix);

	return new ConnectionNode(leftSubtree, rightSubtree);
}

GenericNode* HuffmanDecoder::buildHuffmanTreeFromEncodingTable(const std::map<std::vector<bool>, char>& encodingTable) const {
	if (encodingTable.empty()) {
        throw std::invalid_argument("Empty encoding table!!!");
    }
	return getSubTree(std::vector<bool>());
}

GenericNode* HuffmanDecoder::traverseTree(const bool bit) {
	if (currentNode == nullptr || instanceof<CharNode>(currentNode)) {
		currentNode = root;
	} else if (!instanceof<ConnectionNode>(currentNode)) {
		return nullptr;
	}

	auto *connNode = dynamic_cast<ConnectionNode *>(currentNode);
	// Traverse
	if (bit) {	// Right child
		currentNode = connNode->getRightChild();
	} else {	// Left child
		currentNode = connNode->getLeftChild();
	}

	return currentNode;
}

void HuffmanDecoder::decode(const std::string& huffmanCodeFile,
							const std::string& inFileName,
							const std::string& outFileName) {
	// Read encoding table and build huffman tree
	readHuffmanCodeFile(huffmanCodeFile);
	root = buildHuffmanTreeFromEncodingTable(encodingTable);

	// Process encoded file
	BinFileReader bfr(inFileName);
	std::ofstream outFile(outFileName, std::ios::out);

	for (bool bit : bfr.getMessageAsVector()) {
		GenericNode *node = traverseTree(bit);
		if (instanceof<CharNode>(node)) {
			auto *cn = dynamic_cast<CharNode *>(node);
			outFile.put(cn->getChar());
		}
	}

	outFile.close();
}


void HuffmanDecoder::readHuffmanCodeFile(const std::string& huffmanCodeFile) {
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

std::vector<bool> HuffmanDecoder::getBitVector(const std::string& str, const unsigned int offset) {
	std::vector<bool> bits;
	for (unsigned int i = offset; i < str.size(); ++i) {
        bits.push_back(str[i] != '0');
	}
	return bits;
}
