#include "kernel.h"
#include <iostream>
#include <string>
#include "huffmanTree.h"
#include <conio.h>

void process1()
{
	std::cout << "输入文件路径：" << std::endl;
	std::string path;
	std::cin >> path;
	std::ifstream src(path, std::ios::in);
	if (!src) { //打开失败
		std::cout << "文件打开失败" << std::endl;
		return;
	}
	int freq_table[128] = { 0 };
	stat(src,freq_table);
	HuffmanTree tree(freq_table);
	tree.build();
	tree.code();
	tree.print(std::cout);
}

void process2()
{
	std::cout << "输入文件路径：" << std::endl;
	std::string path;
	std::cin >> path;
	std::ifstream src(path, std::ios::in);
	if (!src) { //打开失败
		std::cout << "文件打开失败" << std::endl;
		return;
	}
	int freq_table[128] = { 0 };
	stat(src, freq_table);
	HuffmanTree tree(freq_table);
	tree.build();
	tree.code();
	tree.print(std::cout);
	std::ifstream src2(path, std::ios::in);
	std::string result;
	compress(tree,src2,result);
	std::cout << "输入编码后的文件名(.huff)：" << std::endl;
	std::string name;
	std::cin >> name;
	std::ofstream outfile;
	outfile.open(name);
	if (!outfile) { //打开失败
		std::cout << "文件打开失败" << std::endl;
		return;
	}
	outfile << result;
	outfile.close();
	outfile.open(name + ".help");
	if (!outfile) { //打开失败
		std::cout << "文件打开失败" << std::endl;
		return;
	}
	tree.print(outfile);
	std::cout << "*已保存*" << std::endl;
}

void process3()
{
	std::cout << "输入文件路径：" << std::endl;
	std::string path;
	std::cin >> path;
	std::ifstream src(path, std::ios::in);
	if (!src) { //打开失败
		std::cout << "文件打开失败" << std::endl;
		return;
	}
	std::cout << "解码中..." << std::endl;
	std::cout << "解码结果为：" << std::endl;
	std::cout << "是否另存为文本文件？（Y/N)" << std::endl;
	char choice = _getch();
	if (choice != 'y' && choice!='Y') return;
	std::cout << "请输入保存的文件名：" << std::endl;
	std::string name;
	std::cin >> name;
	std::cout << "已保存" << std::endl;
}

void compress(HuffmanTree& tree, std::ifstream& text, std::string& result) {
	std::string huffmancodeseq;
	getHuffmanCodeSeq(tree,text,huffmancodeseq);
	//std::cout << huffmancodeseq << std::endl;//debug
	tobin(huffmancodeseq,result);
}

void tobin(const std::string& seq,std::string& result) {
	char unit;
	unsigned int i = 0;
	while (i < seq.size()) {
		memset(&unit, 0, sizeof(unit));
		for (int n = 0; n < 8&&i < seq.size(); n++) {
			if (seq[i] == '1') unit |= (1 <<( 7 - n));
			i++;
		}
		result += unit;
	}
}

void getHuffmanCodeSeq(HuffmanTree& tree, std::ifstream& text,std::string& seq) {
	char c;
	while (text >> c) {
		seq += tree.getHuffmanCode(c);
		//std::cout << seq << std::endl;//debug2
	}
}
