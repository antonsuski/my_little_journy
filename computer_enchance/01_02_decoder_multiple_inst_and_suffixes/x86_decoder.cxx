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
#include <bitset>
#include <cstring>
#include <iostream>
#include <map>

using ft = binary_decoder::field;

static inline std::vector<binary_decoder::x86_instruction> instructions_map{
    { 0b10001000,
      "mov",
      "mov, r/m t/f r",
      { { ft::type::op_code, 0b11111100, 2 },
        { ft::type::d, 0b00000010, 1 },
        { ft::type::w, 0b00000001, 0 },
        { ft::type::mod, 0b11000000, 6 },
        { ft::type::reg, 0b00111000, 3 },
        { ft::type::rm, 0b00000111, 0 },
        { ft::type::disp, 0b0, 0 } } },
    { 0b1011'0000,
      "mov",
      "mov, i t r",
      { { ft::type::op_code, 0b1111'0000, 4 },
        { ft::type::w, 0b0000'1000, 3 },
        { ft::type::reg, 0b0000'0111, 0 },
        { ft::type::data, 0b0, 0 } } },
    // { 0b1100'0110,
    //   "mov",
    //   "mov i t r/m",
    //   { { ft::type::op_code, 0b1111'1110, 1 },
    //     { ft::type::w, 0b0000'0001, 0 },
    //     { ft::type::mod, 0b1100'0000, 6 },
    //     { ft::type::rm, 0b0000'0111, 0 },
    //     { ft::type::disp, 0b0, 0 },
    //     { ft::type::data, 0b0, 0 } } }
};

static inline std::map<uint8_t, std::string> regs_map{
    { 0b0000, "al" }, { 0b0001, "cl" }, { 0b0010, "dl" }, { 0b0011, "bl" },
    { 0b0100, "ah" }, { 0b0101, "ch" }, { 0b0110, "dh" }, { 0b0111, "bh" },
    { 0b1000, "ax" }, { 0b1001, "cx" }, { 0b1010, "dx" }, { 0b1011, "bx" },
    { 0b1100, "sp" }, { 0b1101, "bp" }, { 0b1110, "si" }, { 0b1111, "di" },
};

// for case where mod = 11 use regs_map (the registry positions same)
static inline std::map<uint8_t, std::string> ef_map{
    { 0b0000, "bx + si" }, { 0b0001, "bx + di" }, { 0b0010, "bp + si" },
    { 0b0011, "bp + di" }, { 0b0100, "si" },      { 0b0101, "di" },
    { 0b0110, "bp" },      { 0b0111, "bx" },
};

namespace binary_decoder
{
x86_decoder::x86_decoder(/* args */) {}
x86_decoder::~x86_decoder() {}

std::stringstream x86_decoder::decode(const std::vector<uint8_t>& bytes)
{
    std::stringstream decoded_instructions_buffer;
    decoder_context   context;

    std::vector<uint8_t>::const_iterator i;

    for (i = bytes.begin(); i <= bytes.end(); ++i)
    {
        std::vector<x86_instruction>::iterator instruction =
            std::find_if(instructions_map.begin(), instructions_map.end(),
                         [&](const x86_instruction& inst) -> bool {
                             return inst.code == (*i & inst.fields[0].bit_mask);
                         });

        std::cout << std::bitset<8>{ *i } << ": ";

        if (instruction != instructions_map.end())
        {
            std::string instruction_buffer{};
            std::string destenation_buffer{};
            std::string source_buffer{};

            parse_instruction(i, instruction, context);

            std::cout << instruction->description << " ";
            // std::cout << " d: " << context.d << "/"
            //           << std::bitset<8>{ context.d_field }
            //           << " w: " << context.w << "/"
            //           << std::bitset<8>{ context.w_field }
            //           << " mod: " << context.mod << "/"
            //           << std::bitset<8>{ context.mod_field }
            //           << " reg: " << context.reg << "/"
            //           << std::bitset<8>{ context.reg_field }
            //           << " rm: " << context.rm << "/"
            //           << std::bitset<8>{ context.rm_field }
            //           << " disp: " << context.disp << "/"
            //           << std::bitset<16>{ context.disp_field };

            instruction_buffer = instruction->name;
            uint8_t key        = context.w_field;
            key <<= 3;
            key |= context.reg_field;
            context.reg_buffer = regs_map[key];

            key &= 0b1111'1000;
            key |= context.rm_field;

            if (context.mod && (context.mod_field == 0b11))
            {
                context.rm_buffer = regs_map[key];
            }
            else if (context.mod_field == 0b00 && context.rm_field == 0b110)
            {
                context.direct_addr = true;
            }
            else if (context.mod)
            {
                key &= 0b1111'0111;
                context.rm_buffer = ef_map[key];
            }

            if (context.disp && context.disp_field)
            {
                std::string sign{ " + " };
                int8_t      sign_mul{ 1 };

                if (context.direct_addr)
                {
                    context.disp_buffer += std::to_string(context.disp_field);
                }
                else if (context.disp_l)
                {
                    if ((static_cast<int8_t>(context.disp_field) < 0) &&
                        context.disp_field)
                    {
                        sign     = " - ";
                        sign_mul = -1;
                    }
                    context.disp_buffer +=
                        sign + std::to_string(static_cast<int8_t>(
                                   context.disp_field * sign_mul));
                }
                else
                {
                    if ((static_cast<int16_t>(context.disp_field) < 0) &&
                        context.disp_field)
                    {
                        sign     = " - ";
                        sign_mul = -1;
                    }
                    context.disp_buffer +=
                        sign + std::to_string(static_cast<int16_t>(
                                   context.disp_field * sign_mul));
                }
            }

            if (context.data)
            {
                context.data_buffer += std::to_string(context.data_field);
            }

            if ((source_buffer.find('+') != std::string::npos ||
                 source_buffer.find('-') != std::string::npos))
            {
                context.ef_calc = true;
            }

            if (context.ef_calc)
            {
                source_buffer.insert(0, "[");
                source_buffer += "]";
            }

            if (context.d && !context.d_field)
            {
                std::swap(source_buffer, destenation_buffer);
            }

            std::cout << std::endl
                      << context.reg_buffer + " " + context.rm_buffer + " " +
                             context.disp_buffer + " " + context.data_buffer
                      << std::endl;

            std::memset(&context, 0U, sizeof(context));
            // std::cout << std::endl
            //           << instruction_buffer + " " + destenation_buffer + " ,
            //           " +
            //                  source_buffer
            //           << std::endl;
        }
        std::cout << std::endl;
    }

    return decoded_instructions_buffer;
}

bool x86_decoder::parse_instruction(
    std::vector<uint8_t>::const_iterator&   byte_iterator,
    std::vector<x86_instruction>::iterator& instruction,
    decoder_context&                        context)
{
    uint8_t byte_indecator{ 0b0000'0000 };

    for (auto&& field : instruction->fields)
    {
        switch (field.type)
        {
            case ft::op_code:
            {
                byte_indecator |= field.bit_mask;
            }
            break;
            case ft::type::d:
            {
                context.d       = true;
                context.d_field = (*byte_iterator & field.bit_mask);
                context.d_field >>= field.pos;
                byte_indecator |= field.bit_mask;
                std::cout << " d: " << context.d << "/"
                          << std::bitset<8>{ context.d_field };
            }
            break;
            case ft::type::w:
            {
                context.w       = true;
                context.w_field = (*byte_iterator & field.bit_mask);
                context.w_field >>= field.pos;
                byte_indecator |= field.bit_mask;
                std::cout << " w: " << context.w << "/"
                          << std::bitset<8>{ context.w_field };
            }
            break;
            case ft::type::mod:
            {
                context.mod       = true;
                context.mod_field = (*byte_iterator & field.bit_mask);
                context.mod_field >>= field.pos;
                byte_indecator |= field.bit_mask;
                std::cout << " mod: " << context.mod << "/"
                          << std::bitset<8>{ context.mod_field };
            }
            break;
            case ft::type::reg:
            {
                context.reg       = true;
                context.reg_field = (*byte_iterator & field.bit_mask);
                context.reg_field >>= field.pos;
                byte_indecator |= field.bit_mask;
                std::cout << " reg: " << context.reg << "/"
                          << std::bitset<8>{ context.reg_field };
            }
            break;
            case ft::type::rm:
            {
                context.rm       = true;
                context.rm_field = (*byte_iterator & field.bit_mask);
                context.rm_field >>= field.pos;
                byte_indecator |= field.bit_mask;
                if (context.mod_field != 0b11)
                {
                    context.ef_calc = true;
                }

                std::cout << " rm: " << context.rm << "/"
                          << std::bitset<8>{ context.rm_field };
            }
            break;
            case ft::type::data:
            {
                if (context.w_field)
                {
                    uint8_t data_lo = *byte_iterator;
                    context.data_field |= *(++byte_iterator);
                    context.data_field <<= BYTE_SIZE;
                    context.data_field |= data_lo;
                }
                else
                {
                    context.data_field = *byte_iterator;
                    if (*byte_iterator & 0b1000'0000)
                    {
                        context.data_field <<= BYTE_SIZE;
                    }
                }
                context.data = true;
                std::cout << " data: " << context.data << "/"
                          << std::bitset<16>{ context.data_field };
            }
            break;
            case ft::type::disp:
            {
                switch (context.mod_field)
                {
                    break;
                    case 0b00:
                    {
                        if (context.rm && context.rm_field == 0b110)
                        {
                            context.disp    = true;
                            uint8_t disp_lo = *byte_iterator;
                            context.disp_field |= *(++byte_iterator);
                            context.disp_field <<= BYTE_SIZE;
                            context.disp_field |= disp_lo;
                            context.disp_h = true;
                            break;
                        }
                        context.disp = false;
                        byte_iterator--;
                    }
                    break;
                    case 0b01:
                    {
                        context.disp       = true;
                        context.disp_l     = true;
                        context.disp_field = *byte_iterator;
                    }
                    break;
                    case 0b10:
                    {
                        context.disp    = true;
                        uint8_t disp_lo = *byte_iterator;
                        context.disp_field |= *(++byte_iterator);
                        context.disp_field <<= BYTE_SIZE;
                        context.disp_field |= disp_lo;
                        context.disp_h = true;
                    }
                    break;
                    default:
                        byte_iterator--;
                        break;
                }
            }
            break;
            default:
                break;
        }
        if (byte_indecator == 0b1111'1111)
        {
            ++byte_iterator;
            byte_indecator = 0b0000'0000;
        }
    }
    return true;
}

} // namespace binary_decoder
