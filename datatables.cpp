#include "datatables.h"
#include "projectile.h"

std::vector<AircraftData> initializeAircraftData() {
    std::vector<AircraftData> data(Aircraft::TypeCount);

    data[Aircraft::Eagle].hitpoints = 100;
    data[Aircraft::Eagle].speed = 200.0f;
    data[Aircraft::Eagle].texture = Textures::Eagle;

    data[Aircraft::Raptor].hitpoints = 20;
    data[Aircraft::Raptor].speed = 80.0f;
    data[Aircraft::Raptor].texture = Textures::Raptor;
    data[Aircraft::Raptor].directions.push_back(Direction(45, 80));
    data[Aircraft::Raptor].directions.push_back(Direction(-45, 160));
    data[Aircraft::Raptor].directions.push_back(Direction(45, 80));

    data[Aircraft::Avenger].hitpoints = 10;
    data[Aircraft::Avenger].speed = 120.0f;
    data[Aircraft::Avenger].texture = Textures::Avenger;
    data[Aircraft::Avenger].directions.push_back(Direction(45, 50));
    data[Aircraft::Avenger].directions.push_back(Direction(0, 50));
    data[Aircraft::Avenger].directions.push_back(Direction(-45, 100));
    data[Aircraft::Avenger].directions.push_back(Direction(0, 50));
    data[Aircraft::Avenger].directions.push_back(Direction(45, 50));

    return data;
}

std::vector<ProjectileData> initializeProjectileData() {
    std::vector<ProjectileData> data(Projectile::TypeCount);

    data[Projectile::AlliedBullet].texture = Textures::AlliedBullet;

    data[Projectile::EnemyBullet].texture = Textures::EnemyBullet;

    data[Projectile::Missile].texture = Textures::Missile;

    return data;
}

Direction::Direction(float angle, float distance):
    angle(angle),distance(distance) {
}
