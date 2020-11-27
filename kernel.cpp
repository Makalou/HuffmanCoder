#include "kernel.h"
#include <iostream>

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
