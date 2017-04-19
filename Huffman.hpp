//Huffmann.hpp

#ifndef HUFFMANENCODER_H
#define HUFFMANENCODER_H

#include <map>

#include "GenericNode.hpp"


class HuffmannEcnoder {
private:
    std::map<char, std::string> encodingTable;
    
    /*
     * Creates CharNodes for all character in the map with its occurence
     * and creates a Huffman tree according to these.
     * The root node is returned.
     */
    GenericNode* getHuffmanTree(const std::map<char, int> charOccurences);
    
    /*
     * Adds the symbols to the encoding table according to the tree
     * represented by the passed root node.
     *
     * Writes the encoding table directly to the member variable.
     */
    void addToEncodingTable(GenericNode *root);

public:
	/* First pass:
	 * Reads the input file for the first time and builds the Huffman
	 * tree accordingly.
	 * 
	 * Call this before encodeFile!!!
	 */
	void buildHuffmanTree(std::string inFileName);
	
	/*
	 * Read a file with the encoding table that was created before and
	 * saved to the drive. This replaces the call to buildHuffmanTree().
	 */
	void readHuffmanEncodingFile(std::string huffmanFileName);
	
	/*
	 * Second pass:
	 * Reads the input file again and creates the Huffman encoded
	 * message with the encoding table created by buildHuffmanTree().
	 * Writes the encoded message to the specified file.
	 * 
	 * This method assumes that buildHuffmanTree was executed before!
	 */
    void encodeFile(std::string inFileName, std::string outFileName);

	/*
	 * This writes the huffman code (built by buildHuffmanTree()) to the
	 * specified file.
	 *
	 * Like encodeFile() this method assumest that buildHuffmanTree()
	 * was called before.
	 */
	void writeHuffmanCodeToFile(std::string huffmanFileName);
};


#endif
