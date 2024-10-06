#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>
#include "../icon.h"
#include "../player.h"
#include "public/surface.h"
#include "public/player_class.h" // Include the Player class definition

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Application");

    // Load the icon image from the embedded byte array
    sf::Image icon;
    if (!icon.loadFromMemory(_Users_Avee_Documents_GeometryDash_assets_images_icon_png, sizeof(_Users_Avee_Documents_GeometryDash_assets_images_icon_png))) {
        // Handle error
        return -1;
    }

    // Set the window icon
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Create a player object
    Player player("/Users/Avee/Documents/GeometryDash/assets/images/player.png");

    // Set the initial position of the player
    player.setPosition(200, 100); // Move the player more towards the left

    // Create a surface object
    Surface surface(800, 20, 0, 550); // Width, height, x, y

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle keyboard input
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                    // Move the player sprite up in a separate thread
                    std::thread jumpThread(&Player::jump, &player, std::ref(surface));
                    jumpThread.detach(); // Detach the thread to allow it to run independently
                }
            }
        }

        // Check for collision with the surface
        if (surface.checkCollision(player)) {
            player.collision = 1;
        } else {
            player.collision = 0;
        }

        if (player.collision == 0) player.sprite.move(0, player.gravity);

        window.clear();
        surface.draw(window);
        player.draw(window);
        window.display();

        // Debugging: Print the player's position
        sf::Vector2f position = player.sprite.getPosition();
        std::cout << "Player position: (" << position.x << ", " << position.y << ")" << std::endl;
    }

    return 0;
}