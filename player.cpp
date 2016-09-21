#include <iostream>
#include "player.h"
#include "category.h"
#include "aircraftmover.h"
#include "derivedaction.h"

Player::Player() {
    _keyBinding[sf::Keyboard::Left] = MoveLeft;
    _keyBinding[sf::Keyboard::Right] = MoveRight;

    _actionBinding[MoveLeft].action = [=] (SceneNode& node, sf::Time dt) {
        node.move(-playerSpeed * dt.asSeconds(), 0.0f);
    };

    _actionBinding[MoveRight].action = [=] (SceneNode& node, sf::Time dt) {
        node.move(playerSpeed * dt.asSeconds(), 0.0f);
    };

    for (auto it = _actionBinding.begin(); it != _actionBinding.end(); it++) {
        it->second.category = Category::PlayerAircraft;
    }
}

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
    for (auto it = _keyBinding.begin(); it != _keyBinding.end(); it++) {
        if (sf::Keyboard::isKeyPressed(it->first) && isRealtimeAction(it->second)) {
            commands.push(_actionBinding[it->second]);
        }
    }
}

void Player::assignKey(Player::Action action, sf::Keyboard::Key key) {
    assert(_keyBinding.find(key) == _keyBinding.end());
    _keyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Player::Action action) const {
    for (auto it = _keyBinding.begin(); it != _keyBinding.end(); it++) {
        if (it->second == action) {
            return it->first;
        }
    }
    throw std::range_error("No key assigned to action");
}

bool Player::isRealtimeAction(Player::Action action) {
    return true;
}
