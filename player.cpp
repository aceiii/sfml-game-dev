#include <iostream>
#include "player.h"
#include "category.h"
#include "aircraftmover.h"
#include "derivedaction.h"

void Player::handleEvent(const sf::Event &event, CommandQueue &commands) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
        Command output;
        output.category = Category::PlayerAircraft;
        output.action = [] (SceneNode& node, sf::Time dt) {
            std::cout << node.getPosition().x << "," << node.getPosition().y << std::endl;
        };
        commands.push(output);
    }
}

void Player::handleRealtimeInput(CommandQueue &commands) {
    const float playerSpeed = 30.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        Command moveLeft;
        moveLeft.category = Category::PlayerAircraft;
        moveLeft.action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.0f));
        commands.push(moveLeft);
    }
}
