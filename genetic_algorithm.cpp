#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <iterator>
#include <queue>
#include <set>

using namespace std;

#include "city.hpp"
#include "tour.hpp"
#include "genetic_algorithm.hpp"

GeneticAlgorithm::GeneticAlgorithm() {

    vector<City*> *master = new vector<City*>();

    cout << "master list : " << endl;
    int cityNameChar = 65;
    for (int i = 0; i < TOTAL_NUM_CITIES; i++) {
        double x = rand() % 1000;
        double y = rand() % 1000;

        if (cityNameChar == 90) {
            cityNameChar += 7;
        }
        master->push_back(new City(cityNameChar++, x, y));
        cout << master->at(i)->name << "::(" << x << "," << y << ")" << endl;
    }
    cout << endl;

    multiset<Tour *, Compare> ancestorSet;

    vector<vector<City*>*> *popVectors = new vector<vector<City*>*>;
    for (int i = 0; i < POPULATION_OF_TOURS; i++) {
        popVectors->push_back(new vector<City*>);

        for (int j = 0; j < TOTAL_NUM_CITIES; j++) {
            popVectors->at(i)->push_back(master->at(j));
        }

        random_shuffle(popVectors->at(i)->begin(), popVectors->at(i)->end());

        Tour *tour = new Tour(popVectors->at(i));
        ancestorSet.insert(tour);
    }

    cout << "========================================================================" << endl;
    cout << " ancestorSet" << endl;
    cout << "========================================================================" << endl;
    showSet(ancestorSet);
    Tour *initElite = *ancestorSet.begin();
    cout << "Processing ... " << endl << endl << endl;
    bool reachedPoint = false;
    double bestImprovementRate = 0.00;
    int bestImprovementRateIndex = 0;
    Tour *bestImprovementTour = NULL;

    int totalIndex = 0;
    while (totalIndex < 1000) {
        multiset<Tour *, Compare> descendantSet;

        Tour *elite = *ancestorSet.begin();
        Tour *elite2 = *next(ancestorSet.begin(), 1);
        Tour *elite3 = *next(ancestorSet.begin(), 2);
        Tour *elite4 = *next(ancestorSet.begin(), 3);

        double curImprovementRate = 100.00 - (elite->cost / initElite->cost * 100.00);
        if (curImprovementRate > IMPROVEMENT_RATE) {
            cout << "iteration" << totalIndex << " : " << endl;
            cout << "Currently Achieved the Desired Improvement. Terminating the Iteration ... " << endl;
            reachedPoint = true;
            break;
        }

        if (curImprovementRate > bestImprovementRate) {
            bestImprovementRate = curImprovementRate;
            bestImprovementRateIndex = totalIndex;
            bestImprovementTour = elite;
        }

        cout << "iteration" << totalIndex << " : " << endl;
        cout << "Current Elite Route   - " << *elite << "The Route's Distance : " << elite->cost << endl;
        cout << "Current Improvement   - " << curImprovementRate << "%" << endl;
        cout << "Best Improvement Rate - " << bestImprovementRate << "%" << endl;
        cout << "Desired Improvement is not achieved yet (desired:" << IMPROVEMENT_RATE << "%)" << endl << endl;

        descendantSet.insert(elite);
        descendantSet.insert(elite2);
        descendantSet.insert(elite3);
        descendantSet.insert(elite4);

        int ancesLength = ancestorSet.size();
        int index = 0;
        for (int x = 0; x < POPULATION_OF_TOURS - MAX_NUM_OF_ELITES; x++) {
            int motherIndex = rand() % (POPULATION_OF_TOURS);
            int fatherIndex = rand() % (POPULATION_OF_TOURS);

            multiset<Tour *>::iterator iterForMother = next(ancestorSet.begin(), motherIndex);

            Tour *mother = *iterForMother;

            multiset<Tour *>::iterator iterForFather = next(ancestorSet.begin(), fatherIndex);

            Tour *father = *iterForFather;

            Tour *child = new Tour(mother, father, CROSS_POINT, (totalIndex % 2 == 0) ? CROSS_FROM_LEFT : CROSS_FROM_RIGHT);
            descendantSet.insert(child);
        }

        multiset<Tour *, Compare> descendantSetAfterMutation;

        for (auto it = descendantSet.begin(); it != descendantSet.end(); it++) {
            (*it)->mutate();
            descendantSetAfterMutation.insert(*it);
        }

        ancestorSet = descendantSetAfterMutation;
        totalIndex++;
    }
    cout << "========================================================================" << endl;
    cout << " ResultSet" << endl;
    cout << "========================================================================" << endl;
    showSet(ancestorSet);

    cout << "Report :" << endl;
    Tour *curElite = *ancestorSet.begin();
    cout << "Iteration Number : " << totalIndex << endl;

    cout << "The base elite tour route : " << *initElite;
    cout << "The Distance of the base elite tour : " << initElite->cost << endl << endl;

    if (reachedPoint) {
        cout << "The best elite tour route : " << *curElite;
        cout << "The Distance of the Current Tour : " << curElite->cost << endl << endl;
        cout << "Improvement Rate : " << 100 - (curElite->cost/initElite->cost*100) << "% => Achieved the Desired Improvement " << IMPROVEMENT_RATE << "%" << endl << endl;
    }
    else {
        cout << "Not Achieved the Desired Improvement " << IMPROVEMENT_RATE << "%" << endl;
        cout << "Best Improvement Rate is " << bestImprovementRate << "% at iteration number " << bestImprovementRateIndex << endl << endl;

        cout << "The best elite tour route : " << *bestImprovementTour;
    }
}


void GeneticAlgorithm::showSet(multiset<Tour *, Compare> sset) {
    set<Tour *, Compare>::iterator it;

    for (it=sset.begin(); it!=sset.end(); ++it)
        cout << ' ' << **it;
    cout << '\n';
}
