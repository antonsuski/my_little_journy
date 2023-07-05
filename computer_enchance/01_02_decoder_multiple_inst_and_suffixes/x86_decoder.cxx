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
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string_view>

struct bitset4_cmp
{
    bool operator()(const std::bitset<4>& lhs, const std::bitset<4>& rhs) const
    {
        return lhs.to_ulong() < rhs.to_ulong();
    }
};

struct bitset6_cmp
{
    bool operator()(const std::bitset<6>& lhs, const std::bitset<6>& rhs) const
    {
        return lhs.to_ulong() < rhs.to_ulong();
    }
};

struct bitset7_cmp
{
    bool operator()(const std::bitset<7>& lhs, const std::bitset<7>& rhs) const
    {
        return lhs.to_ulong() < rhs.to_ulong();
    }
};

const static std::map<std::bitset<4>, std::string_view, bitset4_cmp> reg_map{
    { 0b0000, "al" }, { 0b0001, "cl" }, { 0b0010, "dl" }, { 0b0011, "bl" },
    { 0b0100, "ah" }, { 0b0101, "ch" }, { 0b0110, "dh" }, { 0b0111, "bh" },
    { 0b1000, "ax" }, { 0b1001, "cx" }, { 0b1010, "dx" }, { 0b1011, "bx" },
    { 0b1100, "sp" }, { 0b1101, "bp" }, { 0b1110, "si" }, { 0b1111, "di" }
};

const static std::map<std::bitset<4>, std::string_view, bitset4_cmp>
    opcode_map_4bit{ { 0b1011, "mov" } };

const static std::map<std::bitset<6>, std::string_view, bitset6_cmp>
    opcode_map_6bit{ { 0b100010, "mov" } };

const static std::map<std::bitset<7>, std::string_view, bitset7_cmp>
    opcode_map_7bit{ { 0b1100011, "mov" },
                     { 0b1010000, "mov" },
                     { 0b1010001, "mov" } };

const static std::vector<uint8_t, std::string_view> opcodes{ { '0xB', "mov" } };

namespace binary_decoder
{
x86_decoder::x86_decoder()
{
    std::cout << __func__ << std::endl;

    std::cout << "--------------\n"
              << "[REG map]:\n";

    for (auto&& i : reg_map)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }

    std::cout << "--------------\n"
              << "[OP CODE map]:\n";
    for (auto&& i : opcode_map_6bit)
    {
        std::cout << i.first << " " << i.second << std::endl;
    }
    std::cout << "--------------\n";
}

x86_decoder::~x86_decoder()
{
    std::cout << __func__ << std::endl;
}

std::stringstream x86_decoder::decode(const std::vector<uint8_t>& instruction)
{
    std::cout << __func__ << std::endl;
    std::cout << "\n[Instructions]:\n";

    std::stringstream buffer;

    std::string opcode_buffer;
    std::string destenation_buffer;
    std::string source_buffer;

    std::bitset<8> instruction_byte{};
    std::bitset<8> opcode{};
    std::bitset<1> d{};
    std::bitset<1> w{};
    std::bitset<2> mod{};
    std::bitset<3> reg{};
    std::bitset<3> rm{};

    // Add "bits 16" for back compilation
    buffer << "bits 16" << std::endl;

    std::vector<uint8_t>::const_iterator iter;

    for (iter = instruction.begin(); iter != instruction.end(); ++iter)
    {
        instruction_byte = *iter;

        w = instruction_byte.test(0);
        d = instruction_byte.test(1);
        instruction_byte >>= 2;

        // ++iter;

        // instruction_byte = *iter;

        // rm = instruction_byte.to_ulong();
        // instruction_byte >>= rm.size();
        // reg = instruction_byte.to_ulong();
        // instruction_byte >>= reg.size();
        // mod = instruction_byte.to_ulong();

        // // for mod 11 the r/m table is the same as reg
        // if (mod == 0b11)
        // {
        //     try
        //     {
        //         std::bitset<4> reg_map_key{};
        //         std::bitset<4> rm_map_key{};

        //         opcode_buffer = opcode_map_6bit.at(opcode);

        //         reg_map_key = w.to_ulong();
        //         reg_map_key <<= reg.size();
        //         reg_map_key |= reg.to_ullong();

        //         rm_map_key = w.to_ulong();
        //         rm_map_key <<= rm.size();
        //         rm_map_key |= rm.to_ullong();

        //         if (d.any())
        //         {
        //             destenation_buffer = reg_map.at(reg_map_key);
        //             source_buffer      = reg_map.at(rm_map_key);
        //         }
        //         else
        //         {
        //             source_buffer      = reg_map.at(reg_map_key);
        //             destenation_buffer = reg_map.at(rm_map_key);
        //         }
        //     }
        //     catch (const std::exception& e)
        //     {
        //         std::cerr << e.what() << '\n';
        //     }
        // }

        // buffer << opcode_buffer + " " + destenation_buffer + ", " +
        //               source_buffer
        //        << std::endl;
    }

    // std::cout << buffer.str() << std::endl;

    return buffer;
}

} // namespace binary_decoder
