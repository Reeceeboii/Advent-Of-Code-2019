//
// Created by reece on 02/12/2019.
//


#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

int day_1_part_1(){
    std::fstream infile("day1.txt");
    std::string s;
    int total = 0;
    while(getline(infile, s)){
        double temp = 0;
        std::stringstream ss(s);
        ss >> temp;
        total += static_cast<int>(floor(temp / 3)) - 2;
    }
    return total;
}

int day_1_part_2(){
    std::fstream infile("day1.txt");
    std::string s;
    int total = 0;
    while(getline(infile, s)){
        double temp = 0;
        std::stringstream ss(s);
        ss >> temp;
        temp = static_cast<int>(floor(temp / 3) - 2);
        while(temp > 0){
            total += static_cast<int>(temp);
            temp = floor(temp / 3) - 2;
        }
    }
    return total;
}