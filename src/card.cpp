#include "common.h"
#include "card.hpp"


Value::Value(int v): value(v){if(v<1 or v>9) throw invalid_argument("Invalid value");};

Value::operator int() const
{
    return value;
}

CardSet get_card_set(Suit s){
    switch (s)
    {
    case Suit::PINK: return PINKS;
    case Suit::YELLOW: return YELLOWS;
    case Suit::GREEN: return GREENS;
    case Suit::BLUE: return BLUES;
    case Suit::BLACK: return BLACKS;
    }
}

CardSet get_card_set(Value v){
    switch ((int) v)
    {
    case 1: return ONES;
    case 2: return TWOS;
    case 3: return THREES;
    case 4: return FOURS;
    case 5: return FIVES;
    case 6: return SIXES;
    case 7: return SEVENS;
    case 8: return EIGHTS;
    case 9: return NINES;
    }
}

Card::Card(Suit s, int v): suit(s), value(v){
    if(s == Suit::BLACK and ((int) v <= 0 or (int) v > 4)){
        throw invalid_argument("Invalid card");
    }
    if((int) v <= 0 or (int) v > 9){
        throw invalid_argument("Invalid card");
    }
    singular = 1LL << (39 - (((int) suit - 10)*9 + v - 1));
};
Card::Card(CardSet c): value(1){
    if(c & (c-1)){
        throw invalid_argument("Wrongly initialized card");
    }
    singular = c;
    int i = 39 - __popcount(c-1);
    suit = (Suit) (10 + i/9);
    value = Value(1+i%9);
};
bool Card::operator>(const Card &other){
    if(suit == Suit::BLACK) return (other.suit != Suit::BLACK) or (other.value <= value);
    else return (other.suit != Suit::BLACK) and (other.suit != suit or other.value <= value);
}

Trick::Trick(int l, int i): leader(l), index(i){}

void Trick::add(Card card){
    cards.push_back(card);
    if(cards.size() == 1){
        relative_winner = 0;
        lead_suit = card.suit;
    }
    else {
        relative_winner = cards[relative_winner] > card ? relative_winner : cards.size() - 1;
    }
    card_set |= card.singular;
}

int Trick::count(Suit s){
    int c = 0;
    for(auto card: cards) if(card.suit==s) c++;
    return c;
}

int Trick::sum(){
    int s = 0;
    for(auto card: cards) s+=card.value;
    return s;
}

Value Trick::max(){
    int s = 0;
    for(auto card: cards) s=(card.value>s? (int)card.value:s);
    return Value(s);
}

Value Trick::min(){
    int s = 10;
    for(auto card: cards) s=(card.value<s? (int)card.value:s);
    return Value(s);
}
