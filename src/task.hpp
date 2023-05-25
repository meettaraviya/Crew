#pragma once
#include "common.h"
#include "card.hpp"

class Task
{
private:
    static int current_id;
public:
    int id = -1;
    int difficulty = 0;
    int owner = -1;
    Task();
    Task(int diff);
    virtual bool is_successful(class Game* g) = 0;
    virtual void const print() = 0;
};

class WonCardSetCountTask: public Task
{
public:
    CardSet target_cards = 0LL;
    int min_count = 0, max_count = 0;
    WonCardSetCountTask(int diff, CardSet s, int m, int M);
    bool is_successful(Game* g);
    void const print();
};

class WonCardSetConditionTask: public Task
{
public:
    function<bool (CardSet)> won_cardset_condition;
    #ifdef DBG
    string description;
    WonCardSetConditionTask(int diff, function<bool (CardSet)>, string d);
    #else
    WonCardSetConditionTask(int diff, function<bool (CardSet)>);
    #endif
    bool is_successful(Game* g);
    void const print();
};

class TrickConditionTask: public Task
{
public:
    function<bool (Trick)> trick_condition;
    #ifdef DBG
    string description;
    TrickConditionTask(int diff, function<bool (Trick)>, string d);
    #else
    TrickConditionTask(int diff, function<bool (Trick)>);
    #endif
    bool is_successful(Game* g);
    void const print();
};

class NotOpenTrickTask: public Task
{
public:
    CardSet forbidden_cards = 0LL;
    NotOpenTrickTask(int diff, CardSet s);
    bool is_successful(Game* g);
    void const print();
};

class TrickWinnerConfigConditionTask: public Task
{
public:
    function <bool(int[T], int, int)> trick_winner_config_condition;
    #ifdef DBG
    string description;
    TrickWinnerConfigConditionTask(int diff, function <bool(int[T], int, int)>, string d);
    #else
    TrickWinnerConfigConditionTask(int diff, function <bool(int[T], int, int)>);
    #endif    
    bool is_successful(Game* g);
    void const print();
};

extern const shared_ptr<Task> all_tasks[];
extern const int K;