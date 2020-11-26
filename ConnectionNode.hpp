//ConnectionNode.hpp

#ifndef CONNECTION_NODE
#define CONNECTION_NODE


#include "GenericNode.hpp"
#include <unordered_map>


class ConnectionNode : public GenericNode {
private:
	GenericNode *lchild;
	GenericNode *rchild;


public:
    ConnectionNode() = delete;

    ConnectionNode(GenericNode *lchild, GenericNode *rchild) {
		if (lchild == nullptr || rchild == nullptr) {
			throw std::invalid_argument("One child was null!!");
		}

		this->lchild = lchild;
		this->rchild = rchild;
	}

	~ConnectionNode() override {
		delete lchild;
		delete rchild;
	}

	unsigned int getOccurrence() const override {
		return this->lchild->getOccurrence() + this->rchild->getOccurrence();
	}

	void getEncodingTable(const std::vector<bool> symbolVector,
						  std::unordered_map<char, std::vector<bool>> *map) const override {
		std::vector<bool> lVector(symbolVector);
		lVector.push_back(false);

		std::vector<bool> rVector(symbolVector);
		rVector.push_back(true);

		lchild->getEncodingTable(lVector, map);
		rchild->getEncodingTable(rVector, map);
	}

	GenericNode* getLeftChild() const {
		return lchild;
	}
	
	GenericNode* getRightChild() const {
		return rchild;
	}

};


#endif
