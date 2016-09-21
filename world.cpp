#include <memory>

#include "world.h"
#include "spritenode.h"


World::World(sf::RenderWindow& window):
    _window(window),
    _worldView(window.getDefaultView()),
    _worldBounds(0.0f, 0.0f, _worldView.getSize().x, 2000.0f),
    _spawnPosition(_worldView.getSize().x / 2.0f, _worldBounds.height - _worldView.getSize().y),
    _playerAircraft(nullptr)
{
    loadTextures();
    buildScene();

    _worldView.setCenter(_spawnPosition);
}

void World::loadTextures() {
    _textures.load(Textures::Eagle, "media/textures/eagle.png");
    _textures.load(Textures::Raptor, "media/textures/raptor.png");
    _textures.load(Textures::Desert, "media/textures/desert.png");
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

    std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, _textures));
    _playerAircraft = leader.get();
    _playerAircraft->setPosition(_spawnPosition);
    _playerAircraft->setVelocity(40.0f, _scrollSpeed);

    _sceneLayers[Air]->attachChild(std::move(leader));

    std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, _textures));
    leftEscort->setPosition(-80.0f, 50.0f);
    _playerAircraft->attachChild(std::move(leftEscort));

    std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, _textures));
    rightEscort->setPosition(80.0f, 50.0f);
    _playerAircraft->attachChild(std::move(rightEscort));
}

void World::draw() {
    _window.setView(_worldView);
    _window.draw(_sceneGraph);
}

void World::update(sf::Time dt) {
    _worldView.move(0.0f, _scrollSpeed * dt.asSeconds());

    sf::Vector2f position = _playerAircraft->getPosition();
    sf::Vector2f velocity = _playerAircraft->getVelocity();

    if (position.x <= _worldBounds.left + 150 || position.x >= _worldBounds.left + _worldBounds.width - 150) {
        velocity.x = -velocity.x;
        _playerAircraft->setVelocity(velocity);
    }

    while (!_commandQueue.isEmpty()) {
        _sceneGraph.onCommand(_commandQueue.pop(), dt);
    }

    _sceneGraph.update(dt);
}

CommandQueue &World::getCommandQueue() {
    return _commandQueue;
}
