#ifndef BATTLECONFIG_H
#define BATTLECONFIG_H

#include <array>
#include <memory>
#include <random>

struct BattleConfig
{
    static std::random_device seedingDevice;

    enum FightMode {
        Normal = 0,
        Survival = 1,
        Deathmatch = 2
    };

    std::array<QString, 8> names;
    int xSize = 32768, ySize = 32768;
    bool isTeams = false;
    bool isTournament = false;
    int mode = Normal;
    int maxRounds = 6000;
    int maxPoints = 10;
    int numFights = 1;
    std::array<int, 8> teams = { 0 };
    bool fastMode = false;
    bool debugMode = false;

    std::random_device::result_type random_seed;
};

#endif // BATTLECONFIG_H
