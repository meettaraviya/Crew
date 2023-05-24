#pragma once
#include "common.h"
#include "player.hpp"

class AIPlayer1: public RandomPlayer
{
public:
    // void choose_task(vector<shared_ptr<Task>>&);
    AIPlayer1(Game* g, int ix);
    ~AIPlayer1();
    Card play_card(Trick t);
};