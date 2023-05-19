#include "common.h"

class Player
{
public:
    CardSet hand = 0LL, won_cards = 0LL;
    class Game* game;
    int index;
    Player(Game* g, int ix);
    ~Player();
    virtual void choose_task(vector<shared_ptr<Task>>) = 0;
    virtual class Card play_card(Trick t) = 0;
};

class RandomPlayer: public Player
{
public:
    void choose_task(vector<shared_ptr<Task>> tasks);
    RandomPlayer(Game* g, int ix);
    ~RandomPlayer();
    Card play_card(Trick t);
};