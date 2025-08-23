//
// Created by Roberto Jesus Garcia Pino on 22/08/25.
//

#include "../include/DrawableTicTacToeBoard.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "DrawableCell.h"

DrawableTicTacToeBoard::DrawableTicTacToeBoard(sf::Vector2f position, sf::Vector2f origin, sf::Vector2f size) :
m_position(position),
m_origin(origin),
m_size(size)
{
    const sf::Vector2f cellSize{sf::Vector2f(size.x / kColumns, size.y / kRows)};
    for (int i { 0 }; i < kRows; ++i)
    {
        for (int j { 0 }; j < kColumns; ++j)
        {
            sf::Vector2f cellPosition{sf::Vector2f{j * cellSize.x, i * cellSize.y} + position};
            sf::Vector2f cellOrigin{origin};
            board[i][j] = DrawableCell(cellPosition, cellOrigin, cellSize, Symbol::None);
        }
    }
}

void DrawableTicTacToeBoard::markCell(int r, int c, Symbol symbol)
{
    assert(0 <= r && r < kRows && 0 <= c && c < kColumns);
    assert(isCellEmpty(r, c));
    board[r][c].setSymbol(symbol);
}

bool DrawableTicTacToeBoard::isCellEmpty(int r, int c) const
{
    assert(0 <= r && r < kRows && 0 <= c && c < kColumns);
    return board[r][c].getSymbol() == Symbol::None;
}

void DrawableTicTacToeBoard::draw(sf::RenderWindow &window)
{
    drawBoardLayout(window);
    drawCells(window);
}

void DrawableTicTacToeBoard::markAndDrawCell(int r, int c, Symbol symbol, sf::RenderWindow &window)
{
    assert(0 <= r && r < kRows && 0 <= c && c < kColumns);
    markCell(r, c, symbol);
    board[r][c].draw(window);
}

void DrawableTicTacToeBoard::drawBoardLayout(sf::RenderWindow &window)
{
    std::cerr << "DrawableTicTacToeBoard::drawBoardLayout" << std::endl;
    constexpr float lineThickness = 4.0f;
    constexpr sf::Color lineColor = sf::Color::White;

    // Assuming boardSize is the total pixel size of the board (e.g., 300x300)
    // constexpr float boardSize = 300.0f;
    const float cellSize = m_size.x / 3.0f;

    // Vertical lines
    for (int i { 1 }; i < kColumns; ++i) {
        sf::RectangleShape verticalLine(sf::Vector2f(lineThickness, m_size.y));
        verticalLine.setFillColor(lineColor);
        verticalLine.setPosition(sf::Vector2f{i * cellSize - lineThickness / 2.0f, 0} + m_position);
        window.draw(verticalLine);
    }

    // Horizontal lines
    for (int i { 1 }; i < kRows; ++i)
    {
        sf::RectangleShape horizontalLine(sf::Vector2f(m_size.x, lineThickness));
        horizontalLine.setFillColor(lineColor);
        horizontalLine.setPosition(sf::Vector2f{ 0, i * cellSize - lineThickness / 2.0f } + m_position);
        window.draw(horizontalLine);
    }
}

void DrawableTicTacToeBoard::drawCells(sf::RenderWindow &window)
{
    for (int i { 0 }; i < kRows; ++i)
    {
        for (int j { 0 }; j < kColumns; ++j)
        {
            board[i][j].draw(window);
        }
    }
}


