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
    std::fstream infile("res/day5.txt");
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
        std::string opcode, param_1 = "0", param_2 = "0", param_3 = "0";

        switch(instruction.length()){
            case 5:
                opcode = instruction.substr(3, 5);
                param_1 = instruction.at(2);
                param_2 = instruction.at(1);
                param_3 = instruction.at(0);
                break;
            case 4:
                opcode = instruction.substr(2, 4);
                param_1 = instruction.at(1);
                param_2 = instruction.at(0);
                break;
            case 3:
                opcode = instruction.substr(2, 3);
                param_1 = instruction.at(0);
                break;
            case 2: // HALT is the only instruction of length 2
                opcode = instruction;
                break;
            case 1: // IN, or ADD with no addressing mode settings
                opcode = instruction.at(0);
                break;
        }

        switch(std::stoi(opcode)){
            case 99: { // HALT
                end_of_program = true;
                break;
            }
            case 1: { // ADD
                // TODO could likely move this repetition into its own function at some point
                // TODO -- need to just get it working first]
                if(!(param_1 == "0")){ // have addressing modes been specified?
                    int val1 = 0, val2 = 0;
                    switch (std::stoi(param_1)) {
                        // TODO instruction 1|01 - has only 1 param but this tests for 2 - need to add a check for the number of parameters
                        case 1:// parameter 1 is in immediate mode
                            val1 = program[instruction_pointer + 1];
                            break;
                        case 0: // parameter 1 is in direct mode
                            val1 = program[program[instruction_pointer + 1]];
                            break;
                    }
                    if(!(param_2.empty())) {
                        switch (std::stoi(param_2)) {
                            case 1: // parameter 1 is in immediate mode
                                val2 = program[instruction_pointer + 2];
                                break;
                            case 0: // parameter 1 is in direct mode
                                val2 = program[program[instruction_pointer + 2]];
                                break;
                        }
                    }
                    program[program[instruction_pointer + 3]] = val1 + val2;
                    instruction_pointer += branch_table[1];
                    break;
                } else {
                    int val1 = program[program[instruction_pointer + 1]];
                    int val2 = program[program[instruction_pointer + 2]];
                    program[program[instruction_pointer + 3]] = val1 + val2;
                    instruction_pointer += branch_table[1];
                    break;
                }

            }
            case 2: { // MULTIPLY
                int val1 = 0, val2 = 0;
                switch (std::stoi(param_1)){
                    case 1: // parameter 1 is in immediate mode
                        val1 = program[instruction_pointer + 1];
                        break;
                    case 0: // parameter 1 is in direct mode
                        val1 = program[program[instruction_pointer + 1]];
                        break;
                }
                switch (std::stoi(param_2)){
                    case 1:  // parameter 2 is in immediate mode
                        val2 = program[instruction_pointer + 2];
                        break;
                    case 2:  // parameter 2 is in direct mode
                        val2 = program[program[instruction_pointer + 2]];
                        break;
                }
                program[program[instruction_pointer + 3]] = val1 * val2;
                instruction_pointer += branch_table[2];
                break;
            }
            case 3:{
                std::cout << "\nINPUT: ";
                std::cin >> program[program[instruction_pointer + 1]];
                instruction_pointer += branch_table[3];
                break;
            }
            case 4:{
                switch(std::stoi(param_1)){
                    case 1: // output is being used in immediate mode
                        std::cout << "OUT: " << program[instruction_pointer + 1] << "\n";
                        break;
                    case 0: // '' in direct mode
                        std::cout << "OUT: " << program[program[instruction_pointer + 1]] << "\n";
                        break;
                }
                instruction_pointer += branch_table[4];
                break;
            }

        }
    }
}

int day_5_part_1() {
    auto program = load_updated_memory();
    run_test(program);
    return 0;
}

int day_5_part_2() {
    return 0;
}
