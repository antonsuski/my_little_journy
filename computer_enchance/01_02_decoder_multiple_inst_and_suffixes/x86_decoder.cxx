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
#include "x86_instruction.hxx"

#include <algorithm>
#include <array>
#include <bitset>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string_view>

struct bitset3_cmp
{
    bool operator()(const std::bitset<3>& lhs, const std::bitset<3>& rhs) const
    {
        return lhs.to_ulong() < rhs.to_ulong();
    }
};

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

const static std::map<std::bitset<3>, std::string_view, bitset3_cmp> rm_map{
    { 0b000, "bx + si" }, { 0b001, "bx + di" }, { 0b010, "bp + si" },
    { 0b011, "bp + di" }, { 0b100, "si" },      { 0b101, "di" },
    { 0b110, "bp" },      { 0b111, "bx" }
};

const static std::map<std::bitset<4>, std::string_view, bitset4_cmp>
    opcode_map_4bit{ { 0b1011, "mov" } };

const static std::map<std::bitset<6>, std::string_view, bitset6_cmp>
    opcode_map_6bit{ { 0b100010, "mov" } };

const static std::map<std::bitset<7>, std::string_view, bitset7_cmp>
    opcode_map_7bit{ { 0b1100011, "mov" },
                     { 0b1010000, "mov" },
                     { 0b1010001, "mov" } };

const static std::vector<binary_decoder::x86_instruction> opcodes{
    { 0b1011, 4, "mov" },
    { 0b100010, 6, "mov" },
    { 0b1010000, 7, "mov" },
    { 0b1010001, 7, "mov" },
    { 0b1100011, 7, "mov" }
};

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

    // Add "bits 16" for back compilation
    buffer << "bits 16" << std::endl;

    std::vector<uint8_t>::const_iterator iter;

    for (iter = instruction.begin(); iter != instruction.end(); ++iter)
    {

        std::string opcode_buffer;
        std::string destenation_buffer;
        std::string source_buffer;

        std::bitset<8> instruction_byte{};
        std::bitset<8> opcode{};
        uint8_t        disp_lo{};
        uint8_t        disp_hi{};
        std::bitset<8> data_lo{};
        std::bitset<8> data_hi{};
        int16_t        data_buffer{};
        std::bitset<1> d{};
        std::bitset<1> w{};
        std::bitset<2> mod{};
        std::bitset<3> reg{};
        std::bitset<3> rm{};
        bool           is_mod{ false };

        auto inst = std::find_if(
            opcodes.begin(), opcodes.end(),
            [&](const x86_instruction& inst)
            {
                if (inst == static_cast<unsigned int>(*iter >> 4))
                {
                    return true;
                }
                else if (inst == static_cast<unsigned int>(*iter >> 2))
                {
                    return true;
                }
                else if (inst == static_cast<unsigned int>(*iter >> 1))
                {
                    return true;
                }
                return false;
            });

        if (inst != opcodes.end())
        {
            std::cout << "find: " << *inst << std::endl;
            opcode_buffer = inst->name;

            switch (inst->byte)
            {
                case 0b100010:
                {
                    instruction_byte = *iter;
                    w                = instruction_byte.test(0);
                    d                = instruction_byte.test(1);
                    ++iter;
                    instruction_byte = *iter;
                    rm               = instruction_byte.to_ulong();
                    instruction_byte >>= rm.size();
                    reg = instruction_byte.to_ulong();
                    instruction_byte >>= reg.size();
                    mod = instruction_byte.to_ulong();

                    is_mod = true;
                }
                break;
                case 0b1011:
                {
                    instruction_byte = *iter;
                    w                = instruction_byte.test(3);
                    reg              = instruction_byte.to_ulong();

                    try
                    {
                        std::bitset<4> reg_map_key;

                        reg_map_key = w.to_ulong();
                        reg_map_key <<= reg.size();
                        reg_map_key |= reg.to_ullong();

                        destenation_buffer = reg_map.at(reg_map_key);
                    }
                    catch (const std::exception& e)
                    {
                        std::cerr << e.what() << '\n';
                    }

                    data_lo                     = *(++iter);
                    std::bitset<16> data_result = data_lo.to_ulong();

                    if (w.any())
                    {
                        data_hi             = *(++iter);
                        std::bitset<16> tmp = data_hi.to_ulong();
                        tmp <<= data_lo.size();
                        tmp |= data_lo.to_ulong();
                        data_result = tmp;
                    }
                    else if (data_lo.test(7))
                    {
                        data_result <<= data_lo.size();
                        data_result |= data_hi.to_ulong();
                    }
                    source_buffer = std::to_string(data_result.to_ulong());
                }
                break;
                case 0b1100011:
                {
                    instruction_byte = *iter;
                    w                = instruction_byte.test(0);

                    instruction_byte = *(++iter);
                    rm               = instruction_byte.to_ulong();
                    mod              = instruction_byte.to_ulong() >> 6;

                    is_mod = true;
                }
                break;
                case 0b1010000:
                    break;
                case 0b1010001:
                    break;
                default:
                    break;
            }

            // for mod 11 the r/m table is the same as reg
            if (is_mod)
            {
                std::bitset<4> reg_map_key{};
                std::bitset<4> rm_map_key{};
                reg_map_key = w.to_ulong();
                reg_map_key <<= reg.size();
                reg_map_key |= reg.to_ullong();

                rm_map_key = w.to_ulong();
                rm_map_key <<= rm.size();
                rm_map_key |= rm.to_ullong();

                std::string disp_buffer{};
                std::string sign_buffer{ " + " };
                int16_t     disp_ac_buffer{};

                switch (mod.to_ulong())
                {
                    case 0b10:
                    {
                        ++iter;
                        ++iter;
                        disp_hi        = *iter;
                        disp_ac_buffer = disp_hi;
                        disp_ac_buffer <<= 8;
                        --iter;
                        --iter;

                        if (disp_hi & 0x80)
                        {
                            sign_buffer = " - ";
                        }
                    }
                    case 0b01:
                    {
                        ++iter;
                        disp_lo = *iter;

                        if ((disp_lo & 0x80) && (mod != 0b10))
                        {
                            sign_buffer = " - ";
                            disp_ac_buffer |= static_cast<int8_t>(disp_lo) * -1;
                        }
                        else
                        {
                            disp_ac_buffer |= disp_lo;
                            disp_ac_buffer *= -1;
                        }

                        disp_buffer +=
                            sign_buffer + std::to_string(disp_ac_buffer);
                    }
                    case 0b00:
                    {
                        if (d.any())
                        {
                            destenation_buffer = reg_map.at(reg_map_key);
                            source_buffer      = rm_map.at(rm);
                            source_buffer.insert(0, "[");
                            source_buffer += disp_buffer + "]";
                        }
                        else
                        {
                            source_buffer      = reg_map.at(reg_map_key);
                            destenation_buffer = rm_map.at(rm);
                            destenation_buffer.insert(0, "[");
                            destenation_buffer += disp_buffer + "]";
                        }
                    }
                    break;
                    case 0b11:
                    {
                        try
                        {
                            if (d.any())
                            {
                                destenation_buffer = reg_map.at(reg_map_key);
                                source_buffer      = reg_map.at(rm_map_key);
                            }
                            else
                            {
                                source_buffer      = reg_map.at(reg_map_key);
                                destenation_buffer = reg_map.at(rm_map_key);
                            }
                        }
                        catch (const std::exception& e)
                        {
                            std::cerr << e.what() << '\n';
                        }
                    }
                    break;

                    default:
                        break;
                }
            }

            buffer << opcode_buffer + " " + destenation_buffer + ", " +
                          source_buffer
                   << std::endl;
        }
    }
    std::cout << buffer.str() << std::endl;
    return buffer;
}
} // namespace binary_decoder
