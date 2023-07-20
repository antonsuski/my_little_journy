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
      {
          { ft::type::op_code, 0b11111100, 2 },
          { ft::type::d, 0b00000010, 1 },
          { ft::type::w, 0b00000001, 0 },
          { ft::type::mod, 0b11000000, 6 },
          { ft::type::reg, 0b00111000, 3 },
          { ft::type::rm, 0b00000111, 0 },
      } },
    { 0b1011'0000,
      "mov",
      "mov, i t r",
      {
          { ft::type::op_code, 0b1111'0000, 4 },
          { ft::type::w, 0b0000'1000, 3 },
          { ft::type::reg, 0b0000'0111, 0 },
          { ft::type::data, 0b1111'1111, 0 },
      } },
    // { 0b1100'0110,
    //   "mov",
    //   "mov i t r/m",
    //   {
    //       { ft::type::op_code, 0b1111'1110, 1 },
    //       { ft::type::w, 0b0000'0001, 0 },
    //       { ft::type::mod, 0b1100'0000, 6 },
    //       { ft::type::any, 0b0011'1000, 3 },
    //       { ft::type::rm, 0b0000'0111, 0 },
    //       { ft::type::data, 0b0, 0 },
    //   } },
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

    std::vector<uint8_t>::const_iterator i;

    for (i = bytes.begin(); i <= bytes.end(); ++i)
    {
        std::vector<x86_instruction>::iterator instruction =
            std::find_if(instructions_map.begin(), instructions_map.end(),
                         [&](const x86_instruction& inst) -> bool {
                             return inst.code == (*i & inst.fields[0].bit_mask);
                         });

        decoder_context context{};

        if (instruction != instructions_map.end())
        {
            uint8_t     byte_indicator{ 0b0000'0000 };
            std::string buffer{};

            for (std::vector<field>::iterator field_iter =
                     instruction->fields.begin();
                 field_iter <= instruction->fields.end(); field_iter++)
            {

                switch (field_iter->type)
                {
                    case ft::op_code:
                    {
                        context.instruction_buffer = instruction->name;
                        buffer += context.instruction_buffer;
                    }
                    break;
                    case ft::d:
                    {
                        context.d       = true;
                        context.d_field = (*i & field_iter->bit_mask);
                        context.d_field >>= field_iter->pos;
                        buffer += " d:" +
                                  std::bitset<1>{ context.d_field }.to_string();
                    }
                    break;
                    case ft::w:
                    {
                        context.w       = true;
                        context.w_field = (*i & field_iter->bit_mask);
                        context.w_field >>= field_iter->pos;
                        buffer += " w:" +
                                  std::bitset<1>{ context.w_field }.to_string();
                    }
                    break;
                    case ft::mod:
                    {
                        context.mod       = true;
                        context.mod_field = (*i & field_iter->bit_mask);
                        context.mod_field >>= field_iter->pos;
                        buffer +=
                            " mod:" +
                            std::bitset<2>{ context.mod_field }.to_string();
                    }
                    break;
                    case ft::reg:
                    {
                        context.reg       = true;
                        context.reg_field = (*i & field_iter->bit_mask);
                        context.reg_field >>= field_iter->pos;

                        uint8_t key = context.w_field;
                        key <<= 3;
                        key |= context.reg_field;
                        context.reg_buffer = regs_map[key];

                        buffer +=
                            " reg:" +
                            std::bitset<3>{ context.reg_field }.to_string();
                        buffer += " reg_buf:" + context.reg_buffer;
                    }
                    break;
                    case ft::rm:
                    {
                        context.rm       = true;
                        context.rm_field = (*i & field_iter->bit_mask);
                        context.rm_field >>= field_iter->pos;

                        buffer +=
                            " rm:" +
                            std::bitset<3>{ context.rm_field }.to_string();

                        if (context.mod)
                        {
                            uint8_t key{ context.rm_field };
                            context.rm_buffer = ef_map[key];

                            switch (context.mod_field)
                            {
                                case 0b00:
                                {
                                    if (context.rm_field == 0b110)
                                    {
                                        context.disp       = true;
                                        context.disp_h     = true;
                                        uint8_t disp_lo    = *(++i);
                                        context.disp_field = *(++i);
                                        context.disp_field <<= BYTE_SIZE;
                                        context.disp_field |= disp_lo;
                                    }
                                }
                                break;
                                case 0b01:
                                {
                                    context.disp       = true;
                                    context.disp_l     = true;
                                    context.disp_field = *(++i);
                                }
                                break;
                                case 0b10:
                                {
                                    context.disp    = true;
                                    context.disp_h  = true;
                                    uint8_t disp_lo = *(++i);
                                    context.disp_field |= *(++i);
                                    context.disp_field <<= BYTE_SIZE;
                                    context.disp_field |= disp_lo;
                                }
                                break;
                                case 0b11:
                                {
                                    uint8_t mega_key{ context.w_field };
                                    mega_key <<= 3;
                                    mega_key |= key;
                                    context.rm_buffer = regs_map[mega_key];
                                }
                                break;
                                default:
                                    break;
                            }

                            if (context.disp_h)
                            {
                                buffer += " dips:" +
                                          std::to_string(static_cast<int16_t>(
                                              context.disp_field));
                            }
                            else
                            {
                                buffer += " dips:" +
                                          std::to_string(static_cast<int8_t>(
                                              context.disp_field));
                            }
                        }

                        if ((context.disp && context.disp_field) ||
                            (!(context.rm_field & 0b100) &&
                             (context.mod_field == 0b00)))
                        {
                            context.rm_buffer.insert(0, "[");
                            context.rm_buffer.push_back(']');
                        }

                        buffer += " rm_buf:" + context.rm_buffer;
                    }
                    break;
                    case ft::data:
                    {
                        if (context.w_field)
                        {
                            context.data    = true;
                            uint8_t data_lo = *i;
                            context.data_field |= *(++i);
                            context.data_field <<= BYTE_SIZE;
                            context.data_field |= data_lo;
                        }
                        else
                        {
                            context.data       = true;
                            context.data_field = *i;
                            if (*i & 0b1000'0000)
                            {
                                context.data_field |= 0b1111'1111'0000'0000;
                            }
                        }
                        buffer += " data:" + std::to_string(context.data_field);
                    }
                    break;
                    default:
                        break;
                }

                byte_indicator |= field_iter->bit_mask;
                if (byte_indicator == 0b1111'1111 &&
                    field_iter != instruction->fields.end())
                {
                    std::cout << std::bitset<8>{ *i } << " " << buffer
                              << std::endl;
                    ++i;
                    byte_indicator = { 0b0000'0000 };
                    buffer.clear();
                }
            }
            --i;
        }
        else
        {
            std::cout << std::bitset<8>{ *i } << std::endl;
        }
        std::cout << "line: " << std::endl;
        std::memset(&context, 0U, sizeof(context));
    }

    return decoded_instructions_buffer;
}

} // namespace binary_decoder
