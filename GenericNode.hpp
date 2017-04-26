//GenericNode.hpp

#ifndef GENERICNODE_H
#define GENERICNODE_H

#include <unordered_map>
#include <vector>
#include <string>


class GenericNode {

protected:
	const unsigned int occurence;


protected:
	GenericNode() : occurence(0) {};
	GenericNode(const unsigned int occurence) : occurence(occurence) {};

public:
	virtual ~GenericNode() {};


	virtual unsigned int getOccurence() const {
		return occurence;
	}

	virtual void getEncodingTable(const std::vector<bool> symbolVector,
								  std::unordered_map<char, std::vector<bool>> *map) const = 0;


	virtual bool operator< (const GenericNode &otherNode) const {
		return this->getOccurence() < otherNode.getOccurence();
	}

	virtual bool operator> (const GenericNode &otherNode) const {
		return this->getOccurence() > otherNode.getOccurence();
	}

};


#endif
