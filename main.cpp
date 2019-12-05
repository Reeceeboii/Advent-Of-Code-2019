//
// Created by reece on 02/12/2019.
//

#include "src/Day1/day1.h"
#include "src/Day2/day2.h"
#include "src/Day3/day3.h"
#include "src/Day4/day4.h"

#include <iostream>

int main(){

    std::cout << "DAY 1\n";
    std::cout << "  Part 1: " << day_1_part_1() << "\n";
    std::cout << "  Part 2: " << day_1_part_2();

    std::cout << "\nDAY 2\n";
    std::cout << "  Part 1: " << day_2_part_1() << "\n";
    std::cout << "  Part 2: " << day_2_part_2();

    std::cout << "\nDAY 3\n";
    std::cout << "  Part 1: " << day_3_part_1() << "\n";
    std::cout << "  Part 2: " << day_3_part_2();

    std::cout << "\nDAY 4\n";
    std::cout << "  Part 1: " << day_4_part_1() << "\n";
    std::cout << "  Part 2: " << day_4_part_2() << "\n";

    std::cout << "\n";
    return 0;
}
