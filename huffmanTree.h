#pragma once
#include "huffmanNode.h"
#include "comparation.h"
#include "heap.h"

class HuffmanTree {
public:
	HuffmanTree(int* freq_table) {
		count = 0;
		root = nullptr;
		for (int i = 0; i < 128; i++) {
			if (freq_table[i] != 0) {
				count++;
			}
		}
		huffman_array = new HuffmanNode* [count];
		int n = 0;
		for (int i = 0; i < 128; i++) {
			if (freq_table[i] != 0) {
				huffman_array[n++] = new HuffmanNode((char)i, freq_table[i]);
			}
		}
	}
	~HuffmanTree()
	{
		clear();
		delete huffman_array;
		//todo
	}
	void build() {
		heap<HuffmanNode*,Comparation> minheap(huffman_array, count, 256);
		while (minheap.size() > 1) {
			//printf("minheapsize:%d\n", minheap.size());
			HuffmanNode* temp1 = minheap.removefirst();
			HuffmanNode* temp2 = minheap.removefirst();
			//printf("%d %d\n", temp1->getfreq(), temp2->getfreq());
			minheap.insert(new HuffmanNode(temp1, temp2));
		}
		root = minheap.removefirst();
		int idx = 0;
		refresh_freq_table(root,idx);
	}

	void code() {
		code_helper(root);
	}

	
	std::string& decode(std::string& huffmanseq) {
		int i = 0;
		std::string result;
		while (i < huffmanseq.size()) {
			result += decode_helper(root, huffmanseq, i);
		}
		return result;
	}

	void clear() {
		clear_helper(root);
	}

	std::string getHuffmanCode(char c) {
		for (int i = 0; i < count; i++) {
			if (huffman_array[i]->getValue() == c) return huffman_array[i]->getCode();
		}
		return "";
	}
	void print_freq_table() {
		printf("%s%10s%40s\n", "×Ö·û","Æµ¶È","»ô·òÂü±àÂë");
		print_helper(root);
	}
	void print(std::ostream& out) {
		out << "×Ö·û" << "Æµ¶È" << "»ô·òÂü±àÂë" << std::endl;
		for (int i = 0; i < count; i++) {
			HuffmanNode* node = huffman_array[i];
			out<<node->getValue()<<"   "<< node->getfreq()<<"    "<<node->getCode()<<std::endl;
		}
	}
	void refresh_freq_table(HuffmanNode* root,int& i) {
		if (root == nullptr) return;
		if (!root->isleaf()) {
			refresh_freq_table(root->getleft(),i);
			refresh_freq_table(root->getright(),i);
		}
		else {
			huffman_array[i++] = root;
		}
	}

private:
	HuffmanNode** huffman_array;
	HuffmanNode* root;
	int count;
	std::string currentPath;

	void clear_helper(HuffmanNode* node) {
		if (node == nullptr) return;
		if (!node->isleaf()) {
			clear_helper(node->getleft());
			clear_helper(node->getright());
		}
		delete node;
	}
	void code_helper(HuffmanNode* root) {
		if (root != nullptr) {
			if (!root->isleaf()) {
				currentPath += '0';
				code_helper(root->getleft());
				currentPath.pop_back();
				currentPath += '1';
				code_helper(root->getright());
				currentPath.pop_back();
			}
			else {
				root->setCode(currentPath);
				return;
			}
		}
	}
	char decode_helper(HuffmanNode* node, std::string& huffmanseq, int& i) {
		if (node->isleaf())  return node->getValue();
		if (huffmanseq[i] == '0') {
			i++;
			return decode_helper(node->getleft(), huffmanseq, i);
		}
		if (huffmanseq[i] == '1') {
			i++;
			return decode_helper(node->getright(), huffmanseq, i);
		}
	}

	void print_helper(HuffmanNode* node) {
		if (node == nullptr) return;
		if (!node->isleaf()) {
			print_helper(node->getleft());
			print_helper(node->getright());
		}
		else {
			printf("%c%10d%40s\n", node->getValue(), node->getfreq(), node->getCode().c_str());
		}
	}

};

