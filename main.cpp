#include <iostream>
#include "user_interface.h"
#include <conio.h>
#include "kernel.h"


int main()
{
	std::cout << "»¶Ó­Ê¹ÓÃ»ô·òÂü±àÂëÆ÷" << std::endl;
	std::string r;
	while (true)
	{
		show_hint();
		char choice=_getch();
		switch (choice)
		{
		case '1':
			process1();
			break;
		case '2':
			process2();
			break;
		case '3':
			process3();
			break;
		case '4':
			goto END;
		default:
			break;
		}
	}
END:
	return 0;
}