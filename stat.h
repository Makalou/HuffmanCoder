#pragma once
#include <string>
#include <fstream>
static int freq_table[128] = { 0 };

void stat(std::ifstream& text);
void freq_table_out(std::ostream& out);