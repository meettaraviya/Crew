#include "common.h"
#include "card.cpp"

class Game
{
private:
    /* data */
public:
    int numPlayers;
    Card* card;
    Game(int=5);
    ~Game();
};

Game::Game(int n): numPlayers(n)
{
}

Game::~Game()
{
}
