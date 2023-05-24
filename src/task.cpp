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

Task::~Task(){};

int Task::current_id = 0;

WonCardSetTask::WonCardSetTask(int diff, CardSet s, int m, int M): Task{diff}, min_count(m), max_count(M), target_cards(s){}

bool WonCardSetTask::is_successful(Game* g){
    int cnt = __popcount(g->players[owner]->won_cards & target_cards);
    // cout << min_count << ' ' << cnt << ' ' << max_count << ' ' << target_cards << endl;
    return (cnt>=min_count and cnt<=max_count);
}

void const WonCardSetTask::print(){
    cout << "Target: " << as_vector(target_cards) << ", Range: [" << min_count << "," << max_count << "]";
}

inline shared_ptr<Task> WON_CARD_SET_TASK(auto a, auto b, auto c, auto d){ return shared_ptr<Task>(new WonCardSetTask(a,b,c,d));}

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

const int K = sizeof(all_tasks) / sizeof(all_tasks[0]);