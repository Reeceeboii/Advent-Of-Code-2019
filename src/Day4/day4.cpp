//
// Created by reece on 04/12/2019.
//

#include "day4.h"
#include <map>
#include <algorithm>

// map digits against their pairs (anything > 2 will result in their key mapping to a value higher than 1)
bool contains_matching_pair(int potential_pwd){
    std::map<int, int> pairs;
    while(potential_pwd > 0){
        int digit = potential_pwd % 10;
        if(potential_pwd / 10 % 10 == digit){
            pairs.find(digit) != pairs.end() ? ++pairs[digit] : pairs[digit] = 1;
        }
        potential_pwd /= 10;
    }
    // filter out and return
    return std::find_if(pairs.begin(), pairs.end(), [](auto& p){ return p.second == 1; }) != pairs.end();
}

// continually mod by 10 to extract digits. Use this to check for adjacency and decreasing digits
bool adjacent_digits(int potential_pwd){
    bool match = false;
    while(potential_pwd > 0 && !match){
        int digit = potential_pwd % 10; // pop last digit off number
        potential_pwd / 10 % 10 == digit ? match = true : potential_pwd /= 10;
    }
    return match;
}

// similarly, continually mod by 10 to extract digits and check their size in relation to the next popped digit
bool never_decrease(int potential_pwd){
    bool match = true;
    while(potential_pwd > 0 && match){
        int digit = potential_pwd % 10;
        potential_pwd / 10 % 10 > digit ? match = false : potential_pwd /= 10;
    }
    return match;
}


int day_4_part_1(){
    int total = 0;
    for(int i = LOWER; i <= HIGHER; ++i){
        if(adjacent_digits(i) && never_decrease(i)) ++total;
    }
    return total;
}

int day_4_part_2(){
    int total = 0;
    for(int i = LOWER; i <= HIGHER; ++i) {
        if(never_decrease(i) && contains_matching_pair(i)) ++total;
    }
    return total;
}