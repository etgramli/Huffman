//ConnectionNode.hpp

#ifndef CONNECTION_NODE
#define CONNECTION_NODE


#include "GenericNode.hpp"
#include <unordered_map>


class ConnectionNode : public GenericNode {
private:
	GenericNode *lchild;
	GenericNode *rchild;

	ConnectionNode() = delete;


public:
	ConnectionNode(GenericNode *lchild, GenericNode *rchild) {
		if (lchild == nullptr || rchild == nullptr) {
			throw "One child was null!!";
		}

		this->lchild = lchild;
		this->rchild = rchild;
	}

	~ConnectionNode() {
		delete lchild;
		delete rchild;
	}

	unsigned int getOccurence() const {
		return this->lchild->getOccurence() + this->rchild->getOccurence();
	}

	void getEncodingTable(const std::vector<bool> symbolVector,
						  std::unordered_map<char, std::vector<bool>> *map) const {
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
