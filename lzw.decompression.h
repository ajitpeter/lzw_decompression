// lzw.decompression.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <map>
#include <vector>
#include <fstream>
#include <iostream>

bool read_and_update_code(std::vector<unsigned char> input_buffer, std::vector<unsigned char>& output_buffer,
                          bool is_odd_instance);

