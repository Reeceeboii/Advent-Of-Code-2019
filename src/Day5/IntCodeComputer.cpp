//
// Created by reece on 07/12/2019.
//

#include "IntCodeComputer.h"
#include <fstream>
#include <sstream>
#include <iostream>

// construct a new IntCode computer object
IntCodeComputer::IntCodeComputer(const std::string &program_location){
    load_memory(program_location);
    load_branch_table();
    instruction_pointer = prev_instruction_pointer = 0;
    is_system_running = true;
}

// load memory up in the system using data file
void IntCodeComputer::load_memory(const std::string& program_location){
    std::fstream infile(program_location);
    if(!infile){ std::cout << "ERR reading " << program_location << "\n"; exit(1);}
    std::string s;
    while(getline(infile, s, ',')){
        instruction token;
        std::stringstream ss(s);
        ss >> token;
        memory.push_back(token);
    }

}

// the number of instructions to jump after each different opcode
void IntCodeComputer::load_branch_table(){
    branch_table.insert({ 3, 2 }); // OUT
    branch_table.insert({ 4, 2 }); // IN
    branch_table.insert({ 1, 4 }); // ADD
    branch_table.insert({ 2, 4 }); // MULTIPLY
}

// print info regarding the system's current memory contents
void IntCodeComputer::memory_dump(){
    std::cout << "\n\n- MEM DUMP (SIZE: " << memory.size()*sizeof(instruction) << "b)-\n";
    for(auto instruction: memory){
        std::cout << instruction << " ";
    }
    std::cout << "\n- END MEM DUMP -\n";
}

// execute a single instruction and increment the instruction pointer accordingly
void IntCodeComputer::step() {
    std::string current_instruction = std::to_string(memory[instruction_pointer]);
    prev_instruction_pointer = instruction_pointer;
}