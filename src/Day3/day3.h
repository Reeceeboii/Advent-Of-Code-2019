//
// Created by reece on 03/12/2019.
//

#ifndef ADVENT_OF_CODE_2019_DAY3_H
#define ADVENT_OF_CODE_2019_DAY3_H

#include <vector>

typedef std::pair<int, int> point;

int day_3_part_1();
int day_3_part_2();
int manhattan(const point& point);
std::vector<std::vector<point>> load_lines();
std::vector<point> intersection(std::vector<point>& set_a, std::vector<point>& set_b);

#endif //ADVENT_OF_CODE_2019_DAY3_H
