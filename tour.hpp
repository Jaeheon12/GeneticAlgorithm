//
// Created by jaeheon on 2019-03-15.
//

#ifndef GENETICALGORITHM_TOUR_HPP
#define GENETICALGORITHM_TOUR_HPP

#define MUTATION_RATE 12.5
#include <vector>

class City;

class Tour {
public:
    vector<City*> *cities;
    double cost;

    Tour();
    Tour(vector<City*> *cities);
    Tour(Tour *parent1, Tour *parent2, int crossPoint, bool crossLeft);

    void mutate();

    bool operator==(const Tour &other);
    bool operator!=(const Tour &other);
    friend ostream &operator << (ostream &os, const Tour & m);

private:
    void calculateCost();
    bool checkIfAlreadyExists(City *city);
    double dist(City *a, City *b);
};

class Compare {
public:
    bool operator() (Tour *a, Tour *b);
};
#endif //GENETICALGORITHM_TOUR_HPP
