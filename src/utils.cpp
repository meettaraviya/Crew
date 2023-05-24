#include "utils.hpp"
#include "card.hpp"

vector<Card> as_vector(CardSet s){
    vector<Card> out;
    while(s) {
        CardSet x = s & (~s + 1);
        out.push_back(Card(x));
        s ^= x;
    }
    return out;
}
