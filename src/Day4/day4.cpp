//
// Created by reece on 04/12/2019.
//

#include "day4.h"

// continually mod by 10 to extract digits. Use this to check for adjacency and decreasing digits
bool adjacent_digits(int potential_pwd){
    bool match = false;
    while(potential_pwd > 0 && !match){
        int digit = potential_pwd % 10; // pop last digit off number
        int temp = potential_pwd / 10; // hold a temp equal to the digit after popping, and pop that too. Compare.
        temp % 10 == digit ? match = true : potential_pwd /= 10;
    }
    return match;
}

// similarly, continually mod by 10 to extract digits and check their size in relation to the next popped digit
bool never_decrease(int potential_pwd){
    bool match = true;
    while(potential_pwd > 0 && match){
        int digit = potential_pwd % 10;
        int temp = potential_pwd / 10;
        temp % 10 > digit ? match = false : potential_pwd /= 10;
    }
    return match;
}


int day_4_part_1(){
    int total = 0;
    for(int iter = LOWER; iter <= HIGHER; ++iter){
        if(adjacent_digits(iter) && never_decrease(iter)) ++total;
    }
    return total;
}