#include <memory>
#include <cmath>

#include "world.h"
#include "spritenode.h"


World::World(State::Context& context):
    _window(*context.window),
    _worldView(_window.getDefaultView()),
    _worldBounds(0.0f, 0.0f, _worldView.getSize().x, 2000.0f),
    _spawnPosition(_worldView.getSize().x / 2.0f, _worldBounds.height - _worldView.getSize().y),
    _playerAircraft(nullptr),
    _fonts(*context.fonts),
    _textures(*context.textures)
{
    buildScene();

    _worldView.setCenter(_spawnPosition);
}

void World::buildScene() {
    for (std::size_t i = 0; i < LayerCount; i += 1) {
        SceneNode::pointer_type layer(new SceneNode());
        _sceneLayers[i] = layer.get();

        _sceneGraph.attachChild(std::move(layer));
    }

    sf::Texture& texture = _textures.get(Textures::Desert);
    sf::IntRect textureRect(_worldBounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(_worldBounds.left, _worldBounds.top);

    _sceneLayers[Background]->attachChild(std::move(backgroundSprite));

    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, _textures, _fonts));
    _playerAircraft = leader.get();
    _playerAircraft->setPosition(_spawnPosition);
    _playerAircraft->setVelocity(40.0f, _scrollSpeed);

    _sceneLayers[Air]->attachChild(std::move(leader));

    std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, _textures, _fonts));
    leftEscort->setPosition(-80.0f, 50.0f);
    _playerAircraft->attachChild(std::move(leftEscort));

    std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, _textures, _fonts));
    rightEscort->setPosition(80.0f, 50.0f);
    _playerAircraft->attachChild(std::move(rightEscort));
}

void World::draw() {
    _window.setView(_worldView);
    _window.draw(_sceneGraph);
}

void World::update(sf::Time dt) {
    _worldView.move(0.0f, _scrollSpeed * dt.asSeconds());
    _playerAircraft->setVelocity(0.0f, 0.0f);

    while (!_commandQueue.isEmpty()) {
        _sceneGraph.onCommand(_commandQueue.pop(), dt);
    }

    sf::Vector2f velocity = _playerAircraft->getVelocity();

    if (velocity.x != 0.0f && velocity.y != 0.0f) {
        _playerAircraft->setVelocity(velocity / std::sqrt(2.0f));
    }

    _playerAircraft->accelerate(0.0f, _scrollSpeed);

    _sceneGraph.update(dt);

    sf::FloatRect viewBounds(_worldView.getCenter() - _worldView.getSize() / 2.0f, _worldView.getSize());
    const float borderDistance = 40.0f;

    sf::Vector2f position = _playerAircraft->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);

    _playerAircraft->setPosition(position);
}

CommandQueue &World::getCommandQueue() {
    return _commandQueue;
}

sf::FloatRect World::getBattlefieldBounds() const {
    sf::FloatRect bounds = _window.getDefaultView().getViewport();
    bounds.top += 128;

    return bounds;
}

void World::spawnEnemies() {
    while (!_enemySpawnPoints.empty() && _enemySpawnPoints.back().y > getBattlefieldBounds().top) {
        SpawnPoint spawn = _enemySpawnPoints.back();

        std::unique_ptr<Aircraft> enemy(new Aircraft(spawn.type, _textures, _fonts));
        enemy->setPosition(spawn.x, spawn.y);
        enemy->setRotation(180.0f);

        _sceneLayers[Air]->attachChild(std::move(enemy));

        _enemySpawnPoints.pop_back();
    }
}

void World::addEnemies() {
    addEnemy(Aircraft::Raptor, 0.0f, 500.0f);
    addEnemy(Aircraft::Avenger, -70.0f, 1400.0f);

    std::sort(_enemySpawnPoints.begin(), _enemySpawnPoints.end(),
    [] (SpawnPoint lhs, SpawnPoint rhs) {
        return lhs.y < rhs.y;
    });
}
