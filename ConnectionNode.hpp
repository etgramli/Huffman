//ConnectionNode.hpp

#ifndef CONNECTION_NODE
#define CONNECTION_NODE


#include "GenericNode.hpp"
#include <unordered_map>


class ConnectionNode : public GenericNode {
private:
	GenericNode * leftChild;
	GenericNode *rightChild;


public:
    ConnectionNode() = delete;

    ConnectionNode(GenericNode *leftChild, GenericNode *rightChild) {
		if (leftChild == nullptr || rightChild == nullptr) {
			throw std::invalid_argument("One child was null!!");
		}

		this->leftChild = leftChild;
		this->rightChild = rightChild;
	}

	~ConnectionNode() override {
		delete leftChild;
		delete rightChild;
	}

	unsigned int getOccurrence() const override {
		return leftChild->getOccurrence() + rightChild->getOccurrence();
	}

	void getEncodingTable(const std::vector<bool> symbolVector,
						  std::unordered_map<char, std::vector<bool>> *map) const override {
		std::vector<bool> lVector(symbolVector);
		lVector.push_back(false);

		std::vector<bool> rVector(symbolVector);
		rVector.push_back(true);

		leftChild->getEncodingTable(lVector, map);
		rightChild->getEncodingTable(rVector, map);
	}

	GenericNode* getLeftChild() const {
		return leftChild;
	}
	
	GenericNode* getRightChild() const {
		return rightChild;
	}

};


#endif
