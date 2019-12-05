//
// Created by reece on 05/12/2019.
//

#ifndef ADVENT_OF_CODE_2019_DAY5_H
#define ADVENT_OF_CODE_2019_DAY5_H

#include <map>
#include <vector>

typedef int instruction;

std::map<instruction, int> load_updated_branch_table();
std::vector<instruction> load_updated_memory();
void run_test(std::vector<instruction>& program);
void memory_dump(std::vector<instruction>& program);
int day_5_part_1();
int day_5_part_2();

#endif //ADVENT_OF_CODE_2019_DAY5_H
