#include <iostream>

#include "xo.hxx"

int main(int, char**)
{
    std::cout << "Hello world!" << std::endl;
    field game_board;
    view  surface;
    surface.render_field(game_board);
    game_board.set_element(element::zerro, 1, 0);
    game_board.set_element(element::cross, 0, 0);
    surface.render_field(game_board);
    return 0;
}
