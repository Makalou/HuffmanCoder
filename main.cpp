#include <iostream>
#include "user_interface.h"
#include <conio.h>
#include "kernel.h"
#include <iostream>
#include <fstream>


int main()
{
	std::cout << "��ӭʹ�û�����������" << std::endl;
	while (true)
	{
		show_hint();
		char choice=_getch();
		switch (choice)
		{
		case '1':
			method1();
			break;
		case '2':
			method2();
			break;
		case '3':
			method3();
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