#pragma once
#include "huffmanNode.h"
#include "comparation.h"
#include "heap.h"
#include <iostream>

class HuffmanTree {
public:
	HuffmanTree(int* freq_table);
	~HuffmanTree();
	void build();
	void code();
	std::string& decode(std::string& huffmanseq);
	void clear();
	std::string getHuffmanCode(char c);
	void print(std::ostream& out);
	void refresh_freq_table(HuffmanNode* root, int& i);
private:
	HuffmanNode** huffman_array;
	HuffmanNode* root;
	int count;
	std::string currentPath;

	void clear_helper(HuffmanNode* node);
	void code_helper(HuffmanNode* root);
	char decode_helper(HuffmanNode* node, std::string& huffmanseq, int& i);
};

