#include "stat.h"
#include <iostream>

void stat(std::ifstream& text) {
	memset(freq_table, 0, sizeof(freq_table));
	char c;
	while(text>>c)
		freq_table[c]++;
}

void freq_table_out(std::ostream& out) {
	for (int i=0; i < 128; i++) {
		if (freq_table[i] != 0) out << (char)i << ":" << freq_table[i] << std::endl;
	}
}