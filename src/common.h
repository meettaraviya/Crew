#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <bit>
#include <bitset>
#include <memory>
#include <functional>

#ifndef N
#define N 5
#endif
#define T (N==3?13:(N==4?10:8))
#define DIFF(a,b,c) (N==3?a:(N==4?b:c))
#define K 93

typedef long long CardSet;

const CardSet
PINKS = 0b1111111110000000000000000000000000000000LL,
YELLOWS = 0b0000000001111111110000000000000000000000LL,
GREENS = 0b0000000000000000001111111110000000000000LL,
BLUES = 0b0000000000000000000000000001111111110000LL,
BLACKS = 0b0000000000000000000000000000000000001111LL,
ONES = 0b1000000001000000001000000001000000000000LL,
TWOS = 0b0100000000100000000100000000100000000000LL,
THREES = 0b0010000000010000000010000000010000000000LL,
FOURS = 0b0001000000001000000001000000001000000000LL,
FIVES = 0b0000100000000100000000100000000100000000LL,
SIXES = 0b0000010000000010000000010000000010000000LL,
SEVENS = 0b0000001000000001000000001000000001000000LL,
EIGHTS = 0b0000000100000000100000000100000000100000LL,
NINES = 0b0000000010000000010000000010000000010000LL,
BLACK_ONE = 0b1000LL, BLACK_TWO = 0b0100LL, BLACK_THREE = 0b0010LL, BLACK_FOUR = 0b0001LL, DECK = (1LL<<40LL)-1LL;

using namespace std;