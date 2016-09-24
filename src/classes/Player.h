#ifndef PLAYER_H
#define PLAYER_H

#include "../game.h"
#include "Actor.h"

class Player : public Actor {
    public:
        Player(Window &w); // ctor

        void addScore(int newScore);

        int  getScore();
        void setScore(int newScore);
    private:
        int score = 0;
};

#endif

