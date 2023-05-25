#pragma once
#include "common.h"
#include "player.hpp"
#include "fann.h"

class AIPlayer1: public RandomPlayer
{
public:
    fann* q_net;
    const static unsigned int q_net_layers[];
    // void choose_task(vector<shared_ptr<Task>>&);
    AIPlayer1(Game* g, int ix);
    Card play_card(Trick t);
};