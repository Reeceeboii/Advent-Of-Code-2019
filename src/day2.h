//
// Created by reece on 02/12/2019.
//

#ifndef ADVENT_OF_CODE_2019_DAY2_H
#define ADVENT_OF_CODE_2019_DAY2_H

#include <vector>
#include <map>

const int NOUN = 1;
const int VERB = 2;
typedef int instruction;

std::map<instruction, int> load_branch_table();
std::vector<instruction> load_memory();
void execute(std::map<instruction, int> & branch_table, std::vector<instruction>& memory);
int day_2_part_1();
int day_2_part_2();

#endif //ADVENT_OF_CODE_2019_DAY2_H
