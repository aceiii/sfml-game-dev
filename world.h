#ifndef __WORLD_H__
#define __WORLD_H__

#include "textures.h"
#include "textureholder.h"
#include "layers.h"
#include "aircraft.h"
#include "state.h"
#include "commandqueue.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <array>


class World: sf::NonCopyable
{
public:
    struct SpawnPoint {
        Aircraft::Type type;
        float x;
        float y;

        SpawnPoint(Aircraft::Type type, float x, float y):
            type(type),x(x),y(y) {}
    };

public:
    explicit World(State::Context& context);

    void update(sf::Time deltaTime);
    void draw();

    void spawnEnemies();
    void addEnemies();

    CommandQueue& getCommandQueue();

    sf::FloatRect getBattlefieldBounds() const;

private:
    void buildScene();

private:
    sf::RenderWindow& _window;
    sf::View _worldView;
    TextureHolder& _textures;
    FontHolder& _fonts;
    SceneNode _sceneGraph;
    std::array<SceneNode*, LayerCount> _sceneLayers;

    sf::FloatRect _worldBounds;
    sf::Vector2f _spawnPosition;
    float _scrollSpeed;
    Aircraft* _playerAircraft;

    std::vector<SpawnPoint> _enemySpawnPoints;

    CommandQueue _commandQueue;
};


#endif//__WORLD_H__
