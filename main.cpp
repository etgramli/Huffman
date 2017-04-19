//main.cpp
// Entry point for the huffmann encoder.

#include <iostream>
#include <unistd.h>

#include "CharNode.hpp"
#include "ConnectionNode.hpp"
#include "Huffman.hpp"

void printHelp();

int main(int argc, char* argv[]) {
    bool iFlag = false;
    bool oFlag = false;
    bool cFlag = false;
    bool sFlag = false;
    
    std::string inFilePath = "";
    std::string huffmanFilePath = "";
    std::string outFilePath = "";
    
    char optionChar;
    while( (optionChar = getopt(argc, argv, "hi:c:o:s")) != -1 )
    {
        switch(optionChar)
        {
        case 'h':
            printHelp();
            return 0;
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
        case 's':
            sFlag = true;
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


    if (!iFlag || inFilePath.empty()) {
		std::cerr << "No input file specified! Aborting." << std::endl;
		return -1;
	}
	if (cFlag) {
		// Keep the specified file name
	} else if (!sFlag) {
		// Set the default file name
		huffmanFilePath = inFilePath + ".huff";
	}
	// Open the huffman code file (for input if file exists/output if file does not exist)
	if (oFlag) {
		// Keep file name to specified path
	} else {
		// Set file name to default path: <input file name>.out.txt
		outFilePath = inFilePath + ".out.txt";
	}


    HuffmannEcnoder huffEnc;
    // Build Huffman tree & Generate encoding table
    huffEnc.buildHuffmanTree(inFilePath);
    // write encoding table to file
    huffEnc.writeHuffmanCodeToFile(huffmanFilePath);
    
    // Convert the input file to huffman code
    huffEnc.encodeFile(inFilePath, outFilePath);
    
    
    return 0;
}

void printHelp() {
	std::cout << std::endl << "Tengo un ordenator portátil." << std::endl;
	std::cout << std::endl << "This program creates a Huffman code for a specified input file." << std::endl;
	std::cout << "If only the input is specified, it is a 2-pass coding:" << std::endl;
	std::cout << "1st is Building the Huffman tree and the 2nd is ." << std::endl;
	std::cout << "-h\t\t Print this help" << std::endl;
	std::cout << "-i <file>\t The file to create a Huffman Code for" << std::endl;
	std::cout << "-c <file>\t The file with the Huffman Code for the input file;" << std::endl;
	std::cout << "\t\t results in only the 2nd pass" << std::endl;
	std::cout << "-o <file>\t The file to to save the Huffman Code in" << std::endl;
	std::cout << "-s\t\t Silent; do not create a Huffman code file" << std::endl;
}
