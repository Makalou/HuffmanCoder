#pragma once
#include "huffmanNode.h"
#include "heap.h"
class Comp {

};
class HuffmanTree {
public:
	void build(HuffmanNode* array) {
		heap<HuffmanNode, Comp> minheap(array, sizeof(array)/sizeof(array[0]), 128);
		while (minheap.size() > 1) {
			HuffmanNode temp1 = minheap.removefirst();
			HuffmanNode temp2 = minheap.removefirst();
			minheap.insert(HuffmanNode(temp1, temp2));
		}
		root = &minheap.removefirst();
	}
	void code(HuffmanNode* root) {
		if (root != nullptr) {
			if (!root->isleaf()) {
				currentPath += '0';
				code(root->getleft());
				currentPath += '1';
				code(root->getright());
			}else{
				root->setCode(currentPath);
				currentPath.pop_back();
				return;
			}
		}
	}
	std::string& decode(std::string& huffmanseq) {
		int i = 0;
		std::string result;
		while (i < huffmanseq.size()) {
			result += decode_helper(root, huffmanseq, i);
		}
		return result;
	}
	char decode_helper(HuffmanNode* node, std::string& huffmanseq, int i) {
		if (node->isleaf())  return node->getValue();
		if (huffmanseq[i] == '0') return decode_helper(node->getleft(), huffmanseq, i++);
		if (huffmanseq[i] == '1') return decode_helper(node->getright(), huffmanseq, i++);
	}
	void refresh() {
		root = nullptr;
		currentPath.clear();
	}
private:
	HuffmanNode* root;
	std::string currentPath;
};
