//Hnode.hpp
// A node class for the Huffman tree to determine the symbols for the characters.

#ifndef CHARNODE_H
#define CHARNODE_H

#include <map>
#include <string>

#include "GenericNode.hpp"
#include "ConnectionNode.hpp"


class CharNode : public GenericNode {
private:
	const char representedCharacter;

	CharNode() = delete;

public:
	CharNode(const char character, const int occurence): representedCharacter(character) {
		this->occurence = occurence;
	}


	void getEncodingTable(const std::string symbolString,
						  std::map<char, std::string> *map) const {
		(*map).insert(std::pair<char, std::string>(representedCharacter, symbolString));
	}

};


#endif
