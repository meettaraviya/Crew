#pragma once
#include "common.h"
#include "player.hpp"
#include "fann.h"

#define Q_NET_IN (40*(N+2)+5+K*N)
    // 40*N // initial hands
    // + 40 // cards out of play
    // + 40 // cards in trick
    // + 5 // lead suit
    // + K*N // task owners
#define Q_NET_OUT 40
#define CACHE_SIZE 100

typedef array<fann_type, Q_NET_IN> QNetInput;
typedef array<fann_type, Q_NET_OUT> QNetOutput;

class AIPlayer1: public RandomPlayer
{
public:
    fann *q_net, *task_net;
    const static unsigned int q_net_layers[], task_net_layers[];
    // void assign_tasks(vector<shared_ptr<Task>>&);
    array<QNetInput, CACHE_SIZE> q_cache_in;
    array<QNetOutput, CACHE_SIZE> q_cache_out;
    unsigned int q_cache_ix = 0;
    void append_cardset_features(CardSet, int&);
    AIPlayer1(Game* g, int ix);
    Card play_card(Trick t);
};