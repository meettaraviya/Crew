#pragma once
#include "common.h"
#include "game.hpp"
#include "task.hpp"
#include "player.hpp"
#include "utils.hpp"
#include "termio.hpp"

Task::Task(){};

Task::Task(int diff): difficulty(diff){
    id = current_id;
    current_id++;
};

int Task::current_id = 0;

// WonCardSetCountTask

WonCardSetCountTask::WonCardSetCountTask(int diff, CardSet s, int m, int M): Task{diff}, min_count(m), max_count(M), target_cards(s){}

bool WonCardSetCountTask::is_successful(Game* g){
    int cnt = __popcount(g->players[owner]->won_cards & target_cards);
    return (cnt>=min_count and cnt<=max_count);
}

void const WonCardSetCountTask::print(){
    cout << "Target: " << as_vector(target_cards) << ", Range: [" << min_count << "," << max_count << "]";
}

inline shared_ptr<Task> WON_CARD_SET_COUNT_TASK(auto a, auto b, auto c, auto d){ return shared_ptr<Task>(new WonCardSetCountTask(a,b,c,d));}

// NotOpenTrickTask

NotOpenTrickTask::NotOpenTrickTask(int diff, CardSet s): Task{diff}, forbidden_cards(s){}

bool NotOpenTrickTask::is_successful(Game* g){
    for(auto t: g-> tricks) if(t->leader==owner and t->card_set&forbidden_cards) return false;
    return true;
}

void const NotOpenTrickTask::print(){
    cout << "DontOpenWith: " << as_vector(forbidden_cards);
}

inline shared_ptr<Task> NOT_OPEN_TRICK_TASK(auto a, auto b){ return shared_ptr<Task>(new NotOpenTrickTask(a,b));}

// WonCardSetConditionTask

#ifdef DBG
WonCardSetConditionTask::WonCardSetConditionTask(int diff, function<bool (CardSet)> wcc, string d): Task{diff}, won_cardset_condition(wcc), description(d){}
#else
WonCardSetConditionTask::WonCardSetConditionTask(int diff, function<bool (CardSet)> wcc): Task{diff}, won_cardset_condition(wcc){}
#endif

bool WonCardSetConditionTask::is_successful(Game* g){
    return won_cardset_condition(g->players[owner]->won_cards);
}

void const WonCardSetConditionTask::print(){
    #ifdef DBG
    cout << "Goal: " << description;
    #endif
}

#ifdef DBG
inline shared_ptr<Task> WON_CARD_SET_CONDITION_TASK(auto a, auto b, string c){ return shared_ptr<Task>(new WonCardSetConditionTask(a,b,c));}
#else
inline shared_ptr<Task> WON_CARD_SET_CONDITION_TASK(auto a, auto b, string c){ return shared_ptr<Task>(new WonCardSetConditionTask(a,b));}
#endif


// TrickConditionTask

#ifdef DBG
TrickConditionTask::TrickConditionTask(int diff, function<bool (Trick)> tc, string d): Task{diff}, trick_condition(tc), description(d){}
#else
TrickConditionTask::TrickConditionTask(int diff, function<bool (Trick)> tc): Task{diff}, trick_condition(tc){}
#endif

bool TrickConditionTask::is_successful(Game* g){
    for(auto t: g->tricks){
        if(t->winner == owner and trick_condition(*t)) return true;
    }
    return false;
}

void const TrickConditionTask::print(){
    #ifdef DBG
    cout << "Goal: " << description;
    #endif
}

#ifdef DBG
inline shared_ptr<Task> TRICK_CONDITION_TASK(auto a, auto b, string c){ return shared_ptr<Task>(new TrickConditionTask(a,b,c));}
#else
inline shared_ptr<Task> TRICK_CONDITION_TASK(auto a, auto b, string c){ return shared_ptr<Task>(new TrickConditionTask(a,b));}
#endif

// TrickWinnerConfigConditionTask

#ifdef DBG
TrickWinnerConfigConditionTask::TrickWinnerConfigConditionTask(int diff, function <bool(int[T], int, int)> twcc, string d): Task{diff}, trick_winner_config_condition(twcc), description(d){}
#else
TrickWinnerConfigConditionTask::TrickWinnerConfigConditionTask(int diff, function <bool(int[T], int, int)> twcc): Task{diff}, trick_winner_config_condition(twcc){}
#endif

bool TrickWinnerConfigConditionTask::is_successful(Game* g){
    return trick_winner_config_condition(g->trick_winners, owner, g->captain);
}

void const TrickWinnerConfigConditionTask::print(){
    #ifdef DBG
    cout << "Goal: " << description;
    #endif
}

#ifdef DBG
inline shared_ptr<Task> TRICK_WINNER_CONFIG_CONDITION_TASK(auto a, auto b, string c){ return shared_ptr<Task>(new TrickWinnerConfigConditionTask(a,b,c));}
#else
inline shared_ptr<Task> TRICK_WINNER_CONFIG_CONDITION_TASK(auto a, auto b, string c){ return shared_ptr<Task>(new TrickWinnerConfigConditionTask(a,b));}
#endif

// all_tasks

const shared_ptr<Task> all_tasks[] = {
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,3,3),
        PINKS | BLUES,
        0, 0
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,3,3),
        NINES,
        2, 2
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(1,1,1),
        YELLOWS & ONES,
        1, 1
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,3,3),
        (PINKS & NINES) | (YELLOWS & EIGHTS),
        2, 2
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,3,3),
        BLUES & (ONES | TWOS | THREES),
        3, 3
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,3,3),
        BLACKS,
        1, 1
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,4,4),
        SIXES,
        3, 3
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,4,4),
        GREENS,
        2, 2
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,4,5),
        FIVES,
        3, 4
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(4,5,6),
        NINES,
        4, 4
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,2,3),
        (PINKS & FIVES) | (YELLOWS & SIXES),
        2, 2
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,3,3),
        YELLOWS,
        7, 9
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(1,1,1),
        BLACK_THREE,
        1, 1
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,2,3),
        (GREENS & FIVES) | (BLUES & EIGHTS),
        2, 2
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,4,4),
        (GREENS & THREES) | (YELLOWS & FOURS) | (YELLOWS & FIVES),
        3, 3
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,2,2),
        (PINKS & ONES) | (GREENS & SEVENS),
        2, 2
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,2,3),
        (PINKS & EIGHTS) | (BLUES & FIVES),
        2, 2
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(1,1,1),
        BLUES & FOURS,
        1, 1
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,2,2),
        ONES,
        0, 0
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,2,2),
        YELLOWS,
        0, 0
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(1,2,2),
        FIVES,
        0, 0
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(1,1,1),
        BLACKS,
        0, 0
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,3,3),
        YELLOWS | GREENS,
        0, 0
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(1,1,1),
        NINES,
        0, 0
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(1,1,1),
        PINKS & THREES,
        1, 1
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,4,5),
        THREES,
        4, 4
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,2,3),
        (BLUES & SIXES) | (YELLOWS & SEVENS),
        2, 2
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,3,3),
        (YELLOWS & NINES) | (BLUES & SEVENS),
        2, 2
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,3,3),
        ONES | TWOS | THREES,
        0, 0
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,3,2),
        EIGHTS | NINES,
        0, 0
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,3,3),
        PINKS,
        5, 9
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,4,5),
        NINES,
        3, 4
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,2,2),
        GREENS,
        0, 0
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,4,4),
        BLACKS,
        3, 4
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,4,4),
        BLUES,
        2, 2
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(1,1,1),
        GREENS & SIXES,
        1, 1
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(2,2,2),
        SEVENS,
        2, 4
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,3,4),
        BLACKS,
        2, 2
    ),
    WON_CARD_SET_COUNT_TASK(
        DIFF(3,3,4),
        PINKS,
        1, 1
    ),
    TRICK_CONDITION_TASK(
        DIFF(3,4,5),
        [](Trick t){return t.index == T-1 and t.card_set & GREENS & TWOS;},
        "Win G2 in final trick"
    ),
    TRICK_CONDITION_TASK(
        DIFF(3,4,5),
        [](Trick t){return t.cards[t.relative_winner].singular & THREES;},
        "Win using C3"
    ),
    TRICK_CONDITION_TASK(
        DIFF(3,4,5),
        [](Trick t){return t.cards[t.relative_winner].singular & TWOS;},
        "Win using C2"
    ),
    TRICK_CONDITION_TASK(
        DIFF(2,3,3),
        [](Trick t){return t.cards[t.relative_winner].singular & SIXES;},
        "Win using C6"
    ),
    TRICK_CONDITION_TASK(
        DIFF(2,3,4),
        [](Trick t){return t.cards[t.relative_winner].singular & FIVES;},
        "Win using C5"
    ),
    TRICK_CONDITION_TASK(
        DIFF(1,2,2),
        [](Trick t){return t.cards[t.relative_winner].singular & SEVENS and t.card_set & FIVES;},
        "Win C5 using C7"
    ),
    TRICK_CONDITION_TASK(
        DIFF(3,4,5),
        [](Trick t){return t.cards[t.relative_winner].singular & FOURS and t.card_set & EIGHTS;},
        "Win C8 using C4"
    ),
    TRICK_CONDITION_TASK(
        DIFF(3,3,4),
        [](Trick t){return t.count(Suit::BLACK)==0 and t.sum()>DIFF(23,28,31);},
        (string) "Win trick with total>" + DIFF("23","28","31") + " (no K)"
    ),
    TRICK_CONDITION_TASK(
        DIFF(3,3,4),
        [](Trick t){return t.count(Suit::BLACK)==0 and t.sum()<DIFF(8,12,16);},
        (string) "Win trick with total<" + DIFF("8","12","16") + " (no K)"
    ),
    TRICK_CONDITION_TASK(
        DIFF(3,3,4),
        [](Trick t){return t.count(Suit::BLACK)==0 and t.sum()>=22 and t.sum()<=23;},
        "Win trick with total=22 or total=23 (no K)"
    ),
    TRICK_CONDITION_TASK( //TODO: confirm
        DIFF(2,4,5),
        [](Trick t){return t.count(Suit::BLACK)==0 and t.even_count()==0;},
        "Win trick with only odds (no K)"
    ),
    TRICK_CONDITION_TASK( //TODO: confirm
        DIFF(2,5,6),
        [](Trick t){return t.count(Suit::BLACK)==0 and t.even_count()==N;},
        "Win trick with only evens (no K)"
    ),
    TRICK_CONDITION_TASK(
        DIFF(2,3,4),
        [](Trick t){return t.min()>5;},
        "Win trick with min>5"
    ),
    TRICK_CONDITION_TASK(
        DIFF(2,3,3),
        [](Trick t){return t.max()>7;},
        "Win trick with max<5 (no K)"
    ),
    TRICK_CONDITION_TASK(
        DIFF(2,3,4),
        [](Trick t){return t.cards[t.relative_winner].singular & SIXES and (t.card_set^t.cards[t.relative_winner].singular) & SIXES;},
        "Win C6 using another C6"
    ),
    TRICK_CONDITION_TASK(
        DIFF(3,3,3),
        [](Trick t){return t.cards[t.relative_winner].singular & BLACKS and t.card_set & PINKS & SEVENS;},
        "Win P7 using K"
    ),
    TRICK_CONDITION_TASK(
        DIFF(3,3,3),
        [](Trick t){return t.cards[t.relative_winner].singular & BLACKS and t.card_set & GREENS & NINES;},
        "Win G9 using K"
    ),
    TRICK_CONDITION_TASK(
        DIFF(2,3,3),
        [](Trick t){return t.card_set & PINKS and t.count(Suit::PINK)==t.count(Suit::BLUE);},
        "Win trick with #P=#B>0"
    ),
    TRICK_CONDITION_TASK(
        DIFF(2,3,3),
        [](Trick t){return t.card_set & PINKS and t.count(Suit::GREEN)==t.count(Suit::YELLOW);},
        "Win trick with #G=#Y>0"
    ),
    WON_CARD_SET_CONDITION_TASK(
        DIFF(3,4,5),
        [](CardSet cs){return cs&PINKS==PINKS or cs&YELLOWS==YELLOWS or cs&GREENS==GREENS or cs&BLUES==BLUES;},
        "Win all Cn for some C"
    ),
    WON_CARD_SET_CONDITION_TASK(
        DIFF(4,4,4),
        [](CardSet cs){return cs&PINKS and __popcount(cs&PINKS)==__popcount(cs&PINKS);},
        "Win #P=#Y>0"
    ),
    WON_CARD_SET_CONDITION_TASK(
        DIFF(1,1,1),
        [](CardSet cs){return __popcount(cs&PINKS)>__popcount(cs&GREENS);},
        "Win #P>#G"
    ),
    WON_CARD_SET_CONDITION_TASK(
        DIFF(1,1,1),
        [](CardSet cs){return __popcount(cs&YELLOWS)>__popcount(cs&BLUES);},
        "Win #Y>#B"
    ),
    WON_CARD_SET_CONDITION_TASK(
        DIFF(2,3,4),
        [](CardSet cs){return cs&PINKS and cs&GREENS & cs&YELLOWS and cs&BLUES;},
        "Win #P>0 & #G>0 & #B>0 & #Y>0"
    ),
    WON_CARD_SET_CONDITION_TASK(
        DIFF(4,4,4),
        [](CardSet cs){return __popcount(cs&PINKS)==1 and __popcount(cs&GREENS)==1;},
        "Win #P=1 & #G=1"
    ),
    WON_CARD_SET_CONDITION_TASK(
        DIFF(3,3,3),
        [](CardSet cs){return cs&BLACKS==BLACK_TWO;},
        "Win K2 and no other K"
    ),
    WON_CARD_SET_CONDITION_TASK(
        DIFF(3,3,3),
        [](CardSet cs){return cs&BLACKS==BLACK_ONE;},
        "Win K1 and no other K"
    ),
    NOT_OPEN_TRICK_TASK(
        DIFF(2,1,1),
        PINKS | GREENS
    ),
    NOT_OPEN_TRICK_TASK(
        DIFF(4,3,3),
        PINKS | YELLOWS | BLUES
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(2,3,4),
        [](int winners[T], int x, int _){return winners[0]==x and winners[1]==x and winners[2]==x;},
        "Win first 3 tricks"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(3,4,4),
        [](int winners[T], int x, int _){return winners[0]==x and winners[T-1]==x;},
        "Win first and last tricks"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(2,3,3),
        [](int winners[T], int x, int _){return winners[T-1]==x;},
        "Win last trick"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(1,1,1),
        [](int winners[T], int x, int _){return winners[0]==x;},
        "Win first trick"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(1,1,2),
        [](int winners[T], int x, int _){return winners[0]==x and winners[1]==x;},
        "Win first 2 tricks"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(1,2,2),
        [](int winners[T], int x, int _){return winners[0]!=x and winners[1]!=x and winners[2]!=x;},
        "Win none of first 3 tricks"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(1,2,3),
        [](int winners[T], int x, int _){return winners[0]!=x and winners[1]!=x and winners[2]!=x and winners[3]!=x;},
        "Win none of first 4 tricks"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(2,3,3),
        [](int winners[T], int x, int _){return winners[0]!=x and winners[1]!=x and winners[2]!=x and winners[3]!=x and winners[4]!=x;},
        "Win none of first 5 tricks"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(4,3,3),
        [](int winners[T], int x, int _){for(int i=0;i<T; i++) if(winners[i]==x) return false; return true; },
        "Win =0 tricks"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(4,4,4),
        [](int winners[T], int x, int _){for(int i=0;i<T-1; i++) if(winners[i]==x) return false; return winners[T-1]==x; },
        "Win only last trick"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(2,2,2),
        [](int winners[T], int x, int c){if(x==c) return false; int a = 0; for(int i=0;i<T; i++) a += (int) (winners[i]==x) - (int) (winners[i]==c); return a<0;},
        "Win fewer tricks than @ (not @)"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(2,2,3),
        [](int winners[T], int x, int c){if(x==c) return false; int a = 0; for(int i=0;i<T; i++) a += (int) (winners[i]==x) - (int) (winners[i]==c); return a>0;},
        "Win more tricks than @ (not @)"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(4,3,3),
        [](int winners[T], int x, int c){if(x==c) return false; int a = 0; for(int i=0;i<T; i++) a += (int) (winners[i]==x) - (int) (winners[i]==c); return a==0;},
        "Win as many tricks as @ (not @)"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(2,3,4),
        [](int winners[T], int x, int _){for(int i=0;i<T-1; i++) if(winners[i]==x and winners[i+1]==x) return true; return false;},
        "Win 2 tricks in row"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(1,1,1),
        [](int winners[T], int x, int _){for(int i=0;i<T-2; i++) if(winners[i]==x and winners[i+1]==x and winners[i+2]==x) return true; return false;},
        "Win 3 tricks in row"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(3,2,2),
        [](int winners[T], int x, int _){for(int i=0;i<T-1; i++) if(winners[i]==x and winners[i+1]==x) return false; return true;},
        "Never win 2 tricks in row"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(3,3,3),
        [](int winners[T], int x, int _){
            int c = 0;
            for(int i=0;i<T; i++) if(winners[i]==x) c++; if(c!=2) return false;
            for(int i=0;i<T-1; i++) if(winners[i]==x and winners[i+1]==x) return true; return false;
        },
        "Win =2 tricks and 2 tricks in row"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(3,3,4),
        [](int winners[T], int x, int _){
            int c = 0;
            for(int i=0;i<T; i++) if(winners[i]==x) c++; if(c!=3) return false;
            for(int i=0;i<T-2; i++) if(winners[i]==x and winners[i+1]==x and winners[i+2]==x) return true; return false;
        },
        "Win =3 tricks and 3 tricks in row"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(3,2,2),
        [](int winners[T], int x, int _){int c = 0; for(int i=0;i<T; i++) c += (int) (winners[i]==x); return c==1;},
        "Win =1 tricks"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(2,2,2),
        [](int winners[T], int x, int _){int c = 0; for(int i=0;i<T; i++) c += (int) (winners[i]==x); return c==2;},
        "Win =2 tricks"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(2,3,5),
        [](int winners[T], int x, int _){int c = 0; for(int i=0;i<T; i++) c += (int) (winners[i]==x); return c==4;},
        "Win =4 tricks"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(3,4,5),
        [](int winners[T], int x, int _){int c = 0; for(int i=0;i<T; i++) c += (int) (winners[i]==x); return c>T-c;},
        "Win >T/2 tricks"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(2,2,3),
        [](int winners[T], int x, int _){
            int cnt[N];
            for(int i=0; i<N; i++) cnt[i]=0;
            for(int i=0;i<T; i++) cnt[winners[i]]++;
            for(int i=0; i<N; i++) if(i!=x and cnt[i]>=cnt[x]) return false;
            return true;
        },
        "Win fewer tricks than anyone"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(2,3,3),
        [](int winners[T], int x, int _){
            int cnt[N];
            for(int i=0; i<N; i++) cnt[i]=0;
            for(int i=0;i<T; i++) cnt[winners[i]]++;
            for(int i=0; i<N; i++) if(i!=x and cnt[i]<=cnt[x]) return false;
            return true;
        },
        "Win more tricks than anyone"
    ),
    TRICK_WINNER_CONFIG_CONDITION_TASK(
        DIFF(4,3,3),
        [](int winners[T], int x, int _){int c = 0; for(int i=0;i<T-1; i++) c += (int) (winners[i]==x); return c==1 and winners[0]==x;},
        "Win only first trick"
    ),

};

const int K = sizeof(all_tasks) / sizeof(all_tasks[0]);