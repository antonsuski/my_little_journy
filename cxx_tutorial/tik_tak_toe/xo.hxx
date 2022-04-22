#pragma once

#include <array>
#include <iostream>

enum class element
{
    cross,
    zerro,
    none
};

void print_element(const element& e);

class field
{
private:
    std::array<std::array<element, 3>, 3> field_data;

public:
    ~field();
    field();
    bool set_element(const element& e, const unsigned int& x_cord,
                     const unsigned int& y_cord);
    const std::array<std::array<element, 3>, 3>& get_field();
};

class view
{
public:
    void render_field(field& f);
};
