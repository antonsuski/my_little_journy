/**
 * @file x86_decoder.hxx
 * @author Anton Suskiy (antonsyski@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-06-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace binary_decoder
{
#define BYTE_SIZE 8

struct decoder_context
{
    bool d{ false };
    bool w{ false };
    bool mod{ false };
    bool reg{ false };
    bool rm{ false };
    bool disp{ false };

    uint8_t d_field;
    uint8_t w_field;
    uint8_t mod_field;
    uint8_t reg_field;
    uint8_t rm_field;
    uint8_t disp_field;
};

struct field
{
    enum type
    {
        none    = 0,
        op_code = 1,
        d       = 2,
        w       = 3,
        mod     = 4,
        reg     = 5,
        rm      = 6,
        disp    = 7,
    };

    type    type{};
    uint8_t bit_mask{};
    int8_t  pos{};
    int8_t  byte_pos{};
};

struct x86_instruction
{
    uint8_t            code{};
    std::string        name{};
    std::string        description{};
    std::vector<field> fields{};
};

class x86_decoder
{
public:
    x86_decoder(/* args */);
    ~x86_decoder();

    std::stringstream decode(const std::vector<uint8_t>& bytes);
};
} // namespace binary_decoder
