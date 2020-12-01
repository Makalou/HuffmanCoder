#include "stat.h"
#include <iostream>

void stat(std::ifstream& text,int *freq_table) {
	memset(freq_table, 0, sizeof(freq_table));
	char c;
	while (text >> c) {
		freq_table[c]++;
	}
}