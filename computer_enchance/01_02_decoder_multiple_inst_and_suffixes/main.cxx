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

    if (argc > 1)
    {
        const std::filesystem::path binary{ argv[1] };

        if (std::filesystem::exists(binary))
        {
            try
            {
                std::ifstream binary_file{ binary, std::ios::binary };

                std::filesystem::path out_asm_name{ binary.filename().string() +
                                                    ".asm" };
                std::fstream          out_asm_file{ out_asm_name,
                                           std::ios::out | std::ios::trunc };

                if (!binary_file)
                {
                    std::cerr << "[ERR]: Can't read the file" << std::endl;
                }

                std::vector<uint8_t> buffer(
                    std::istreambuf_iterator<char>(binary_file), {});

                for (auto&& i : buffer)
                {
                    signed char num = static_cast<signed char>(
                        std::bitset<8>{ i }.to_ulong());
                    std::cout << std::bitset<8>{ i } << " "
                              << static_cast<int>(num) << std::endl;
                }

                out_asm_file << decoder.decode(buffer).str();
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
