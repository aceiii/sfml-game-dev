#ifndef __WORLD_H__
#define __WORLD_H__

#include "textures.h"
#include "textureholder.h"
#include "layers.h"
#include "aircraft.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <array>


class World: sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow& window);

    void update(sf::Time deltaTime);
    void draw();

private:
    void loadTextures();
    void buildScene();

private:
    enum Layer
    {
        Background,
        Air,
        layerCount,
    };

private:
    sf::RenderWindow& _window;
    sf::View _worldView;
    TextureHolder _textures;
    SceneNode _sceneGraph;
    std::array<SceneNode*, LayerCount> _sceneLayers;

    sf::FloatRect _worldBounds;
    sf::Vector2f _spawnPosition;
    float _scrollSpeed;
    Aircraft* _playerAircraft;
};


#endif//__WORLD_H__
