//
// Created by reece on 05/12/2019.
//

#include "day5.h"
#include "IntCodeComputer.h"
#include <fstream>
#include <sstream>
#include <iostream>

void run_test(std::vector<instruction> &program){
    while(!end_of_program) {
        // is the current instruction using direct or immediate addressing?
        // work that out and set the addressing mode for the parameters
        std::string instruction = std::to_string(program[instruction_pointer]);
        prev_instruction = instruction;
        std::string opcode, param_1, param_2, param_3;

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
            case 2: // HALT or ADD with in immediate mode are the only length 2 instructions
                if(instruction.at(1) == '4'){ // handle IN with addressing mode 1
                    opcode = instruction.at(1);
                    param_1 = instruction.at(0);
                }else{ // any other length 2 instruction can be assumed to be HALT for now
                    opcode = instruction;
                }
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
                if(!(param_1.empty())){ // have addressing modes been specified?
                    int val1 = 0, val2 = 0; // TODO 101
                    switch (std::stoi(param_1)) {
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
                    } else { // make sure val2 is not left empty at this point
                        val2 = program[program[instruction_pointer + 2]];
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
                if(!(param_1.empty())){ // have addressing modes been specified?
                    int val1 = 0, val2 = 0;
                    switch (std::stoi(param_1)) {
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
                    } else { // make sure val2 is not left empty at this point
                        val2 = program[program[instruction_pointer + 2]];
                    }
                    program[program[instruction_pointer + 3]] = val1 + val2;
                    instruction_pointer += branch_table[2];
                    break;
                } else {
                    int val1 = program[program[instruction_pointer + 1]];
                    int val2 = program[program[instruction_pointer + 2]];
                    program[program[instruction_pointer + 3]] = val1 + val2;
                    instruction_pointer += branch_table[2];
                    break;
                }
            }
            case 3:{
                std::cout << "\nINPUT: ";
                std::cin >> program[program[instruction_pointer + 1]];
                instruction_pointer += branch_table[3];
                break;
            }
            case 4:{
                if(!(param_1.empty())) {
                    switch (std::stoi(param_1)) {
                        case 1: // output is being used in immediate mode
                            if(program[instruction_pointer + 1] != 0){
                                std::cout << "NON Zero: " << prev_instruction << "\n";
                            } else {
                                std::cout << "OUT: " << program[instruction_pointer + 1] << "\n";
                            }
                            break;
                        case 0: // '' in direct mode
                            if(program[instruction_pointer + 1] != 0){
                                std::cout << "NON Zero: " << prev_instruction << "\n";
                            } else {
                                std::cout << "OUT: " << program[instruction_pointer + 1] << "\n";
                            }
                            break;
                    }
                }else{
                    if(program[instruction_pointer + 1] != 0){
                        std::cout << "NON Zero: " << prev_instruction << "\n";
                    } else {
                        std::cout << "OUT: " << program[instruction_pointer + 1] << "\n";
                    }
                }
                instruction_pointer += branch_table[4];
                break;
            }
        }
    }
}

int day_5_part_1() {
    //auto program = load_updated_memory();
    //run_test(program);
    IntCodeComputer icc = IntCodeComputer("res/day5test.txt");
    icc.memory_dump();
    exit(1);

    return 0;
}

int day_5_part_2() {
    return 0;
}
