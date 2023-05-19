#include "common.h"
#include "game.cpp"
#pragma once

// enum class TaskStatus {FAIL = 0, PENDING = 1, SUCCESS = 2};

class Task
{
private:
    static int current_id;
public:
    int id = -1;
    int difficulty = 0;
    int owner = -1;
    // TaskStatus status;
    Task(){};
    // Task(int diff, TaskStatus s): status(s), difficulty(diff){
    Task(int diff): difficulty(diff){
        id = current_id;
        current_id++;
    };
    ~Task(){};
    virtual bool is_successful(Game* g) = 0;
};

int Task::current_id = 0;

class WonCardSetTask: public Task
{
public:
    CardSet target_cards = 0LL, won_cards = 0LL;
    int min_count = 0, max_count = 0;
    
    WonCardSetTask(int diff, CardSet s, int m, int M): Task{diff}, min_count(m), max_count(M){
        // if(m==0) status = TaskStatus::SUCCESS;
    }

    // void add(CardSet c){
    //     won_cards |= c;
    //     update_status();
    // }

    // void update_status(){
    //     int cnt = __popcount(won_cards & target_cards);
    //     if(cnt>=min_count and cnt<=max_count) status = TaskStatus::SUCCESS;
    //     else status = TaskStatus::FAIL;
    // }

    bool is_successful(Game* g){
        int cnt = __popcount(g->players[owner]->won_cards & target_cards);
        return (cnt>=min_count and cnt<=max_count);
    }
};

// class ComplexWonCardSetTask: public Task
// {
// public:
//     vector <WonCardSetTask> subtasks;
    
//     ComplexWonCardSetTask(int diff, vector<WonCardSetTask> sts): Task{diff, TaskStatus::PENDING}, subtasks(sts){}

//     void add(CardSet c){
//         for(auto st: subtasks) st.add(c);
//     }

//     void update_status(){
//         for(auto st: subtasks) st.update_status();
//     }
// };

inline auto WON_CARD_SET_TASK(auto a, auto b, auto c, auto d){ return shared_ptr<Task>(new WonCardSetTask(a,b,c,d));}

const shared_ptr<Task> all_tasks[] = {
    WON_CARD_SET_TASK(
        DIFF(3,3,3),
        PINKS | BLUES,
        0, 0
    ),
    WON_CARD_SET_TASK(
        DIFF(2,3,3),
        NINES,
        2, 2
    ),
    WON_CARD_SET_TASK(
        DIFF(1,1,1),
        YELLOWS & ONES,
        1, 1
    ),
    WON_CARD_SET_TASK(
        DIFF(2,3,3),
        (PINKS & NINES) | (YELLOWS & EIGHTS),
        2, 2
    ),
    WON_CARD_SET_TASK(
        DIFF(2,3,3),
        BLUES & (ONES | TWOS | THREES),
        3, 3
    ),
    WON_CARD_SET_TASK(
        DIFF(3,3,3),
        BLACKS,
        1, 1
    ),
    WON_CARD_SET_TASK(
        DIFF(3,4,4),
        SIXES,
        3, 3
    ),
    WON_CARD_SET_TASK(
        DIFF(3,4,4),
        GREENS,
        2, 2
    ),
    WON_CARD_SET_TASK(
        DIFF(3,4,5),
        FIVES,
        3, 4
    ),
    WON_CARD_SET_TASK(
        DIFF(4,5,6),
        NINES,
        4, 4
    ),
    WON_CARD_SET_TASK(
        DIFF(2,2,3),
        (PINKS & FIVES) | (YELLOWS & SIXES),
        2, 2
    ),
    WON_CARD_SET_TASK(
        DIFF(3,3,3),
        YELLOWS,
        7, 9
    ),
    WON_CARD_SET_TASK(
        DIFF(1,1,1),
        BLACK_THREE,
        1, 1
    ),
    WON_CARD_SET_TASK(
        DIFF(2,2,3),
        (GREENS & FIVES) | (BLUES & EIGHTS),
        2, 2
    ),
    WON_CARD_SET_TASK(
        DIFF(3,4,4),
        (GREENS & THREES) | (YELLOWS & FOURS) | (YELLOWS & FIVES),
        3, 3
    ),
    WON_CARD_SET_TASK(
        DIFF(2,2,2),
        (PINKS & ONES) | (GREENS & SEVENS),
        2, 2
    ),
    WON_CARD_SET_TASK(
        DIFF(2,2,3),
        (PINKS & EIGHTS) | (BLUES & FIVES),
        2, 2
    ),
    WON_CARD_SET_TASK(
        DIFF(1,1,1),
        BLUES & FOURS,
        1, 1
    ),
    WON_CARD_SET_TASK(
        DIFF(2,2,2),
        ONES,
        0, 0
    ),
    WON_CARD_SET_TASK(
        DIFF(2,2,2),
        YELLOWS,
        0, 0
    ),
    WON_CARD_SET_TASK(
        DIFF(1,2,2),
        FIVES,
        0, 0
    ),
    WON_CARD_SET_TASK(
        DIFF(1,1,1),
        BLACKS,
        0, 0
    ),
    WON_CARD_SET_TASK(
        DIFF(3,3,3),
        YELLOWS | GREENS,
        0, 0
    ),
    WON_CARD_SET_TASK(
        DIFF(1,1,1),
        NINES,
        0, 0
    ),
    WON_CARD_SET_TASK(
        DIFF(1,1,1),
        PINKS & THREES,
        1, 1
    ),
    WON_CARD_SET_TASK(
        DIFF(3,4,5),
        THREES,
        4, 4
    ),
    WON_CARD_SET_TASK(
        DIFF(2,2,3),
        (BLUES & SIXES) | (YELLOWS & SEVENS),
        2, 2
    ),
    WON_CARD_SET_TASK(
        DIFF(2,3,3),
        (YELLOWS & NINES) | (BLUES & SEVENS),
        2, 2
    ),
    WON_CARD_SET_TASK(
        DIFF(3,3,3),
        ONES | TWOS | THREES,
        0, 0
    ),
    WON_CARD_SET_TASK(
        DIFF(3,3,2),
        EIGHTS | NINES,
        0, 0
    ),
    WON_CARD_SET_TASK(
        DIFF(2,3,3),
        PINKS,
        5, 9
    ),
    WON_CARD_SET_TASK(
        DIFF(3,4,5),
        NINES,
        3, 4
    ),
    WON_CARD_SET_TASK(
        DIFF(2,2,2),
        GREENS,
        0, 0
    ),
    WON_CARD_SET_TASK(
        DIFF(3,4,4),
        BLACKS,
        3, 4
    ),
    WON_CARD_SET_TASK(
        DIFF(3,4,4),
        BLUES,
        2, 2
    ),
    WON_CARD_SET_TASK(
        DIFF(1,1,1),
        GREENS & SIXES,
        1, 1
    ),
    WON_CARD_SET_TASK(
        DIFF(2,2,2),
        SEVENS,
        2, 4
    ),
    WON_CARD_SET_TASK(
        DIFF(3,3,4),
        BLACKS,
        2, 2
    ),
    WON_CARD_SET_TASK(
        DIFF(3,3,4),
        PINKS,
        1, 1
    ),

};
