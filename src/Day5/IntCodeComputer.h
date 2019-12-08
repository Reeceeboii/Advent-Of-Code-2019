//
// Created by reece on 07/12/2019.
//

#ifndef ADVENT_OF_CODE_2019_INTCODECOMPUTER_H
#define ADVENT_OF_CODE_2019_INTCODECOMPUTER_H

#include <vector>
#include <string>
#include <map>

struct op_and_params{
    int opcode = 0; // the current instruction's opcode
    std::vector<int> param_modes = {0, 0}; // parameter 1 and 2's addressing modes
};

class IntCodeComputer{
    private:
        enum mnemonics {
            EQUALS = 8, LESS_THAN = 7, JUMP_IF_FALSE = 6 ,JUMP_IF_TRUE = 5,
            OUT = 4, IN = 3, MULT = 2, ADD = 1, HALT = 9
        };
        std::vector<int> memory;
        op_and_params oap;
        int instruction_ptr;
        bool system_running;
    public:
        explicit IntCodeComputer(const std::string& program_location);
        void load_memory(const std::string& program_location);
        void step();
        void interpret_opcode(int opcode);
        int run_opcode(int operand_1, int operand_2);
        void execute();
};

// driver functions called from main
void day_5_part_1();
void day_5_part_2();

#endif //ADVENT_OF_CODE_2019_INTCODECOMPUTER_H