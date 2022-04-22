#include "xo.hxx"

#include <iostream>
#include <vector>

void print_element(const element& e)
{
    switch (e)
    {
        case element::cross:
            std::cout << "x";
            break;
        case element::zerro:
            std::cout << "o";
            break;
        case element::none:
            std::cout << "_";
            break;
    }
}

field::~field()
{
    std::cout << "Bye from, <field> destructor!" << std::endl;
}

field::field()
{
    std::cout << "Hello from, <field> default constractor!" << std::endl;

    for (auto& i : field_data)
    {
        for (auto& j : i)
        {
            j = element::none;
        }
    }
}

bool field::set_element(const element& e, const unsigned int& x_cord,
                        const unsigned int& y_cord)
{
    if (x_cord > 3 || y_cord > 3)
    {
        return false;
    }

    field_data[y_cord][x_cord] = e;

    return true;
}

const std::array<std::array<element, 3>, 3>& field::get_field()
{
    return field_data;
}

void view::render_field(field& f)
{
    for (const auto i : f.get_field())
    {
        for (const auto j : i)
        {
            print_element(j);
            std::cout << "|";
        }
        std::cout << std::endl;
    }
}
