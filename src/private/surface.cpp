#include "../public/surface.h"

Surface::Surface(float width, float height, float x, float y) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Green);
}

void Surface::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Surface::checkCollision(const Player& player) {
    return shape.getGlobalBounds().intersects(player.sprite.getGlobalBounds());
}