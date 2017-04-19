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


	void getEncodingTable(const std::string symbolString,
						  std::map<char, std::string> *map) const {
		lchild->getEncodingTable(symbolString + "0", map);
		rchild->getEncodingTable(symbolString + "1", map);
	}

};


#endif
