#include "common.h"
#include "card.hpp"
#include "task.hpp"
#include "player.hpp"

Player::Player(Game* g, int ix=-1): index(ix), game(g) {}

void Player::cleanup(){}

void RandomPlayer::choose_task(vector<shared_ptr<Task>> &tasks){
    int i = 0;
    while (tasks[i]->owner>=0) i++;
    tasks[i]->owner = index;
}

void RandomPlayer::assign_tasks(vector<shared_ptr<Task>> &tasks){
    for(auto &task: tasks){
        task -> owner = rand()%N;
    }
}

RandomPlayer::RandomPlayer(Game* g, int ix=-1): Player{g, ix}{}

Card RandomPlayer::play_card(Trick t){
    CardSet following =  get_card_set(t.lead_suit);
    CardSet choices = (hand&following);
    if(!choices) choices = hand;
    int n = rand()%__popcount(choices);
    while(n>0){
        n--; choices &= (choices-1);
    }
    Card out(choices & (~choices + 1));
    hand ^= out.singular;
    return out;
}