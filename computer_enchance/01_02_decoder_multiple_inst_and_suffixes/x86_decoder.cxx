/**
 * @file x86_decoder.cxx
 * @author Anton Suskiy (antonsyski@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-06-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "x86_decoder.hxx"

#include <algorithm>
#include <iostream>

using ft = binary_decoder::filed;
std::vector<binary_decoder::x86_instruction> instructions_map{
    { 0b100010,
      "mov",
      { { ft::type::op_code, 1, 6 },
        { ft::type::d, 2, 1 },
        { ft::type::w, 3, 1 },
        { ft::type::mod, 4, 2 },
        { ft::type::reg, 5, 3 },
        { ft::type::rm, 6, 8 } } }
};

namespace binary_decoder
{
x86_decoder::x86_decoder(/* args */) {}
x86_decoder::~x86_decoder() {}

std::stringstream x86_decoder::decode(const std::vector<uint8_t>& bytes)
{
    std::stringstream decoded_instructions_buffer;

    for (auto&& i : bytes)
    {
        std::cout << std::hex << +i << " ";
        if ((i >> 2) == instructions_map[0].code)
        {
            std::cout << "r/m t/f r";
        }
        std::cout << std::endl;
    }

    return decoded_instructions_buffer;
}

} // namespace binary_decoder
