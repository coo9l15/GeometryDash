#include "../public/player_class.h"
#include "../public/surface.h"
#include <thread>
#include <chrono>
#include <stdexcept>

Player::Player(const std::string& textureFile) : isJumping(false), isRotating(false) {
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load player texture");
    }
    sprite.setTexture(texture);
    // Set the origin to the center of the sprite
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

void Player::jump(Surface& surface) {
    if (isJumping || surface.checkCollision(*this)) return; // Prevent jumping if already in progress
    isJumping = true;

    // Move the sprite up and rotate
    for (int i = 0; i < 40; ++i) {
        sprite.move(0, -5);
        sprite.rotate(9); // Rotate by 9 degrees each step (360 degrees / 40 steps)
        std::this_thread::sleep_for(std::chrono::milliseconds(5)); // Add a small delay
    }

    isJumping = false;
}

void Player::startRotation(float angle, int duration) {
    if (isRotating) return; // Prevent rotation if already in progress
    isRotating = true;
    std::thread(&Player::rotate, this, angle, duration).detach();
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Player::rotate(float angle, int duration) {
    int steps = duration / 10;
    float stepAngle = angle / steps;
    for (int i = 0; i < steps; ++i) {
        sprite.rotate(stepAngle);
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Add a small delay
    }
    isRotating = false;
}