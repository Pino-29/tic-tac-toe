//
// Created by Roberto Jesus Garcia Pino on 22/08/25.
//

#ifndef TICTACTOE_DRAWABLETICTACTOEBOARD_H
#define TICTACTOE_DRAWABLETICTACTOEBOARD_H

#include "drawable_cell.h"
#include "symbol.h"

#include <SFML/Graphics/RenderWindow.hpp>

class DrawableTicTacToeBoard
{
public:
    DrawableTicTacToeBoard(sf::Vector2f position, sf::Vector2f origin, sf::Vector2f size);
    void markCell(int r, int c, Symbol symbol);
    [[nodiscard]] bool isCellEmpty(int r, int c) const;
    void draw(sf::RenderWindow &window);
    void markAndDrawCell(int r, int c, Symbol symbol, sf::RenderWindow &window);
    void drawBoardLayout(sf::RenderWindow &window);
    void drawCells(sf::RenderWindow &window);

private:
    static constexpr int kRows = 3;
    static constexpr int kColumns = 3;
    std::array<std::array<DrawableCell, kRows>, kColumns> m_board;
    sf::Vector2f m_position;
    sf::Vector2f m_origin;
    sf::Vector2f m_size;
};


#endif //TICTACTOE_DRAWABLETICTACTOEBOARD_H