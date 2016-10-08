
#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <cstdlib>
#include <ncurses.h>

#include "../directions.h"
#include "../game.h"
#include "../windows/Window.h"
#include "Entity.h"

struct Attributes {
    uint_fast16_t ATK = 0;
    uint_fast16_t ACT = 1;
    uint_fast16_t LCK = 1;
    uint_fast16_t HP = 100;
    uint_fast16_t DF = 0;
};

class Actor : public Entity {
    public:

        Actor() {};
        Actor(Window *newW);

        // Movement
        void  moveNorth();
        void  moveNorthEast();
        void  moveEast();
        void  moveSouthEast();
        void  moveSouth();
        void  moveSouthWest();
        void  moveWest();
        void  moveNorthWest();


        // Iterators
        void  wait();
        void  tick();
        void  step();
        void  move();  // tick + step

        int   getSteps() { return steps; }
        int   getTicks() { return ticks; }

        uint_fast16_t getATK() { return attr.ATK; }
        uint_fast16_t getACT() { return attr.ACT; }
        uint_fast16_t getLCK() { return attr.LCK; }
        uint_fast16_t getHP() { return attr.HP; }
        uint_fast16_t getDF() { return attr.DF; }

    protected:
        int   steps = 0;
        int   ticks = 0;
        Attributes attr;
};

#endif

