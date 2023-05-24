#include "ai.hpp"
#include "card.hpp"

AIPlayer1::AIPlayer1(Game* g, int ix): RandomPlayer(g, ix){

}

AIPlayer1::~AIPlayer1(){RandomPlayer::~RandomPlayer();}

Card AIPlayer1::play_card(Trick t){
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