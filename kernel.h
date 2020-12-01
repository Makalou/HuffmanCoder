#pragma once
#include "stat.h"
#include "huffmanTree.h"

void process1();
void process2();
void process3();
void compress(HuffmanTree& tree, std::ifstream& text, std::string& bin);
void getHuffmanCodeSeq(HuffmanTree& tree, std::ifstream& text,std::string& seq);
void tobin(const std::string& seq, std::string& result);
void toseq(const std::string& bin, std::string& result);
void extract(HuffmanTree& tree, std::ifstream& bin, std::string& text);