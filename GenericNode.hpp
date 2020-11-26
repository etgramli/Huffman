//GenericNode.hpp

#ifndef GENERICNODE_H
#define GENERICNODE_H

#include <unordered_map>
#include <vector>
#include <string>


class GenericNode {

protected:
	const unsigned int occurrence;


protected:
	GenericNode() : occurrence(0) {};
	explicit GenericNode(const unsigned int occurrence) : occurrence(occurrence) {};

public:
	virtual ~GenericNode() = default;


	virtual unsigned int getOccurrence() const {
		return occurrence;
	}

	virtual void getEncodingTable(std::vector<bool> symbolVector,
								  std::unordered_map<char, std::vector<bool>> *map) const = 0;


	virtual bool operator< (const GenericNode &otherNode) const {
		return this->getOccurrence() < otherNode.getOccurrence();
	}

	virtual bool operator> (const GenericNode &otherNode) const {
		return this->getOccurrence() > otherNode.getOccurrence();
	}

};


#endif
