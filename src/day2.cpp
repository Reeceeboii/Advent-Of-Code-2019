//
// Created by reece on 02/12/2019.
//

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "day2.h"

// branch table representing the jump size of each opcode (depending on operand count)
// the jump is added to the instruction pointer after one instruction has executed
std::map<instruction, int> load_branch_table(){
    std::map<instruction, int> branch_table;
    branch_table.insert({ 1, 4 }); // no need to include a branch for HALT
    branch_table.insert({ 2, 4 });
    return branch_table;
}

// return vector representing memory after reading program file from disk
std::vector<instruction> load_memory(){
    std::fstream infile("res/day2.txt");
    std::string s;
    std::vector<instruction> program;
    // tokenize
    while(getline(infile, s, ',')){
        instruction token;
        std::stringstream ss(s);
        ss >> token;
        program.push_back(token);
    }
    return program;
}

void execute(std::map<instruction, int>& branch_table, std::vector<instruction>& program){
    instruction instruction_pointer = 0;
    bool end_of_program = false;
    while(!end_of_program){
        switch(program[instruction_pointer]){
            case 99: {
                end_of_program = true;
                break;
            } case 1: {
                int temp = program[program[instruction_pointer + 1]] + program[program[instruction_pointer + 2]];
                program[program[instruction_pointer + 3]] = temp;
                instruction_pointer += branch_table[1];
                break;
            } case 2: {
                int temp = program[program[instruction_pointer + 1]] * program[program[instruction_pointer + 2]];
                program[program[instruction_pointer + 3]] = temp;
                instruction_pointer += branch_table[2];
                break;
            }
        }
    }
}

int day_2_part_1(){
    std::map<instruction, int> branch_table = load_branch_table();
    std::vector<instruction> program = load_memory();

    // make required memory changes specified in task
    program[NOUN] = 12;
    program[VERB] = 2;
    execute(branch_table, program);
    return program[0];
}

int day_2_part_2(){
    std::map<instruction, int> branch_table = load_branch_table();
    std::vector<instruction> program = load_memory();
    const int MAGIC_NUMBER = 19690720;
    for (int noun = 0; noun < 100; ++noun) {
        for (int verb = 0; verb < 100; ++verb) {
            program[NOUN] = noun;
            program[VERB] = verb;
            execute(branch_table, program);
            if (program[0] == MAGIC_NUMBER) return 100 * noun + verb;
            // reset program memory before next n/v combination
            program = load_memory();
        }
    }
    return 0;
}
