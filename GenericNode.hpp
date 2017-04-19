//GenericNode.hpp

#ifndef GENERICNODE_H
#define GENERICNODE_H

#include <map>
#include <string>


class GenericNode {

protected:
	int occurence;


public:
	virtual ~GenericNode() {};


	int getOccurence() const {
		return occurence;
	}

	virtual void getEncodingTable(const std::string symbolString,
								  std::map<char, std::string> *map) const = 0;


	virtual bool operator< (const GenericNode &otherNode) const {
		return this->occurence < otherNode.getOccurence();
	}

	virtual bool operator> (const GenericNode &otherNode) const {
		return this->occurence > otherNode.getOccurence();
	}

};


#endif
