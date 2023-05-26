#pragma once
#include "common.h"

class Player
{
public:
    CardSet hand = 0LL, won_cards = 0LL;
    class Game* game;
    int index;
    Player(Game* g, int ix);
    virtual void choose_task(vector<shared_ptr<class Task>>&) = 0;
    virtual class Card play_card(class Trick t) = 0;
    virtual void assign_tasks(vector<shared_ptr<class Task>>&) = 0;
    virtual void cleanup();
};

class RandomPlayer: public Player
{
public:
    void choose_task(vector<shared_ptr<Task>>&);
    void assign_tasks(vector<shared_ptr<class Task>>&);
    RandomPlayer(Game* g, int ix);
    Card play_card(Trick t);
};
