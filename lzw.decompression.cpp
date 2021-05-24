// lzw.decompression.cpp : Defines the entry point for the application.
//

#include "lzw.decompression.h"

constexpr uint8_t byte_in_bits = 8;
constexpr uint8_t half_byte_in_bits = 4;
constexpr uint8_t clear_first_half = 0x0F;

/**
 * \brief Function to read codes and decompress them by extracting codes stored in several bytes 
 * \param input_buffer 
 * \param output_buffer 
 * \param is_odd_instance 
 * \return 
 */
bool read_and_update_code(std::vector<uint8_t> input_buffer, std::vector<uint8_t> &output_buffer, bool is_odd_instance) {

	uint8_t prev_bytes[2] = {};
    std::map<int, std::string> dict;	

    for (uint8_t i = 0; i < input_buffer.size();) {
        
        uint8_t data[3];
        uint8_t code;

        data[0] = input_buffer[i];
        data[1] = input_buffer[i + 1];
        data[2] = input_buffer[i + 2];

    	if(is_odd_instance)
    	{
            prev_bytes[0] = data[1];
            prev_bytes[1] = data[2];
    	}

    	if(is_odd_instance)
    	{
            code = (static_cast<int>(data[0]) << half_byte_in_bits) | data[1] >> half_byte_in_bits;
            i += 3;
    	}
        else
        {
            code = ((prev_bytes[0] & clear_first_half) << byte_in_bits) | static_cast<int>(prev_bytes[1]);
        }
        
        output_buffer.push_back(code);

    	//Invert flag for next iteration
        is_odd_instance = !is_odd_instance;
    }
    return true;
}

int main(int argc, char* argv[])
{
	std::cout << "LZW Decompression" << std::endl;
    std::vector<uint8_t> output_buffer;
	const bool is_odd = true;

    if (argc != 3) {
        std::cerr << "Usage: ./lzw_decompression <input_file> <output_file>\n";
        return 1;
    }

	//Load file
	std::ifstream in_file(argv[1], std::ios::binary);

	// Copy all data into buffer
	const std::vector<uint8_t> input_buffer(std::istreambuf_iterator<char>(in_file), {});
	std::cout << "Input file is : " << argv[1] << std::endl;
    read_and_update_code(input_buffer, output_buffer, is_odd);

	//Write out the decompressed file
    std::ofstream out_file(argv[2]);
    for (const auto& e : output_buffer) 
        out_file << e;


    std::cout << "Decompressed file is: " << argv[2] << std::endl;
	return 0;
}
