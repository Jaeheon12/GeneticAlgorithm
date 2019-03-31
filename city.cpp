//
// Created by jaeheon on 2019-03-14.
//

#include <iostream>
#include <map>
#include <iterator>

using namespace std;

#include "city.hpp"

City::City() {
    x = -1;
    y = -1;
}

City::City(char name, double x, double y) {
    this->name = name;
    this->x = x;
    this->y = y;
}

bool City::operator==(const City &other) {
    return name == other.name;
}