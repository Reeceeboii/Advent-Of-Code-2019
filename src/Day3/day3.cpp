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

int manhattan(const point& point){
    // calculate the manhattan distance as |a−c|+|b−d| where c and d are x and y from point
    return abs(0 - point.first) + abs(0 - point.second);
}

// load both lines from the file and return a vector containing them
std::vector<std::vector<point>> load_lines(){
    std::fstream infile("res/day3.txt");
    std::vector<std::vector<point>> lines = { std::vector<point>(),
                                                            std::vector<point>() };
    std::string s;
    int current_line = 0;
    while(getline(infile, s)){
        std::stringstream ss(s);
        std::string movement;
        point current(0, 0);
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
                    for(int x = current.first; x <= current.first + direction; ++x){
                        point new_pair(0, 0);
                        new_pair.first = x;
                        new_pair.second = current.second;
                        lines[current_line].push_back(new_pair);
                    }
                    current.first += direction;
                    break;
                } case 'L': { // x decreasing
                    std::stringstream value(movement.substr(1, movement.size()));
                    value >> direction;
                    for(int x = current.first; x >= current.first - direction; --x){
                        point new_pair(0, 0);
                        new_pair.first = x;
                        new_pair.second = current.second;
                        lines[current_line].push_back(new_pair);
                    }
                    current.first -= direction;
                    break;
                } case 'U': { // y increasing
                    std::stringstream value(movement.substr(1, movement.size()));
                    value >> direction;
                    for(int y = current.second; y <= current.second + direction; ++y){
                        point new_pair(0, 0);
                        new_pair.first = current.first;
                        new_pair.second = y;
                        lines[current_line].push_back(new_pair);
                    }
                    current.second += direction;
                    break;
                } case 'D': { // y decreasing
                    std::stringstream value(movement.substr(1, movement.size()));
                    value >> direction;
                    for(int y = current.second; y >= current.second - direction; --y){
                        point new_pair(0, 0);
                        new_pair.first = current.first;
                        new_pair.second = y;
                        lines[current_line].push_back(new_pair);
                    }
                    current.second -= direction;
                    break;
                }
            }
        }
        ++current_line;
    }

    // std::unique can be used to remove duplicate coordinates counted when lines make a turn
    // I could do this when reading them but I'm too lazy for that
    lines[0].erase(std::unique(lines[0].begin(), lines[0].end()), lines[0].end());
    lines[1].erase(std::unique(lines[1].begin(), lines[1].end()), lines[1].end());

    return lines;
}

// carry out a set intersection of the two vectors of points
std::vector<point> intersection(std::vector<point>& set_a, std::vector<point>& set_b){
    std::vector<point> result;
    std::sort(set_a.begin(), set_a.end());
    std::sort(set_b.begin(), set_b.end());

    std::set_intersection(set_a.begin(), set_a.end(), set_b.begin(), set_b.end(),
                          std::back_inserter(result));

    result.erase(std::remove_if(result.begin(), result.end(),
                                               [](const point& p){
                                                   return p.first == 0 && p.second == 0;
                                               }), result.end());
    return result;
}

int day_3_part_1(){
    // load the lines and intersect them to get a vector of intersections
    auto lines = load_lines();
    std::vector<point> intersecting_elements = intersection(lines[0], lines[1]);

    // find smallest manhattan distance out of all of the intersections
    int min = std::numeric_limits<int>::max();
    for(auto& pair: intersecting_elements){
        int man = manhattan(pair);
        if(man < min) min = man;
    }

    return min;
}

int day_3_part_2(){
    auto lines = load_lines();
    // copies to not be affected by sorting
    std::vector<point> original_w1 = lines[0];
    std::vector<point> original_w2 = lines[1];
    // get vector of all intersections
    std::vector<point> intersecting_elements = intersection(lines[0], lines[1]);

    // find the intersection that takes the smallest step sum of both wires to reach
    std::vector<long> steps;
    for(auto& pair: intersecting_elements){
        auto l1_it = std::find(original_w1.begin(), original_w1.end(), pair);
        auto l2_it = std::find(original_w2.begin(), original_w2.end(), pair);
        steps.push_back(std::distance(original_w1.begin(), l1_it) + std::distance(original_w2.begin(), l2_it));
    }

    return *std::min_element(steps.begin(), steps.end());
}
