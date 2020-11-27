//Hnode.hpp
// A node class for the Huffman tree to determine the symbols for the characters.

#ifndef CHARNODE_H
#define CHARNODE_H

#include <unordered_map>
#include <string>

#include "GenericNode.hpp"
#include "ConnectionNode.hpp"


class CharNode : public GenericNode {
private:
	const char representedCharacter;

public:
    CharNode() = delete;

    CharNode(const char character, const unsigned int occurrence)
		: GenericNode(occurrence), representedCharacter(character) {}


	void getEncodingTable(const std::vector<bool> symbolVector,
						  std::unordered_map<char, std::vector<bool>> *map) const override {
		(*map).emplace(representedCharacter, symbolVector);
	}

	char getChar() const {
		return representedCharacter;
	}

};


#endif
