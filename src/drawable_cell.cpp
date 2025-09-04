//
// Created by Roberto Jesus Garcia Pino on 14/08/25.
//

#include "drawable_cell.h"

#include "symbol.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Exception.hpp>

DrawableCell::DrawableCell() :
m_symbol(Symbol::None)
{
}

DrawableCell::DrawableCell(const sf::Vector2f& position, const sf::Vector2f& origin, const sf::Vector2f& size, const Symbol& symbol) :
    m_position(position),
    m_origin(origin),
    m_size(size),
    m_symbol(symbol)
{
}

void DrawableCell::setSymbol(const Symbol &symbol)
{
    assert((symbol == Symbol::X || symbol == Symbol::O) && "Symbol must be either 'X' or 'O'.");
    m_symbol = symbol;
}

Symbol DrawableCell::getSymbol() const
{
    return m_symbol;
}

void DrawableCell::setPosition(const sf::Vector2f &position)
{
    m_position = position;
}

sf::Vector2f DrawableCell::getPosition() const
{
    return m_position;
}

void DrawableCell::setOrigin(const sf::Vector2f &origin)
{
    m_origin = origin;
}

sf::Vector2f DrawableCell::getOrigin() const
{
    return m_origin;
}

void DrawableCell::setSize(const sf::Vector2f &size)
{
    m_size = size;
}

sf::Vector2f DrawableCell::getSize() const
{
    return m_size;
}


void DrawableCell::draw(sf::RenderWindow &window) const
{
    // drawBackground(window);
    switch (m_symbol)
    {
    case Symbol::X:
        drawX(window);
        break;
    case Symbol::O:
        drawO(window);
        break;
    case Symbol::None:
        // do nothing
        break;
    default:
        throw sf::Exception("Symbol must be either 'X' or 'O'.");
        break;
    }
}

void DrawableCell::drawBackground(sf::RenderWindow &window) const
{
    sf::RectangleShape background;
    background.setPosition(m_position);
    background.setOrigin(m_origin);
    background.setSize(m_size);
    background.setFillColor(sf::Color::Black);
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(1.f);
    window.draw(background);
}

void DrawableCell::drawX(sf::RenderWindow& window) const
{
    // Apply origin offset to position
    sf::Vector2f topLeft = m_origin + m_position;
    sf::Vector2f bottomRight = topLeft + m_size;
    [[maybe_unused]] sf::Vector2f topRight = topLeft + sf::Vector2f(m_size.x, 0.f);
    [[maybe_unused]] sf::Vector2f bottomLeft = topLeft + sf::Vector2f(0.f, m_size.y);

    const sf::Vertex line1[] {
        sf::Vertex(topLeft, sf::Color::Red),
        sf::Vertex(bottomRight, sf::Color::Red)
    };

    const sf::Vertex line2[] {
        sf::Vertex(topRight, sf::Color::Red),
        sf::Vertex(bottomLeft, sf::Color::Red)
    };

    window.draw(line1, 2, sf::PrimitiveType::Lines);
    window.draw(line2, 2, sf::PrimitiveType::Lines);
}

void DrawableCell::drawO(sf::RenderWindow &window) const
{
    sf::CircleShape circle(m_size.x / 2.5f);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(4.f);
    circle.setOutlineColor(sf::Color::Green);

    const sf::Vector2f center {m_position.x + m_size.x / 2.f - circle.getRadius(),
        m_position.y + m_size.y / 2.f - circle.getRadius()};
    circle.setPosition(center);

    window.draw(circle);
}
