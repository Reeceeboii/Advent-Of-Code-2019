//
// Created by reece on 04/12/2019.
//

#ifndef ADVENT_OF_CODE_2019_DAY4_H
#define ADVENT_OF_CODE_2019_DAY4_H

#include <string>

const int LOWER = 231832;
const int HIGHER = 767346;

bool adjacent_digits(int potential_pwd);
bool has_adj_equal_to_2_without_repeat(int potential_pwd);
bool never_decrease(int potential_pwd);
int day_4_part_1();
int day_4_part_2();

#endif //ADVENT_OF_CODE_2019_DAY4_H
