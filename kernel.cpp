#include "kernel.h"
#include <iostream>
#include <string>

void method1()
{
	std::string path;
	std::cout << "输入文件路径：" << std::endl;
	std::cin >> path;
	std::ifstream src(path, std::ios::in);
	if (!src) { //打开失败
		std::cout << "文件打开失败" << std::endl;
		return;
	}
	stat(src);
	freq_table_out(std::cout);
}

void method2()
{

}

void method3()
{

}

std::string& compress(std::string& text) {
	std::string result;
	std::string huffmancodeseq;
	huffmancodeseq = getHuffmanCodeSeq(text);
	tobin(huffmancodeseq,result);
	return result;
}

void tobin(const std::string& seq,std::string& result) {
	char unit;
	std::string buf;
	unsigned int i = 0;
	while (i < seq.size()) {
		memset(&unit, 0, sizeof(unit));
		for (int n = 0; n < 8; n++) {
			if (seq[i] == '1') unit |= (1 <<( 7 - n));
			i++;
		}
		buf += unit;
	}
	result = buf;
}

std::string& getHuffmanCodeSeq(std::string& text) {
	std::string seq;
	for (auto& c : text) {
		seq += getHuffmanCode(c);
	}
	return seq;
}
