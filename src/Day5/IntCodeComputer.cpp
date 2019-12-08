//
// Created by reece on 07/12/2019.
//

#include "IntCodeComputer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

// construct a new IntCode computer object
IntCodeComputer::IntCodeComputer(const std::string &program_location){
    load_memory(program_location);
    instruction_ptr = 0;
    system_running = true;
}

// load memory up in the system using data file
void IntCodeComputer::load_memory(const std::string& program_location){
    std::fstream infile(program_location);
    if(!infile) { std::cout << "ERR reading: " << program_location << "\n"; exit(1); }
    std::string s;
    while(getline(infile, s, ',')){
        int token;
        std::stringstream ss(s);
        ss >> token;
        memory.push_back(token);
    }
}
// get given an opcode and assign
void IntCodeComputer::interpret_opcode(const int opcode){
    oap.opcode = opcode % 10; // extract last digit of opcode
    switch(oap.opcode){
        case ADD:
        case MULT:
        case JUMP_IF_TRUE:
        case JUMP_IF_FALSE:
        case LESS_THAN:
        case EQUALS:
            oap.param_modes[0] = (opcode / 100) % 10;
            oap.param_modes[1] = (opcode / 1000) % 10;
            break;
        case OUT:
            oap.param_modes[0] = opcode / 100 % 10;
            break;
        case HALT:
            oap.opcode = HALT;
            break;
    }
}

// using the current instruction's opcode affect memory accordingly
int IntCodeComputer::run_opcode(int operand_1, int operand_2){
    switch(oap.opcode){
        case ADD: return operand_1 + operand_2;
        case MULT: return operand_1 * operand_2;
        case LESS_THAN: return operand_1 < operand_2;
        case EQUALS: return operand_1 == operand_2;
        default: throw std::invalid_argument("Invalid opcode in run_opcode");
    }
}

// execute a single instruction and increment the instruction pointer accordingly
void IntCodeComputer::step(){
    oap = op_and_params();
    interpret_opcode(memory[instruction_ptr]); // set up this step's opcode and param modes
    switch(oap.opcode){
        case ADD:
        case MULT:
        case JUMP_IF_TRUE:
        case JUMP_IF_FALSE:
        case LESS_THAN:
        case EQUALS: {
            // assign values according to addressing modes for this instruction
            int param1_val = oap.param_modes[0] == 1 ? memory[instruction_ptr + 1] : memory[memory[instruction_ptr + 1]];
            int param2_val = oap.param_modes[1] == 1 ? memory[instruction_ptr + 2] : memory[memory[instruction_ptr + 2]];

            if (oap.opcode != JUMP_IF_TRUE && oap.opcode != JUMP_IF_FALSE) {
                memory[memory[instruction_ptr + 3]] = run_opcode(param1_val, param2_val);
                instruction_ptr += 4;
            }else{
                if(oap.opcode == JUMP_IF_TRUE){
                    param1_val > 0 ? instruction_ptr = param2_val : instruction_ptr += 3;
                }else if(oap.opcode == JUMP_IF_FALSE){
                    param1_val == 0 ? instruction_ptr = param2_val : instruction_ptr += 3;
                }else if(oap.opcode == LESS_THAN){
                    memory[memory[instruction_ptr + 2]] = run_opcode(param1_val, param2_val);
                    instruction_ptr += 3;
                }else if(oap.opcode == EQUALS){
                    memory[memory[instruction_ptr + 2]] = run_opcode(param1_val, param2_val);
                    instruction_ptr += 3;
                }
            }
            break;
        }
        case IN: { // IN is always direct mode
            std::cout << "INPUT: ";
            std::cin >> memory[memory[instruction_ptr + 1]];
            instruction_ptr += 2;
            break;
        }
        case OUT: {
            int param1_val = oap.param_modes[0] ? memory[instruction_ptr + 1] : memory[memory[instruction_ptr + 1]];
            if (memory[instruction_ptr + 2] == 99) {
                std::cout << "OUTPUT: " << param1_val;
            }
            instruction_ptr += 2;
            break;
        }
        case HALT: {
            system_running = false;
            break;
        }
    }
}

// run the system until a HALT signal is encountered
void IntCodeComputer::execute(){
    while(system_running) step();
}

void day_5_part_1() {
    IntCodeComputer icc = IntCodeComputer("res/day5.txt");
    icc.execute();
}

void day_5_part_2() {
    IntCodeComputer icc = IntCodeComputer("res/day5.txt");
    icc.execute();
}
