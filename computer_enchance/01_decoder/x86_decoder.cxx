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

#include <bitset>
#include <iostream>
#include <map>
#include <string_view>

const static std::map<std::bitset<4>, std::string_view> reg_map{
    { 0b0000, "al" }, { 0b0001, "cl" }, { 0b0010, "dl" }, { 0b0011, "bl" },
    { 0b0100, "ah" }, { 0b0101, "ch" }, { 0b0110, "dh" }, { 0b0111, "bh" },
    { 0b1000, "ax" }, { 0b1001, "cx" }, { 0b1010, "dx" }, { 0b1011, "bx" },
    { 0b1100, "sp" }, { 0b1101, "bp" }, { 0b1110, "si" }, { 0b1111, "di" }
};

namespace binary_decoder
{
x86_decoder::x86_decoder()
{
    std::cout << "x86_decoder constructor" << std::endl;
}

x86_decoder::~x86_decoder()
{
    std::cout << "x86_decoder destructor" << std::endl;
}

void x86_decoder::decode_instruction(std::vector<uint8_t> instruction)
{
    std::cout << __func__ << std::endl;
    std::cout << "trying get access to each byte\n";
    for (auto&& i : instruction)
    {
        std::cout << std::hex << static_cast<int>(i) << std::endl;
    }

    for (auto&& i : reg_map)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }
}

} // namespace binary_decoder
