#include <string>
#include "category.h"

namespace Category
{
    std::string toString(Type category) {
        if (category == None) {
            return "None";
        } else if (category == Scene) {
            return "Scene";
        } else if (category == SceneAirLayer) {
            return "SceneAirLayer";
        } else if (category == PlayerAircraft) {
            return "PlayerAircraft";
        } else if (category == AlliedAircraft) {
            return "AlliedAircraft";
        } else if (category == EnemyAircraft) {
            return "EnemyAircraft";
        } else if (category == AlliedProjectile) {
            return "AlliedProject";
        } else if (category == EnemyProjectile) {
            return "EnemyProjectile";
        } else if (category == Pickup) {
            return "Pickup";
        } else if (category == Projectile) {
            return "Projectile";
        }
        return "Unknown";
    }

    std::string toString(const int category) {
        return toString(static_cast<Type>(category));
    }
}
