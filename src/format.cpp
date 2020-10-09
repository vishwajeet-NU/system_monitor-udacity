#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    
    int hours{0}, minutes{0};

    hours = seconds/3600;
    seconds = seconds%3600;
    minutes = seconds/60;
    seconds = seconds%60;

    string out = to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
    return out; }