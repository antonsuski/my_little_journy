#include <iostream>

#include "xo.hxx"

int main(int, char**)
{
    std::cout << "Hello world!" << std::endl;

    game    app;
    field   game_board;
    view    surface;
    command c;

    surface.render_field(game_board);
    game_board.set_element(element::zerro, 2, 2);
    game_board.set_element(element::cross, 0, 0);
    surface.render_field(game_board);
    app.run();
    std::cin >> c;
    std::cout << static_cast<int>(c) << std::endl;

    return 0;
}
