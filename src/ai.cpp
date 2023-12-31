#include "ai.hpp"
#include "card.hpp"
#include "fann.h"
#include "task.hpp"
#include "game.hpp"
#include "utils.hpp"

const unsigned int AIPlayer1::q_net_layers[] = {
    Q_NET_IN,
    128,
    64,
    Q_NET_OUT
};

const unsigned int AIPlayer1::task_net_layers[] = {

};

unsigned int AIPlayer1::q_cache_ix = 0;

fann *AIPlayer1::q_net = NULL, *AIPlayer1::task_net = NULL;
array<QNetInput, CACHE_SIZE> AIPlayer1::q_cache_in;
array<QNetOutput, CACHE_SIZE> AIPlayer1::q_cache_out;

AIPlayer1::AIPlayer1(Game* g, int ix): RandomPlayer(g, ix){
    if(q_net==NULL){
        q_net = fann_create_standard_array(sizeof(q_net_layers)/sizeof(q_net_layers[0]), q_net_layers);
        fann_set_activation_function_hidden(q_net, FANN_ELLIOT_SYMMETRIC);
        fann_set_activation_function_output(q_net, FANN_ELLIOT_SYMMETRIC);
    }
}

void AIPlayer1::append_cardset_features(CardSet cs, int &ix){
    for(int j=0; j<40; j++){
        q_cache_in[q_cache_ix][ix++] = float((cs>>j)&1);
    }
    int left = 40;
    while(cs){
        int n = __popcount(cs^(cs-1))-1;
        cs >>= (n+1);
        ix += n;
        q_cache_in[q_cache_ix][ix++] = 1.0;
        left -= (n+1);
    }
    ix+=left;
}

Card AIPlayer1::play_card(Trick t){
    for(int i=0; i<Q_NET_IN; i++) q_cache_in[q_cache_ix][i] = 0.0;
    int ix = 0;
    CardSet cards_out = DECK;
    for(int i=0; i<N; i++){
        int pid = (i+index)%N;
        CardSet hand = game->players[pid]->hand;
        cards_out ^= hand;
        append_cardset_features(hand, ix);
    }
    cards_out ^= t.card_set;
    append_cardset_features(cards_out, ix);
    append_cardset_features(t.card_set, ix);
    if(t.card_set)
        q_cache_in[q_cache_ix][ix+((int) t.lead_suit - (int) Suit::PINK)] = 1.0;
    ix += 5;

    for(auto task: game->tasks){
        q_cache_in[q_cache_ix][ix+(((task->owner+N-index)%N)*K)+task->id] = 1.0;
    }

    copy(q_cache_out[q_cache_ix].begin(), q_cache_out[q_cache_ix].end(), fann_run(q_net, q_cache_in[q_cache_ix].data()));

    CardSet followingset =  get_card_set(t.lead_suit);
    CardSet choiceset = (hand&followingset);
    if(!choiceset) choiceset = hand;

    auto choices = as_vector(choiceset);

    Card retval = *max_element(choices.begin(), choices.end(), [&](Card a, Card b){
        return q_cache_out[q_cache_ix][__popcount(a.singular&(a.singular-1))] < q_cache_out[q_cache_ix][__popcount(b.singular&(b.singular-1))];
    });
    q_cache_ix = (q_cache_ix+1)%CACHE_SIZE;
    return retval;
}

void AIPlayer1::cleanup(){
    int delta = game->is_successful()? +LR : 0.;
    for(int i=q_cache_ix-40; i<q_cache_ix; i=(i+1)%CACHE_SIZE){
        fann_type *chosen = max_element(q_cache_out[i].data(), q_cache_out[i].data()+Q_NET_OUT);
        for(int j=0; j<Q_NET_OUT; j++){
            q_cache_out[i][j] -= delta;
        }
        *chosen += 2*delta;
    }
}