#include "ai.hpp"
#include "card.hpp"
#include "fann.h"
#include "task.hpp"

const unsigned int AIPlayer1::q_net_layers[] = {
    40*N // initial hands
    + 5 // number of cards in hand for each suit
    + 40 // cards out of play
    + 40 // cards in trick
    + 5 // lead suit
    + K*N,
    100,
    40
};

AIPlayer1::AIPlayer1(Game* g, int ix): RandomPlayer(g, ix){
    q_net = fann_create_standard_array(sizeof(q_net_layers)/sizeof(q_net_layers[0]), q_net_layers);
    fann_set_activation_function_hidden(q_net, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(q_net, FANN_LINEAR);
}

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