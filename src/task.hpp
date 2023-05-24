#pragma once
#include "common.h"

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
    ~Task();
    virtual bool is_successful(class Game* g) = 0;
    virtual void const print() = 0;
};

class WonCardSetTask: public Task
{
public:
    CardSet target_cards = 0LL, won_cards = 0LL;
    int min_count = 0, max_count = 0;
    WonCardSetTask(int diff, CardSet s, int m, int M);
    bool is_successful(Game* g);
    void const print();
};

inline shared_ptr<Task> WON_CARD_SET_TASK(auto a, auto b, auto c, auto d);


extern const shared_ptr<Task> all_tasks[];
extern const int K;