/***************************************************************************
                          textmodebattlearea.cpp  -  description
                             -------------------
    begin                : Fri Nov 23 2001
    copyright            : (C) 2001 by Andreas Agorander
    email                : Bluefire@bluefire.nu
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "textmodebattlearea.h"
//Added by qt3to4:
#include <QDebug>
#include <QStandardPaths>
#include <QtMath>

TextmodeBattleArea::TextmodeBattleArea()
{
}
/**
	* Constructor, inits area and starts first battle round
	*/
TextmodeBattleArea::TextmodeBattleArea(const BattleConfig &battleConfig)
{
    m_battleMode = battleConfig.mode;
    m_maxPoints = battleConfig.numFights;
    qsrand(time(nullptr)); //Initialize random seed

    m_isTeams = battleConfig.isTeams;
    m_xSize = battleConfig.xSize;
    m_ySize = battleConfig.ySize;
    ifdelete = false;

    // OPen the current config file
    m_maxRounds = battleConfig.maxRounds;
    QString confFileName = QStandardPaths::locate(QStandardPaths::AppConfigLocation, "current.cfg");

    config.load(confFileName);

    for (int i = 0; i < maxbots; i++) {
        botteams[i] = battleConfig.teams[i];
    }

    //Initialize vars
    numfights = battleConfig.numFights;
    fightsfought = 0;
    names = battleConfig.names;
    for (int x = 0; x < 8; x++) {
        fightswon[x] = 0;
        m_scorePoints[x] = 0;
    }

    startonebattle(firstrun);
}

/**
	* Destructor, deletes self
	*/
TextmodeBattleArea::~TextmodeBattleArea()
{
    int x;
    for (x = 0; x < maxobjects; x++) {
        delete objects[x];
        objects[x] = nullptr;
    }
}

/**
	* start one round of fight
	* In case this isn't the first round, deallocate previous mem
	*/
void TextmodeBattleArea::startonebattle(int y)
{
    int x;
    //If this isn't the first run, deallocate the memory
    //from the run before this
    if (y == notfirstround) {
        //Deallocate memory
        for (x = 0; x < maxobjects; x++) {
            delete objects[x];
            objects[x] = nullptr;
        }
    }

    //Randomize start positions and make sure the bots don't start to
    //close to each other
    xstarts[0] = qrand() % m_xSize;
    ystarts[0] = qrand() % m_ySize;
    for (x = 1; x < maxbots; x++) {
        int dst = minstartdistance - 1;
        int tries = 0;
        while (dst < minstartdistance && tries < 128) {
            dst = minstartdistance;
            xstarts[x] = qrand() % m_xSize;
            ystarts[x] = qrand() % m_ySize;
            for (y = 0; y < x; y++) {
                int xdiff = abs(xstarts[y] - xstarts[x]);
                int ydiff = abs(ystarts[y] - ystarts[x]);
                int tdist = int(sqrt((xdiff * xdiff) + (ydiff * ydiff)));
                if (tdist < dst) {
                    dst = tdist;
                }
            }
            tries++;
        }
    }

    //Load the bots
    QString tn;
    for (x = 0; x < maxbots; x++) {
        tn = names[x];
        if (!tn.isEmpty()) {
            objects[x] = new Robots(tn, *this, x, config, botteams[x], false, false);
        } else {
            objects[x] = new ScreenObject();
        }
    }

    //Make all other positions as "standard" screenobjects
    for (x = maxbots; x < maxobjects; x++) {
        objects[x] = new ScreenObject();
    }

    roundsrun = 0;
}

/**
	* Executed ~50 times a second (normally)
	* each time one "step" is executed in the battle
	*/

int TextmodeBattleArea::execround()
{
    //	eventH->stop( );
    int x;
    roundsrun++;
    if (roundsrun > m_maxRounds) //If the times up...
    {
        if (m_battleMode == 1 || m_battleMode == 0) {
            for (x = 0; x < maxbots; x++) {
                delete objects[x];
                objects[x] = new ScreenObject();
            }
        }
        if (m_battleMode == 2) {
            checkwin = true;
            m_maxPoints = 0;
        }
    }

    for (x = 0; x < maxobjects; x++) {
        int ifdel = objects[x]->execute(); //Let each object execute,
        //move around and things like that
        int x2;
        if (objects[x]->type() > 0) //Check If the object exists and
        { //is a "collidable" object
            for (x2 = (x + 1); x2 < maxobjects; x2++) //Loop through all possible objects
            { //(to check for collisions)

                // Also, if the objects has the same collid (and it's != 256)
                // (Eg, bullets fired by the same bot)  don't issue a collision
                if (objects[x2]->type() > 0 && ((objects[x]->collisionId() == collenabled || objects[x2]->collisionId() == collenabled) || (objects[x]->collisionId() != objects[x2]->collisionId()))) { //If object exists
                    int xx1, xx2, yy1, yy2, dist, dx, dy;

                    xx1 = objects[x]->xPos(); //
                    xx2 = objects[x2]->xPos(); // Get positions
                    dx = (xx1 - xx2) / 2; // and distances
                    yy1 = objects[x]->yPos(); // between each object
                    yy2 = objects[x2]->yPos(); //
                    dy = (yy1 - yy2) / 2; //
                    dist = int(sqrt((dx * dx) + (dy * dy))); //
                    dist *= 2;

                    if (dist < ((objects[x]->size() << 6) + (objects[x2]->size() << 6))) { //If they're bigger than their distance they have collided
                        //						int xxx;

                        int type1, type2, str1, str2;
                        type1 = objects[x]->collisionType();
                        type2 = objects[x2]->collisionType();
                        str1 = objects[x]->collisionStrength(); // Get the damage they will
                        str2 = objects[x2]->collisionStrength(); // inflict on each other
                        if (type1 == 1) // If he collided with a bot
                        {
                            objects[x2]->setSpeed(-(objects[x2]->speed() / 2));
                            double dir = objects[x2]->direction() * toradians; //Change dir
                            objects[x2]->setPosition(cos(dir) * objects[x2]->speed(),
                                                     sin(dir) * objects[x2]->speed());
                        }
                        if (type2 == 1) {
                            objects[x]->setSpeed(-(objects[x]->speed() / 2));
                            double dir = objects[x]->direction() * toradians;
                            objects[x]->setPosition(cos(dir) * objects[x]->speed(),
                                                    sin(dir) * objects[x]->speed());
                        }
                        xx1 = objects[x]->xPos(); //
                        xx2 = objects[x2]->xPos(); // Get positions
                        dx = xx1 - xx2; // and distances between
                        yy1 = objects[x]->yPos(); // each object
                        yy2 = objects[x2]->yPos(); //
                        dy = yy1 - yy2; //
                        dist = int(sqrt(dx * dx + dy * dy)); //

                        if (dist < ((objects[x]->size() << 6) + (objects[x2]->size() << 6))
                            && objects[x]->type() == ScreenObject::BotObject && objects[x2]->type() == ScreenObject::BotObject) //If they're bigger than their distance, move them apart
                        {
                            double angl = atan2(dy, dx);
                            int dst = (objects[x]->size() << 6) + (objects[x2]->size() << 6) - dist;
                            objects[x]->setPosition(cos(angl) * ((dst + 16) / 2), sin(angl) * ((dst + 16) / 2));
                            objects[x2]->setPosition(cos(angl + pi) * ((dst + 16) / 2),
                                                     sin(angl + pi) * ((dst + 16) / 2));
                        }
                        int x2owner = objects[x2]->owner();
                        if (objects[x2]->objectHit(9, str1) == 1) {
                            switch (m_battleMode) {
                            case 0:
                                delete objects[x2];
                                objects[x2] = new ScreenObject();
                                break;
                            case 1:
                                if (x < 8 && objects[x2]->type() == ScreenObject::BotObject) {
                                    fightswon[x2]++;
                                    delete objects[x2];
                                    if (fightswon[x2] < m_maxPoints) {
                                        //Calc X and Y position
                                        xstarts[x2] = qrand() % m_xSize;
                                        ystarts[x2] = qrand() % m_ySize;
                                        objects[x2] = new Robots(names[x2],
                                                                 *this, x2, config, botteams[x2], false, false);
                                        objects[x2]->objectHit(0, 0);
                                    } else {
                                        objects[x2] = new ScreenObject();
                                        fightswon[x2] = roundsrun;
                                    }
                                } else {
                                    delete objects[x2];
                                    objects[x2] = new ScreenObject();
                                }
                                break;
                            case 2: //If it's a deathmatch battle
                                if (objects[x2]->type() == ScreenObject::BotObject) {
                                    if (objects[x]->owner() < 8 && x2 != objects[x]->owner()) {
                                        fightswon[objects[x]->owner()]++;
                                    }
                                    checkwin = true;
                                    //Calc X and Y position
                                    xstarts[x2] = qrand() % m_xSize;
                                    ystarts[x2] = qrand() % m_ySize;
                                    objects[x2] = new Robots(names[x2], *this,
                                                             x2, config, botteams[x2], false, false);
                                    objects[x2]->objectHit(0, 0);
                                } else {
                                    delete objects[x2];
                                    objects[x2] = new ScreenObject();
                                }
                                break;
                            }
                        }
                        if (objects[x]->objectHit(9, str2) == 1) //If the damage killed him
                        {
                            switch (m_battleMode) {
                            case 0: //If it's a normal battle
                                delete objects[x];
                                objects[x] = new ScreenObject();
                                x2 = maxobjects;
                                continue;
                                break;
                            case 1: //If it's a survival battle
                                if (x < 8 && objects[x]->type() == ScreenObject::BotObject) {
                                    fightswon[x]++;
                                    delete objects[x];
                                    x2 = maxobjects;
                                    if (fightswon[x] < m_maxPoints) {
                                        //Calc X and Y position
                                        xstarts[x] = qrand() % m_xSize;
                                        ystarts[x] = qrand() % m_ySize;
                                        objects[x] = new Robots(names[x], *this,
                                                                x, config, botteams[x], false, false);
                                        objects[x]->objectHit(0, 0);
                                    } else {
                                        objects[x] = new ScreenObject();
                                        fightswon[x] = roundsrun;
                                    }
                                } else {
                                    delete objects[x];
                                    objects[x] = new ScreenObject();
                                    x2 = maxobjects;
                                    continue;
                                }
                                break;
                            case 2: //If it's a deathmatch battle
                                if (objects[x]->type() == ScreenObject::BotObject) {
                                    if (x2owner < 8 && x != x2owner) {
                                        fightswon[x2owner]++;
                                    }
                                    delete objects[x];
                                    x2 = maxobjects;
                                    checkwin = true;
                                    //Calc X and Y position
                                    xstarts[x] = qrand() % m_xSize;
                                    ystarts[x] = qrand() % m_ySize;
                                    objects[x] = new Robots(names[x], *this, x,
                                                            config, botteams[x], false, false);
                                    objects[x]->objectHit(0, 0);
                                } else {
                                    delete objects[x];
                                    objects[x] = new ScreenObject();
                                    x2 = maxobjects;
                                    continue;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (ifdel == -1) //If the object ordered it's own destruction
        { //Example: shot that gets outside of screen
            delete objects[x];
            objects[x] = new ScreenObject();
        }
    }

    //Here, check if the battle has ended (eg. <= 1 bot or <= 1 team is left)

    int numofbots = 0;
    int botnum;
    if (m_isTeams) //If teams
    {
        alive[0] = 0;
        alive[1] = 0;
        alive[2] = 0;
        alive[3] = 0;
        for (x = 0; x < maxbots; x++) //Mark teams with bots left
        {
            if (objects[x]->type() == ScreenObject::BotObject) {
                int yy;
                yy = objects[x]->team();
                if (yy > 3 || yy < 0) {
                    yy = 0;
                }
                alive[yy] = 1;
            }
        }
        for (x = 0; x < 4; x++) //Count them
        {
            if (alive[x] == 1) {
                numofbots++;
                botnum = x;
            }
        }
        if (numofbots <= 1) //If battle is over
        {
            if (numofbots == 1) {
                fightswon[botnum]++;
            }
            fightsfought++;
            if (fightsfought >= numfights) //If all rounds of battle is over
            {
                int winbot = 0;
                int curval = 0;
                bool draw = false;
                for (x = 0; x < maxteams; x++) {
                    if (fightswon[x] == curval) {
                        draw = true;
                    }
                    if (fightswon[x] > curval) {
                        curval = fightswon[x];
                        winbot = x;
                        draw = false;
                    }
                }
                QString msg;
                if (!draw) {
                    msg = " Team ";
                    msg += int(winbot) + '1';
                    msg += " won!";
                } else {
                    msg = "Fight was a draw";
                }
                //				ermsg->setText( msg );
                //				ermsg->setButtonText( 0, "OK" );
                //				int ret = ermsg->exec( );
                //				delete ermsg;
                //				QMessageBox::information( 0, "Fight Ended",msg );
                qDebug() << "Result: " << msg.data() << endl;
                return 3;
            }
            startonebattle(notfirstround); //If we have rounds left, continue

        } // with a new round
    }

    if (!m_isTeams && (m_battleMode == 0 || m_battleMode == 1)) {
        for (x = 0; x < maxbots; x++) {
            if (objects[x]->type() == ScreenObject::BotObject) {
                numofbots++; //Count the number of bots alive
                botnum = x;
            }
        }
        if (numofbots <= 1) //If the current fight has ended
        {
            if (numofbots == 1) { //If we have a winner ,count up his points
                fightswon[botnum]++;
            }
            fightsfought++;
            if (fightsfought >= numfights) //If we have done all the rounds of
            { // fights we should have, Determine the overall winner
                int curval = 0;
                int curval2 = 1000;
                for (x = 0; x < maxbots; x++) {
                    if (fightswon[x] > curval) {
                        curval = fightswon[x];
                    }
                    if (fightswon[x] < curval2 && names[x] != "") {
                        curval2 = fightswon[x];
                        botnum = x;
                    }
                }
                QString msg;
                if (true) {
                    switch (m_battleMode) {
                    case 0:
                        for (int xx = 0; xx < 8; xx++) {
                            if (names[xx] != "") {
                                msg += " Bot ";
                                msg += names[xx];
                                msg += " won ";
                                msg += QString::number(fightswon[xx]);
                                msg += " fights.\n";
                            }
                        }
                        break;
                    case 1:
                        msg += " Bot ";
                        msg += names[botnum];
                        msg += " won with ";
                        msg += QString::number(m_maxPoints - fightswon[botnum]);
                        msg += " lives left!\n";
                        for (int xx = 0; xx < 8; xx++) {
                            if (names[xx] != "" && xx != botnum) {
                                msg += " Bot ";
                                msg += names[xx];
                                msg += " survived ";
                                msg += QString::number(fightswon[xx]);
                                msg += " cycles.\n";
                            }
                        }
                        break;
                    }
                    //					QMessageBox::information( 0,"Fight ended",msg );
                    qDebug() << "Result: " << msg.data() << endl;
                    return 3;
                }
            } else {
                startonebattle(notfirstround); //If we have fights left,start a new
            }
        }
    }

    if (m_battleMode == 2 && checkwin) {
        checkwin = false;
        for (x = 0; x < 8; x++) {
            if (fightswon[x] >= m_maxPoints) {
                QString msg;
                for (int xx = 0; xx < 8; xx++) {
                    if (names[xx] != "") {
                        msg += " Bot ";
                        msg += names[xx];
                        msg += " got ";
                        msg += QString::number(fightswon[xx]);
                        msg += " frags.\n";
                    }
                }
                qDebug() << "Result: " << msg.data() << endl;
                return 3;
            }
        }
    }
    return 0;
}

/**
	* If a device wants to add a screenobject (as a shot) he calls
	* this function (via his bot)
	*/
void TextmodeBattleArea::addscrobject(int owner, int X, int Y, int dir, int type,
                                      int arg1, int arg2, void *arg3)
{
    int x;
    for (x = 0; x < maxobjects; x++) {
        if (objects[x]->type() == ScreenObject::Destroyed) {
            delete objects[x];
            Ram *temp3 = (Ram *)arg3;
            switch (type) {
            case 0:
                objects[x] = new ScreenObject();
                break;
            case 1:
                //					objects[x] = new robots( "unnamed.bot",*this,x );
                break;
            case 2:
                objects[x] = new Missile(X, Y, dir, arg1, x, *this, false);
                break;
            case 3:
                objects[x] = new Mine(X, Y, *this, owner, false);
                break;
            case 4:
                objects[x] = new RadarMissile(X, Y, dir, arg1, arg2, x, *this, temp3, owner, false);
                /*          ++missilesLaunched;
                          if (debugenabled && (owner==debugbot))
                            ((radarmissile*)objects[x])->createDbgWindow(missilesLaunched,
                                _dbedit, _dbl, _dbm);*/
                break;
            case 5:
                objects[x] = new Beam(X, Y, dir, arg1, *this, owner, false);
                break;
            case 6:
                objects[x] = new Rocket(X, Y, dir, arg1, x, *this, owner, false);
                break;
            case 7:
                objects[x] = new Chaff(X, Y, dir, arg1, *this, false);
                break;
            default:
                objects[x] = new ScreenObject();
            }
            break;
        }
    }
}

/**
	* If a device (as the scanner) needs info about
	* the other screenobjects it calls this function
	* (via his bot)
	*/
int TextmodeBattleArea::devio(int bot, int dev, int choice, int arg1, int arg2)
{
    Q_UNUSED(dev);

    switch (choice) {
    case 1: //getXpos
        return objects[arg1]->xPos();
        break;
    case 2: //getYpos
        return objects[arg1]->yPos();
        break;
    case 3: //getdir
        return objects[arg1]->direction();
        break;
    case 4: //getspeed
        return objects[arg1]->speed();
        break;
    case 5: //delete screenobject
        delete objects[bot];
        objects[bot] = new ScreenObject();
        break;
    case 6:
        return objects[arg1]->returnRadar();
        break;
    case 7:
        int x;
        for (x = 0; x < maxbots; x++) {
            if (objects[x]->type() == ScreenObject::BotObject && objects[x]->team() == bot && (arg2 == 255 || objects[x]->number() == arg2)) {
                objects[x]->writeRadio(arg1);
            }
        }
        break;
    case 8:
        return objects[arg1]->team();
        break;
    case 9:
        objects[bot]->objectScanned(arg1, arg2);
        break;
    case 10:
        return getareainfo(0);
        break;
    case 11:
        return getareainfo(1);
        break;
    case 12:
        return getareainfo(2);
        break;
    }
    return 0;
}

/**
	* Returns info about the battlearea
	*/
int TextmodeBattleArea::getareainfo(int choice)
{
    switch (choice) {
    case 0:
        return m_xSize;
        break;
    case 1:
        return m_ySize;
        break;
    case 2:
        return m_battleMode;
        break;
    }
    return 0;
}

/**
	* This function issues special areal (noncollision) hits.
	* The AS-rocket uses it
	*/
void TextmodeBattleArea::explosions(int x, int y, int rad, int strength, int whichobject)
{
    int X1, Y1, D1, S1, z;
    for (z = 0; z < maxbots; z++) {
        if (z == whichobject) {
            continue;
        }
        if (!objects[z]->areaExplosionAffects()) {
            continue;
        }
        X1 = objects[z]->xPos();
        Y1 = objects[z]->yPos();
        D1 = int(sqrt(((X1 - x) * (X1 - x)) + ((Y1 - y) * (Y1 - y))));
        if (D1 >= rad) {
            continue;
        }
        S1 = strength - (D1 * strength / rad);
        if (objects[z]->objectHit(9, S1) == 1) //If the damage killed him
        {
            switch (m_battleMode) {
            case 0:
                delete objects[z];
                objects[z] = new ScreenObject();
                break;
            case 1:
                if (z < 8 && objects[z]->type() == ScreenObject::BotObject) {
                    fightswon[z]++;
                    delete objects[z];
                    if (fightswon[z] < m_maxPoints) {
                        //Calc X and Y position
                        xstarts[z] = qrand() % m_xSize;
                        ystarts[z] = qrand() % m_ySize;
                        objects[z] = new Robots(names[z], *this, z,
                                                config, botteams[z], false, false);
                    } else {
                        objects[z] = new ScreenObject();
                        fightswon[z] = roundsrun;
                    }
                } else {
                    delete objects[z];
                    objects[z] = new ScreenObject();
                }
                break;
            case 2:
                int x = whichobject;
                int x2 = z;
                if (objects[x2]->type() == ScreenObject::BotObject) {
                    if (objects[x]->owner() < 8 && x2 != objects[x]->owner()) {
                        fightswon[objects[x]->owner()]++;
                    }
                    checkwin = true;
                    //Calc X and Y position
                    xstarts[x2] = qrand() % m_xSize;
                    ystarts[x2] = qrand() % m_ySize;
                    objects[x2] = new Robots(names[x2], *this, x2,
                                             config, botteams[x2], false, false);
                } else {
                    delete objects[x2];
                    objects[x2] = new ScreenObject();
                }
                break;
            }
        }
    }
}

/**
	* Gets xposition for one of the random start positions
	*/
int TextmodeBattleArea::getstartx(int bot)
{
    return xstarts[bot];
}

/**
	* Gets yposition for one o the random start positions
	*/
int TextmodeBattleArea::getstarty(int bot)
{
    return ystarts[bot];
}
