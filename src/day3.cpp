//
// Created by reece on 03/12/2019.
//

#include "day3.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <cmath>
#include <limits>

int manhattan(const std::pair<int, int>& point){
    // calculate the manhattan distance as |a−c|+|b−d| where c and d are x and y from point
    return abs(0 - point.first) + abs(0 - point.second);
}

int day_3_part_1(){
    std::fstream infile("res/day3.txt");
    std::vector<std::vector<std::pair<int, int>>> lines = { std::vector<std::pair<int, int>>(),
                                                         std::vector<std::pair<int, int>>() };
    std::string s;
    int current_line = 0;

    while(getline(infile, s)){
        std::stringstream ss(s);
        std::string movement;
        std::pair<int, int> curr(0, 0);
        while(getline(ss, movement, ',')){
            int direction;
            switch(movement[0]){
                /*
                     * As we're moving right (adding to x) we loop from the current x all the way until the current x
                     * plus the amount we're moving by. For each iteration, we add a new pair to the current line we're on.
                     * The y of this pair is the current y, and the x is the current loop counter.
                     *  So for example, if we're currently at 0,0 and we read R5, we will add
                     *  0,0 - 1,0 - 2,0 - 3,0 - 4,0 - 5,0 to that line's vector to represent all points we now have in that line
                     *  as a result of this movement. This is done for all directions. If you traced these coordinate pairs
                     *  on a graph you would end up with the line represented by the movements from the file.
                     *
                     *  Once we then have these coordinate pair collections, we take their intersection (points in common)
                     *  and calculate the manhattan distance for all of them. The minimum distance is returned.
                     */
                case 'R': { // x increasing
                    std::stringstream value(movement.substr(1, movement.size()));
                    value >> direction;
                    for(int x = curr.first; x <= curr.first + direction; ++x){
                        std::pair<int, int> new_pair(0, 0);
                        new_pair.first = x;
                        new_pair.second = curr.second;
                        lines[current_line].push_back(new_pair);
                    }
                    curr.first += direction;
                    break;
                } case 'L': { // x decreasing
                    std::stringstream value(movement.substr(1, movement.size()));
                    value >> direction;
                    for(int x = curr.first; x >= curr.first - direction; --x){
                        std::pair<int, int> new_pair(0, 0);
                        new_pair.first = x;
                        new_pair.second = curr.second;
                        lines[current_line].push_back(new_pair);
                    }
                    curr.first -= direction;
                    break;
                } case 'U': { // y increasing
                    std::stringstream value(movement.substr(1, movement.size()));
                    value >> direction;
                    for(int y = curr.second; y <= curr.second + direction; ++y){
                        std::pair<int, int> new_pair(0, 0);
                        new_pair.first = curr.first;
                        new_pair.second = y;
                        lines[current_line].push_back(new_pair);
                    }
                    curr.second += direction;
                    break;
                } case 'D': { // y decreasing
                    std::stringstream value(movement.substr(1, movement.size()));
                    value >> direction;
                    for(int y = curr.second; y >= curr.second - direction; --y){
                        std::pair<int, int> new_pair(0, 0);
                        new_pair.first = curr.first;
                        new_pair.second = y;
                        lines[current_line].push_back(new_pair);
                    }
                    curr.second -= direction;
                    break;
                }
            }
        }
        ++current_line;
    }

    // perform intersection
    std::vector<std::pair<int, int>> intersecting_elements;
    std::sort(lines[0].begin(), lines[0].end());
    std::sort(lines[1].begin(), lines[1].end());

    std::set_intersection(lines[0].begin(), lines[0].end(), lines[1].begin(), lines[1].end(),
                          std::back_inserter(intersecting_elements));

    // exclude 0,0
    intersecting_elements.erase(std::remove_if(intersecting_elements.begin(), intersecting_elements.end(),
                                               [](const std::pair<int, int>& p){
                                                    return p.first == 0 && p.second == 0;
                                               }), intersecting_elements.end());

    // find smallest manhattan distance
    int min = std::numeric_limits<int>::max();
    for(auto& pair: intersecting_elements){
        int man = manhattan(pair);
        if(man < min) min = man;
    }

    return min;
}
