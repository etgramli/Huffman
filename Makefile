CC=g++
CCFLAGS=-std=c++11 -Werror -Wall -pedantic
HEADERS=HuffmanEncoder.hpp HuffmanDecoder.hpp GenericNode.hpp CharNode.hpp ConnectionNode.hpp BinFileWriter.hpp BinFileReader.hpp
SOURCES=main.cpp HuffmanEncoder.cpp
ALLFILES=$(HEADERS) $(SOURCES)

huffman: $(ALLFILES)
	$(CC) $(CCFLAGS) -g $(SOURCES) -o $@

huffmanO3: $(ALLFILES)
	$(CC) $(CCFLAGS) -O3 $(SOURCES) -o $@

huffmanOs: $(ALLFILES)
	$(CC) $(CCFLAGS) -Os $(SOURCES) -o $@

huffmanClang: $(ALLFILES)
	clang++ $(CCFLAGS) $(SOURCES) -o $@

all: huffman huffmanO3 huffmanOs huffmanClang

clean:
	rm huffman huffmanO3 huffmanOs huffmanClang
