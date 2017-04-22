//GenericNode.hpp

#ifndef GENERICNODE_H
#define GENERICNODE_H

#include <unordered_map>
#include <vector>
#include <string>


class GenericNode {

protected:
	int occurence;


public:
	virtual ~GenericNode() {};


	int getOccurence() const {
		return occurence;
	}

	virtual void getEncodingTable(const std::vector<bool> symbolVector,
								  std::unordered_map<char, std::vector<bool>> *map) const = 0;


	virtual bool operator< (const GenericNode &otherNode) const {
		return this->occurence < otherNode.getOccurence();
	}

	virtual bool operator> (const GenericNode &otherNode) const {
		return this->occurence > otherNode.getOccurence();
	}

};


#endif
