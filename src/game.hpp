#pragma once
#include "common.h"

class Game
{
public:
    shared_ptr<class Player> players[N];
    shared_ptr<class Trick> tricks[T];
    Game();
};

class SequentialSelectionGame: public Game
{
public:
    int difficulty;
    vector<shared_ptr<class Task>> tasks;
    SequentialSelectionGame(int);
    void task_selection_phase();
    void initialize_hands();
    void trick_phase();
    bool is_successful();
    ~SequentialSelectionGame();
};