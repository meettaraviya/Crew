#pragma once
#include "common.h"

class Game
{
public:
    int captain = -1;
    shared_ptr<class Player> players[N];
    shared_ptr<class Trick> tricks[T];
    vector<shared_ptr<class Task>> tasks;
    int trick_winners[T];
    Game();
    void trick_phase();
    bool is_successful();
    void allot_tasks(int);
    void initialize_hands();
};

class SequentialSelectionGame: public Game
{
public:
    int difficulty;
    SequentialSelectionGame(int);
    void task_selection_phase();
};

class FreeSelectionGame: public Game
{
public:
    int difficulty;
    FreeSelectionGame(int);
    void task_selection_phase();
};