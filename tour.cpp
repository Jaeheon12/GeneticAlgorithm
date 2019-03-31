//
// Created by jaeheon on 2019-03-15.
//

#include <cmath>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#include "city.hpp"
#include "tour.hpp"


Tour::Tour() {
    this->cities = NULL;
    cost = -1;
}

Tour::Tour(vector<City*> *cities) {
    this->cities = cities;
    calculateCost();
}

/***
 *
 * When Tour is goes into the parametrized constructor, cross starts based on the two parent tours
 *
 */
Tour::Tour(Tour *parent1, Tour *parent2, int crossPoint, bool crossLeft) {
    vector<City*> *vec1 = parent1->cities;
    vector<City*> *vec2 = parent2->cities;

    cities = new vector<City *>;

    for (int i = 0; i < crossPoint; i++) {
        cities->push_back(vec1->at(i));
    }
    for (int i = crossPoint; i < vec2->size(); i++) {
        if (!checkIfAlreadyExists(vec2->at(i))) {
            cities->push_back(vec2->at(i));
        }
        else {
            for (int j = 0; j < vec2->size(); j++) {
                if (!checkIfAlreadyExists(vec2->at(j))) {
                    cities->push_back(vec2->at(j));
                    break;
                }
            }
        }

    }
    if (!crossLeft) {
        reverse(cities->begin(), cities->end());
    }
    calculateCost();

}

/***
 *
 * This is used for checking if there is a city already in the cities vector
 * to avoid duplicate cities in one tour
 *
 */
bool Tour::checkIfAlreadyExists(City *city) {
    for (int i = 0; i < cities->size(); i++) {
        if (*cities->at(i) == *city) {
            return true;
        }
    }
    return false;
}

/***
 *
 * going thru every citiy in the tour, swap i and i + 1 cities at a percentage of "MUTATION_RATE"
 *
 */
void Tour::mutate() {
    srand (time(NULL));

    for (auto it = cities->begin(); it != cities->end(); it++) {
        int randNum = rand() % 100 + 1;
        if (randNum <= MUTATION_RATE) {
            if (it == cities->end() - 1) {
                iter_swap(it, cities->begin());
            }
            else {
                iter_swap(it, it + 1);
            }
        }
    }
    calculateCost();
}


void Tour::calculateCost() {
    double sum = 0.00;
    for (int i = 0; i < cities->size(); i++) {
        if (i == cities->size() - 1) {
            City *city1 = cities->at(i);
            City *city2 = cities->at(0);
            sum += dist(city1, city2);
        }
        else {
            City *city1 = cities->at(i);
            City *city2 = cities->at(i + 1);
            sum += dist(city1, city2);
        }
    }
    cost = sum;
}

double Tour::dist(City *a, City *b) {
    return sqrt ((b->x - a->x)*(b->x - a->x) + (b->y - a->y)*(b->y - a->y));
}

bool Tour::operator==(const Tour &other) {
    for (int i = 0; i < cities->size(); i++) {
        if (cities->at(i) != other.cities->at(i)) {
            return false;
        }
    }
    return true;
}

bool Tour::operator!=(const Tour &other) {
    return !(*this == other);
}

ostream &operator << (ostream &os, const Tour & m) {
    for (int i = 0; i < m.cities->size(); i++) {
        cout << m.cities->at(i)->name;
        if (i == m.cities->size() - 1) {
            cout << endl;
        }
        else {
            cout << ", ";
        }
    }
//    cout << m.cost << endl;
    return os;
}

bool Compare::operator() (Tour *a, Tour *b) {
    return b->cost > a->cost;
}