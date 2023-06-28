#include "x86_decoder.hxx"

#include <bitset>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

int main(int argc, char const* argv[])
{
    binary_decoder::x86_decoder decoder;
    std::cout << "Hello, from decoder!" << std::endl;
    // decoder.decode_instruction({ 0x89, 0xD9 });

    if (argc > 1)
    {
        const std::filesystem::path binary{ argv[1] };

        if (std::filesystem::exists(binary))
        {
            try
            {
                std::ifstream binary_file{ binary, std::ios::binary };

                if (!binary_file)
                {
                    std::cerr << "[ERR]: Can't read the file" << std::endl;
                }

                std::vector<uint8_t> buffer(
                    std::istreambuf_iterator<char>(binary_file), {});

                for (auto&& i : buffer)
                {
                    std::cout << std::bitset<8>{ i } << " ";
                }
                std::cout << std::endl;
                decoder.decode_instruction(buffer);
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
        {
            std::cerr << "[ERR]: No such file exists: " << argv[1] << std::endl;
        }
    }

    return 0;
}
