//HuffmanDecoder.hpp

#ifndef HUFFMANDECODER_H
#define HUFFMANDECODER_H

#include "BinFileReader.hpp"


class HuffmannDecoder {
private:


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
