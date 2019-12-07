//
// Created by reece on 07/12/2019.
//

#ifndef ADVENT_OF_CODE_2019_INTCODECOMPUTER_H
#define ADVENT_OF_CODE_2019_INTCODECOMPUTER_H

#include <vector>
#include <string>
#include <map>

typedef int instruction;
const int OUT = 4;
const int IN = 3;
const int MULT = 2;
const int ADD = 1;
const int HALT = 99;

class IntCodeComputer{
    private:
        std::vector<instruction> memory;
        std::map<instruction, int> branch_table;
        int prev_instruction_pointer;
        int instruction_pointer;
        bool is_system_running;
    public:
        explicit IntCodeComputer(const std::string& program_location);
        void load_memory(const std::string& program_location);
        void load_branch_table();
        void memory_dump();
        void step();
        void execute();

};

#endif //ADVENT_OF_CODE_2019_INTCODECOMPUTER_H
