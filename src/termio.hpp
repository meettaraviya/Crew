#pragma once
#include "common.h"
#include "card.hpp"
#include "task.hpp"

namespace bg {
const string dflt="\e[49m",
black="\e[40m",
// black="K",
red="\e[41m",
green="\e[42m",
// green="G",
yellow="\e[43m",
// yellow="Y",
blue="\e[44m",
// blue="B",
magenta="\e[45m",
// magenta="P",
cyan="\e[46m",
light_gray="\e[47mL",
dark_gray="\e[100m",
light_red="\e[101m",
light_green="\e[102m",
light_yellow="\e[103m",
light_blue="\e[104m",
light_magenta="\e[105m",
light_cyan="\e[106m",
white="\e[107";
};

namespace fg {
const string dflt="\e[39m",
black="\e[30m",
red="\e[31m",
green="\e[32m",
yellow="\e[33m",
blue="\e[34m",
magenta="\e[35m",
cyan="\e[36m",
light_gray="\e[37m",
dark_gray="\e[90m",
light_red="\e[91m",
light_green="\e[92m",
light_yellow="\e[93m",
light_blue="\e[94m",
light_magenta="\e[95m",
light_cyan="\e[96m",
white="\e[97m";
};

namespace set {
const string bold="\e[1m",
dim="\e[2m",
underlined="\e[4m",
blink="\e[5m",
inverted="\e[7m",
hidden="\e[8m";
};

namespace reset {
const string bold="\e[21m",
dim="\e[22m",
underlined="\e[24m",
blink="\e[25m",
inverted="\e[27m",
hidden="\e[28m";
};

ostream& operator<<(ostream& x, const Card &c);
ostream& operator<<(ostream& x, const vector<Card> &_s);
ostream& operator<<(ostream& x, const Trick &t);
ostream& operator<<(ostream& x, Task* task);