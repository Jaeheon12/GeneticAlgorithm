//
// Created by jaeheon on 2019-03-14.
//

#ifndef GENETICALGORITHM_CITY_HPP
#define GENETICALGORITHM_CITY_HPP

#define MAX_X 1000
#define MAX_Y 1000

#include <iostream>
#include <map>

using namespace std;

class City {
public:
    char name;
    double x, y;


    City();
    City(char name, double x, double y);

    bool operator==(const City &other);
};


#endif //GENETICALGORITHM_CITY_HPP
