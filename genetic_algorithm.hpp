//
// Created by jaeheon on 2019-03-14.
//

#ifndef GENETICALGORITHM_GENETIC_ALGORITHM_HPP
#define GENETICALGORITHM_GENETIC_ALGORITHM_HPP

#define TOTAL_NUM_CITIES 32
#define POPULATION_OF_TOURS 32

#define NUMBER_OF_PARENTS 2
#define PARENT_POOL_SIZE POPULATION_OF_TOURS

#define MAX_NUM_OF_ELITES 4

#define IMPROVEMENT_RATE 30

#define CROSS_FROM_LEFT true
#define CROSS_FROM_RIGHT false
#define CROSS_POINT 16

#include <set>
#include <queue>
#include <vector>

class Compare;
class Tour;

class GeneticAlgorithm {
public:
    GeneticAlgorithm();

    void showSet(multiset<Tour *, Compare> sset);
};


#endif //GENETICALGORITHM_GENETIC_ALGORITHM_HPP
