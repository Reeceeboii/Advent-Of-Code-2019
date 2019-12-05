//
// Created by reece on 05/12/2019.
//

#include "day5.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::map<instruction, int> load_updated_branch_table(){
    std::map<instruction, int> branch_table;
    branch_table.insert({ 3, 2 }); // OUT
    branch_table.insert({ 4, 2 }); // IN
    branch_table.insert({ 1, 4 }); // ADD
    branch_table.insert({ 2, 4 }); // MULTIPLY
    return branch_table;
}

std::vector<instruction> load_updated_memory() {
    std::fstream infile("res/day5test.txt");
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

void memory_dump(std::vector<instruction>& program){
    std::cout << "\n\n- MEM DUMP -\n";
    for(auto i: program){
        std::cout << i << " ";
    }
    std::cout << "\n- END MEM DUMP -\n";
}

void run_test(std::vector<instruction> &program){
    auto branch_table = load_updated_branch_table();
    instruction instruction_pointer = 0;
    bool end_of_program = false;
    while(!end_of_program) {
        // is the current instruction using direct or immediate addressing?
        // work that out and set the addressing mode for the parameters
        std::string instruction = std::to_string(program[instruction_pointer]);
        std::string opcode, param_1, param_2, param_3;
        if(instruction.length() > 2) {
            if (instruction.length() == 5) { // opcode and 3 parameters
                opcode = instruction.substr(3, 5);
                param_1 = instruction.at(2);
                param_2 = instruction.at(1);
                param_3 = instruction.at(0);
            } else if (instruction.length() == 4) { // opcode and 2 parameters
                opcode = instruction.substr(2, 4);
                param_1 = instruction.at(1);
                param_2 = instruction.at(0);
            }
        } else {
            opcode = instruction;
        }

        switch(std::stoi(opcode)){
            case 99:{ // HALT
                end_of_program = true;
                break;
            } case 2: {
                int val1 = 0, val2 = 0;
                switch (std::stoi(param_1)) {
                    case 1: { // parameter 1 is in immediate mode
                        val1 = program[instruction_pointer + 1];
                        break;
                    }
                    case 0: { // parameter 1 is in direct mode
                        val1 = program[program[instruction_pointer + 1]];
                        break;
                    }
                }
                switch (std::stoi(param_2)) {
                    case 1: { // parameter 2 is in immediate mode
                        val2 = program[instruction_pointer + 2];
                        break;
                    }
                    case 2: { // parameter 2 is in direct mode
                        val2 = program[program[instruction_pointer + 2]];
                        break;
                    }
                }
                program[program[instruction_pointer + 3]] = val1 * val2;
                instruction_pointer += branch_table[2];
                break;
            }
            /*
            } case 3:{
                // TODO not done
                std::cout << "\nINPUT: ";
                std::cin >> program[program[instruction_pointer + 1]];
                instruction_pointer += branch_table[3];
                break;
            } case 4:{
                // TODO not done
                std::cout << "OUT: " << program[program[instruction_pointer + 1]];
                instruction_pointer += branch_table[4];
                break;
            }
             */
        }
    }
}

int day_5_part_1() {
    auto program = load_updated_memory();
    memory_dump(program);
    run_test(program);
    memory_dump(program);
    exit(1);
    return 0;
}

int day_5_part_2() {
    return 0;
}
