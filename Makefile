CC=g++
CCFLAGS=-std=c++11 -Werror -Wall -pedantic
SOURCEFILES=main.cpp HuffmanEncoder.cpp HuffmanEncoder.hpp GenericNode.hpp CharNode.hpp ConnectionNode.hpp BinFileWriter.hpp

huffman: $(SOURCEFILES)
	$(CC) $(CCFLAGS) -g main.cpp HuffmanEncoder.cpp -o $@

huffmanO3: $(SOURCEFILES)
	$(CC) $(CCFLAGS) -O3 main.cpp HuffmanEncoder.cpp -o $@

huffmanOs: $(SOURCEFILES)
	$(CC) $(CCFLAGS) -Os main.cpp HuffmanEncoder.cpp -o $@

huffmanClang: $(SOURCEFILES)
	clang++ $(CCFLAGS) main.cpp HuffmanEncoder.cpp -o $@

all: huffman huffmanO3 huffmanOs huffmanClang

clean:
	rm huffman huffmanO3 huffmanOs huffmanClang
