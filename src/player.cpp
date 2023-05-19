#include "common.h"
#include "task.cpp"
#include "card.cpp"

class Player
{
public:
    CardSet hand = 0LL, won_cards = 0LL;
    class Game* game;
    int index;
    Player(Game* g, int ix=-1): index(ix), game(g) {}
    ~Player(){}
    virtual void choose_task(vector<shared_ptr<Task>>) = 0;
    virtual Card play_card(Trick t) = 0;
};

class RandomPlayer: public Player
{
public:
    void choose_task(vector<shared_ptr<Task>> tasks){
        int i = 0;
        while (tasks[i]->owner>=0) i++;
        tasks[i]->owner = index;
    }
    RandomPlayer(Game* g, int ix=-1): Player{g, ix}{}
    Card play_card(Trick t){
        CardSet following =  get_card_set(t.lead_suit);
        CardSet choices = (hand&following);
        if(!choices) choices = hand;
        int n = rand()%__popcount(choices);
        while(n>0){
            n--; choices &= (choices-1);
        }
        return Card(choices & (~choices + 1));

    }
};
