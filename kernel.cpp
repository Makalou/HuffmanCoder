#include "kernel.h"
#include <iostream>

void method1()
{
	std::string path;
	std::cout << "�����ļ�·����" << std::endl;
	std::cin >> path;
	std::ifstream src(path, std::ios::in);
	if (!src) { //��ʧ��
		std::cout << "�ļ���ʧ��" << std::endl;
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
