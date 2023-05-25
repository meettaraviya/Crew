#include "termio.hpp"
#include "card.hpp"
#include "utils.hpp"

ostream& operator<<(ostream& x, const Card &c){
    string s = (c.suit == Suit::BLACK?
        bg::black:
        (c.suit == Suit::PINK?
        bg::magenta:
        (c.suit == Suit::YELLOW?
        bg::yellow:
        (c.suit == Suit::GREEN?
        bg::green:
        (bg::blue)))));
    return x << s << c.value << bg::dflt;
}

ostream& operator<<(ostream& x, const vector<Card> &_s){
    for(int i=0; i<_s.size(); i++) x << _s[i];
    return x;
}

ostream& operator<<(ostream& x, const Trick &t){
    cout << "Leader[" << t.index << "]: " << t.leader << ", Trick[" << t.index << "]: ";
    for(Card c: t.cards) cout << c;
    cout << ", Winner[" << t.index << "]: " << (t.leader + t.relative_winner)%N << "," << endl;
}

ostream& operator<<(ostream& x, Task* task){
    cout << "Id: " << task->id << ", Owner: " << task->owner << ", Difficulty: " << task->difficulty << ", ";
    task->print();
}
