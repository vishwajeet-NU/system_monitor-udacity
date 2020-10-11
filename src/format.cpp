#include <string>

#include "format.h"

using std::string;
using std::to_string;

string Format::ElapsedTime(long seconds) {
    
    int hours{0}, minutes{0};

    hours = seconds/3600;
    seconds = seconds%3600;
    minutes = seconds/60;
    seconds = seconds%60;

    string out = to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
    return out; }