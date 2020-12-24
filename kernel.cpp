#pragma warning(disable:4996)
#include "kernel.h"
#include <iostream>
#include <sstream>
#include <string>
#include "huffmanTree.h"
#include <conio.h>

void process1()
{
	std::cout << "�����ļ����ƣ�" << std::endl;
	std::string path;
	std::cin >> path;
	std::ifstream in(path);
	if (!in.is_open()) { //��ʧ��
		std::cout << "�ļ���ʧ��" << std::endl;
		return;
	}
	std::ostringstream tmp;
	tmp << in.rdbuf();
	std::string str = tmp.str();

	std::cout << str << std::endl;

	int freq_table[128] = { 0 };
	stat(str, freq_table);
	HuffmanTree tree(freq_table);
	tree.build();
	tree.code();
	tree.print(std::cout);
	std::cout << "�����Ƿ񱣴��ļ�(Y/N):";
	char choice = _getch();
	if (choice != 'Y' && choice != 'y') {
		return;
	}
	std::string result;
	compress(tree,str,result);
	std::cout << "\n����������ļ���(.huff)��" << std::endl;
	std::string name;
	std::cin >> name;
	std::ofstream outfile;
	outfile.open(name);
	if (!outfile) { //��ʧ��
		std::cout << "�ļ���ʧ��" << std::endl;
		return;
	}
	outfile << result;
	outfile.close();
	outfile.open(name + ".help");
	if (!outfile) { //��ʧ��
		std::cout << "�ļ���ʧ��" << std::endl;
		return;
	}
	tree.print(outfile);
	std::cout << "*�ѱ���*" << std::endl;
}

void process2()
{
	std::cout << "�����ļ����ƣ�" << std::endl;
	std::string path;
	char ch[128];
	int freq;
	int freq_table[128] = { 0 };

	char str[128];
	do {
		std::cin >> path;
	} while (path == "");
	std::cout << path << std::endl;
	FILE* fp = fopen((path + ".help").c_str(), "r+");;
	if (fp == NULL) { //��ʧ��
		std::cout << "�ļ���ʧ��" << std::endl;
		return;
	}
	else {
		while (!feof(fp)) {
			fscanf(fp, "%s\t%d\t%s\t", ch, &freq, str);
			//printf("%s\t%d\t%s\t\n", ch, freq, str);
			std::string ss(ch);
			if (ss == "\\n") {
				//std::cout << "hahahahahahahahaha";
				freq_table['\n'] = freq;
			}
			else if (ss == "space") {
				//std::cout << "hehehehehehehehhehehe";
				freq_table[' '] = freq;
			}
			else {
				freq_table[ch[0]] = freq;
			}
		}
	}
	std::ifstream in(path,std::ios::binary);
	if (!in.is_open()) { //��ʧ��
		std::cout << "�ļ���ʧ��" << std::endl;
		return;
	}
	std::ostringstream tmp;
	tmp << in.rdbuf();
	std::string bin_res = tmp.str();
	std::cout << "������..." << std::endl;
	HuffmanTree tree(freq_table);
	tree.build();
	tree.code();
	std::string seq = "";
	toseq(bin_res, seq);
	std::string result;
	tree.decode(seq, result);
	std::cout << "������Ϊ��" << std::endl;
	std::cout << result << std::endl;
	std::cout << "�Ƿ����Ϊ�ı��ļ�����Y/N)" << std::endl;
	char choice = _getch();
	if (choice != 'y' && choice!='Y') return;
	std::cout << "�����뱣����ļ�����" << std::endl;
	std::string name;
	std::cin >> name;
	std::ofstream outfile;
	outfile.open(name);
	if (!outfile) { //��ʧ��
		std::cout << "�ļ���ʧ��" << std::endl;
		return;
	}
	outfile << result;
	outfile.close();
	std::cout << "�ѱ���" << std::endl;
}

void compress(HuffmanTree& tree, std::string& text, std::string& result) {
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

void toseq(const std::string& bin, std::string& result) {
	int i = 0;
	while (i < bin.size()) {
		for (int n = 0; n < 8; n++) {
			char f = bin[i] & (1 << 7 - n);
			result += (f == 0 ? '0' : '1');
		}
		i++;
	}
}

void getHuffmanCodeSeq(HuffmanTree& tree, std::string& text,std::string& seq) {
	for (char c : text) {
		seq += tree.getHuffmanCode(c);
	}
}
