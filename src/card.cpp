#include "common.h"

enum class Suit {BLACK = 10, PINK = 11, YELLOW = 12, GREEN = 13, BLUE = 14};

class Value
{
public:
    int value;
    Value(int v): value(v){};
    operator int() const
    {
        return value;
    }
};


class Card
{
public:
    Suit suit;
    Value value;
    Card(Suit s, int v): suit(s), value(v){
        if(s == Suit::BLACK and ((int) v <= 0 or (int) v > 4)){
            throw invalid_argument("Invalid card");
        }
        if((int) v <= 0 or (int) v > 9){
            throw invalid_argument("Invalid card");
        }
    };
};