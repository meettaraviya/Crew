#pragma once
#include "common.h"

enum class Suit {PINK = 10, YELLOW = 11, GREEN = 12, BLUE = 13, BLACK = 14};

class Value
{
public:
    int value;
    Value(int v);
    operator int() const;
};

CardSet get_card_set(Suit s);

CardSet get_card_set(Value v);

class Card
{
public:
    Suit suit;
    Value value;
    CardSet singular;
    Card(Suit s, int v);
    Card(CardSet c);
    bool operator>(const Card &other);
};

class Trick
{
public:
    int leader = -1, index = -1;
    Suit lead_suit;
    int relative_winner = -1, winner = -1;
    vector<Card> cards;
    CardSet card_set = 0LL;

    Trick();
    Trick(int l, int i);
    
    void add(Card card);
    int count(Suit s);
    int even_count();
    int sum();
    Value max();
    Value min();
};
