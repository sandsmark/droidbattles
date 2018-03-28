#ifndef BATTLECONFIG_H
#define BATTLECONFIG_H

#include <array>

struct BattleConfig
{
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
};

#endif // BATTLECONFIG_H
