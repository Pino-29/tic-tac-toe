//
// Created by Roberto Jesus Garcia Pino on 14/08/25.
//

#ifndef TICTACTOE_CELL_H
#define TICTACTOE_CELL_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "symbol.h"

class DrawableCell
{
public:
    DrawableCell();
    DrawableCell(const sf::Vector2f& position, const sf::Vector2f& origin, const sf::Vector2f& size, const Symbol& symbol);

    void setSymbol(const Symbol& symbol);

    Symbol getSymbol() const;

    void setPosition(const sf::Vector2f& position);

    sf::Vector2f getPosition() const;

    void setOrigin(const sf::Vector2f& origin);

    sf::Vector2f getOrigin() const;

    void setSize(const sf::Vector2f& size);

    sf::Vector2f getSize() const;

    void draw(sf::RenderWindow &window) const;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_origin;
    sf::Vector2f m_size;
    Symbol       m_symbol;

    void drawBackground(sf::RenderWindow &window) const;

    void drawX(sf::RenderWindow& window) const;

    void drawO(sf::RenderWindow& window) const;
};


#endif //TICTACTOE_CELL_H