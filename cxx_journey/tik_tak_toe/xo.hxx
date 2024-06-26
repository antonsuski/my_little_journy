#pragma once

#include <array>
#include <iostream>

enum class element
{
    cross,
    zerro,
    none
};

enum class command
{
    set,
    start,
    end,
    exit,
    quit,
    unknown
};

class field
{
private:
    std::array<std::array<element, 3>, 3> field_data;

public:
    ~field();
    field();
    bool set_element(const element& e, const unsigned int& x_cord,
                     const unsigned int& y_cord);
    void set_element_to_all(const element& e);
    const std::array<std::array<element, 3>, 3>& get_field();
};

class view
{
public:
    void render_field(field& f);
};

void print_element(const element& e);

std::ostream& operator<<(std::ostream& out, const element& e);
std::istream& operator>>(std::istream& in, element& e);
std::istream& operator>>(std::istream& in, command& c);

class game
{
private:
    view  surface;
    field game_board;

    bool is_game_running{ false };

public:
    void run();
};
