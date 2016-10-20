#include <iostream>

#include "easylogging++.h"
#include "player.h"
#include "category.h"
#include "aircraftmover.h"
#include "derivedaction.h"

Player::Player() {
    _keyBinding[sf::Keyboard::Left] = MoveLeft;
    _keyBinding[sf::Keyboard::Right] = MoveRight;
    _keyBinding[sf::Keyboard::Up] = MoveUp;
    _keyBinding[sf::Keyboard::Down] = MoveDown;
    _keyBinding[sf::Keyboard::Space] = Fire;
    _keyBinding[sf::Keyboard::M] = LaunchMissile;

    initializeActions();

    for (auto it = _actionBinding.begin(); it != _actionBinding.end(); it++) {
        it->second.category = Category::PlayerAircraft;
    }
}

void Player::initializeActions() {
//    _actionBinding[MoveLeft].action = [=] (SceneNode& node, sf::Time dt) {
//        node.move(-playerSpeed * dt.asSeconds(), 0.0f);
//    };
//
//    _actionBinding[MoveRight].action = [=] (SceneNode& node, sf::Time dt) {
//        node.move(playerSpeed * dt.asSeconds(), 0.0f);
//    };
//
//    using namespace std::placeholders;
//
//    _actionBinding[Fire].action = derivedAction<Aircraft>(std::bind(&Aircraft::fire, _1));
//    _actionBinding[LaunchMissile].action = derivedAction<Aircraft>(std::bind(&Aircraft::launchMissile, _1));

    _actionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-1, 0));
    _actionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(1, 0));
    _actionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0, -1));
    _actionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0, 1));

    _actionBinding[Fire].action = derivedAction<Aircraft>([] (Aircraft& a, sf::Time) {
        a.fire();
    });

    _actionBinding[LaunchMissile].action = derivedAction<Aircraft>([] (Aircraft& a, sf::Time) {
        a.launchMissile();
    });
}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands) {
//    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
//        Command output;
//        output.category = Category::PlayerAircraft;
//        output.action = [] (SceneNode& node, sf::Time dt) {
//            LOG(INFO) << node.getPosition().x << "," << node.getPosition().y;
//        };
//        commands.push(output);
//    }
    if (event.type == sf::Event::KeyPressed) {
        auto found = _keyBinding.find(event.key.code);
        if (found != end(_keyBinding) && isRealtimeAction(found->second)) {
            commands.push(_actionBinding[found->second]);
        }
    }
}

void Player::handleRealtimeInput(CommandQueue &commands) {
    for (auto it = _keyBinding.begin(); it != _keyBinding.end(); it++) {
        if (sf::Keyboard::isKeyPressed(it->first) && isRealtimeAction(it->second)) {
            commands.push(_actionBinding[it->second]);
        }
    }
}

void Player::removeAssignedKey(sf::Keyboard::Key key) {
    auto it = _keyBinding.find(key);
    assert(it != _keyBinding.end());

    _keyBinding.erase(it);
}

void Player::assignKey(Player::Action action, sf::Keyboard::Key key) {
    assert(_keyBinding.find(key) == _keyBinding.end());
    _keyBinding[key] = action;
}

Player::Action Player::getActionForKey(sf::Keyboard::Key key) const {
    auto it = _keyBinding.find(key);
    if (it != _keyBinding.end()) {
        return it->second;
    }
    throw std::range_error("No action for key");
}

sf::Keyboard::Key Player::getAssignedKey(Player::Action action) const {
    for (auto it = _keyBinding.begin(); it != _keyBinding.end(); it++) {
        if (it->second == action) {
            return it->first;
        }
    }
    return sf::Keyboard::Unknown;
}

bool Player::isRealtimeAction(Player::Action action) {
    switch (action) {
        case MoveLeft:
        case MoveRight:
        case MoveUp:
        case MoveDown:
        case Fire:
            return true;
        default:
            return false;
    }
}

std::string Player::actionToString(Player::Action action) {
    switch (action) {
        case MoveLeft: return "Move Left";
        case MoveRight: return "Move Right";
        case MoveUp: return "Move Up";
        case MoveDown: return "Move Down";
        default: return "Player::Action";
    }
}
