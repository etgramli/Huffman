//ConnectionNode.hpp

#ifndef CONNECTION_NODE
#define CONNECTION_NODE


#include "GenericNode.hpp"


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

		this->occurence = this->lchild->getOccurence() + this->rchild->getOccurence();
	}

	~ConnectionNode() {
		delete lchild;
		delete rchild;
	}


	void getEncodingTable(const std::vector<bool> symbolVector,
						  std::map<char, std::vector<bool>> *map) const {
		std::vector<bool> lVector(symbolVector);
		lVector.push_back(false);

		std::vector<bool> rVector(symbolVector);
		rVector.push_back(true);

		lchild->getEncodingTable(lVector, map);
		rchild->getEncodingTable(rVector, map);
	}

};


#endif
