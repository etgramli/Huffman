//main.cpp
// Entry point for the huffmann encoder.

#include <iostream>
#include <unistd.h>

#include "HuffmanEncoder.hpp"
#include "HuffmanDecoder.hpp"

void printHelp();

int main(int argc, char* argv[]) {
	bool dFlag = false;
    bool iFlag = false;
    bool oFlag = false;
    bool cFlag = false;
    
    std::string inFilePath = "";
    std::string huffmanFilePath = "";
    std::string outFilePath = "";
    
    char optionChar;
    while( (optionChar = getopt(argc, argv, "hdi:c:o:")) != -1 ) {
        switch(optionChar) {
        case 'h':
            printHelp();
            return 0;
            break;
        case 'd':
            dFlag = true;
            break;
        case 'i':
            iFlag = true;
            inFilePath = optarg;
            break;
        case 'c':
            cFlag = true;
			huffmanFilePath = optarg;
            break;
        case 'o':
            oFlag = true;
			outFilePath = optarg;
            break;
        case '?':
            if (isprint(optopt)) {
              std::cerr << "Unknown option `-" << optopt << "'" << std::endl;
            } else {
              fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            }
        default:
            printHelp();
            return 0;
            break;
        }
    }


    if (!iFlag) {
		std::cerr << "No input file specified! Aborting." << std::endl;
		return -1;
	}
	if (cFlag) {
		// Keep the specified file name
	} else {
		huffmanFilePath = inFilePath + ".huff";
	}
	// Open the huffman code file (for input if file exists/output if file does not exist)
	if (oFlag) {
		// Keep file name to specified path
	} else {
		// Set file name to default path: <input file name>.out.txt
		outFilePath = inFilePath + ".out";
	}



	if (dFlag) {
		HuffmanDecoder huffDec;
		huffDec.decodeFile(huffmanFilePath, inFilePath, outFilePath);
	} else {

		HuffmanEncoder huffEnc;
		// Build Huffman tree & Generate encoding table
		huffEnc.buildHuffmanTree(inFilePath);

		// write encoding table to file
		huffEnc.writeHuffmanCodeToFile(huffmanFilePath);
    
		// Convert the input file to huffman code
		huffEnc.encodeFile(inFilePath, outFilePath);
    }

    return 0;
}



void printHelp() {
	std::cout << std::endl << "Tengo un ordenator portátil." << std::endl;
	std::cout << std::endl << "This program creates a Huffman code for a specified input file" << std::endl;
	std::cout << "and the encodig table in a separate file." << std::endl;
	std::cout << "Alternatively it restores the original message with the generated files." << std::endl << std::endl;
	std::cout << "-h\t\t Print this help" << std::endl;
	std::cout << "-d\t\t Decode file instead of encoding" << std::endl;
	std::cout << "-i <file>\t The file to create a Huffman Code for" << std::endl;
	std::cout << "-c <file>\t The file with the Huffman Code for the input file;" << std::endl;
	std::cout << "-o <file>\t The file to to save the Huffman Code in" << std::endl;
}
