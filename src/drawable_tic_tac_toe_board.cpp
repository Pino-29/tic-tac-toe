//
// Created by Roberto Jesus Garcia Pino on 22/08/25.
//

#include "drawable_tic_tac_toe_board.h"

#include "drawable_cell.h"
#include "symbol.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include <iostream>
#include <utility>

DrawableTicTacToeBoard::DrawableTicTacToeBoard()
{
}

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
            m_board[i][j] = DrawableCell(cellPosition, cellOrigin, cellSize, Symbol::None);
        }
    }
}

void DrawableTicTacToeBoard::markCell(int r, int c, Symbol symbol)
{
    assert(0 <= r && r < kRows && 0 <= c && c < kColumns);
    assert(isCellEmpty(r, c));
    m_board[r][c].setSymbol(symbol);
    --m_emptyCells;
}

bool DrawableTicTacToeBoard::isCellEmpty(int r, int c) const
{
    assert(0 <= r && r < kRows && 0 <= c && c < kColumns);
    return m_board[r][c].getSymbol() == Symbol::None;
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
    m_board[r][c].draw(window);
}

void DrawableTicTacToeBoard::drawBoardLayout(sf::RenderWindow &window)
{
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
            m_board[i][j].draw(window);
        }
    }
}

bool DrawableTicTacToeBoard::contains(const sf::Vector2f& point) const
{
    return (m_position.x + m_origin.x <= point.x && point.x  <= m_position.x + m_origin.x + m_size.x)
        && (m_position.y + m_origin.y <= point.y && point.y  <= m_position.y + m_origin.y + m_size.y);
}

std::pair<int, int> DrawableTicTacToeBoard::getCellAt(const sf::Vector2f &point) const
{
    if (!contains(point))
    {
        return {-1, -1};
    }

    const sf::Vector2f cellPosition { point - m_position };
    const sf::Vector2f cellSize     { sf::Vector2f(m_size.x / kColumns, m_size.y / kRows) };
    const int row = cellPosition.y / cellSize.x;
    const int col = cellPosition.x / cellSize.y;
    return {row, col};
}

bool DrawableTicTacToeBoard::isWinningState() const
{
    for (int r { 0 }; r < kRows; ++r)
    {
        if (isRowFull(r))
        {
            return true;
        }
    }

    for (int c { 0 }; c < kColumns; ++c)
    {
        if (isColumnFull(c))
        {
            return true;
        }
    }

    if (isDiagonalFull())
    {
        return true;
    }

    if (isAntiDiagonalFull())
    {
        return true;
    }

    return false;
}

bool DrawableTicTacToeBoard::isWinningMove(const int& r,  const int& c) const
{
    if (isRowFull(r) || isColumnFull(c))
    {
        return true;
    }

    if (r == c && isDiagonalFull())
    {
        return true;
    }

    if (r + c == kRows - 1 && isAntiDiagonalFull())
    {
        return true;
    }

    return false;
}

bool DrawableTicTacToeBoard::isFull() const
{
    return m_emptyCells == 0;
}

bool DrawableTicTacToeBoard::isRowFull(const int& r) const
{
    if (isCellEmpty(r, 0))
    {
        return false;
    }

    for (int c { 0 }; c < kColumns; ++c)
    {
        if (m_board[r][c].getSymbol() != m_board[r][0].getSymbol())
        {
            return false;
        }
    }
    return true;
}

bool DrawableTicTacToeBoard::isColumnFull(const int& c) const
{
    if (isCellEmpty(0, c))
    {
        return false;
    }

    for (int r { 0 }; r < kRows; ++r)
    {
        if (m_board[r][c].getSymbol() != m_board[0][c].getSymbol())
        {
            return false;
        }
    }

    return true;
}

bool DrawableTicTacToeBoard::isDiagonalFull() const
{
    if (isCellEmpty(0, 0))
    {
        return false;
    }

    for (int i { 0 }; i < kRows; ++i)
    {
        if (m_board[i][i].getSymbol() != m_board[0][0].getSymbol())
        {
            return false;
        }
    }

    return true;
}

bool DrawableTicTacToeBoard::isAntiDiagonalFull() const
{
    if (isCellEmpty(0, kColumns - 1))
    {
        return false;
    }

    for (int i { 0 }; i < kRows; ++i)
    {
        if (m_board[i][kColumns - 1 - i].getSymbol() != m_board[0][kColumns - 1].getSymbol())
        {
            return false;
        }
    }

    return true;
}





