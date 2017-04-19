CC=g++
CCFLAGS=-std=c++11 -Werror -Wall -pedantic
SOURCEFILES=main.cpp Huffman.cpp Huffman.hpp GenericNode.hpp CharNode.hpp ConnectionNode.hpp

huffman: $(SOURCEFILES)
	$(CC) $(CCFLAGS) -g main.cpp Huffman.cpp -o $@

huffmanO3: $(SOURCEFILES)
	$(CC) $(CCFLAGS) -O3 main.cpp Huffman.cpp -o $@

huffmanOs: $(SOURCEFILES)
	$(CC) $(CCFLAGS) -Os main.cpp Huffman.cpp -o $@

huffmanClang: $(SOURCEFILES)
	clang++ $(CCFLAGS) main.cpp Huffman.cpp -o $@

all: huffman huffmanO3 huffmanOs huffmanClang

clean:
	rm huffman huffmanO3 huffmanOs huffmanClang
