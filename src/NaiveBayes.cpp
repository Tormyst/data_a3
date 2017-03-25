//
// Created by Raphael Bronfman-Nadas on 2017-03-19.
//
#include <limits>
#include <iostream>

#include "NaiveBayes.h"
#include "frequentSet.h"
#define M 1.0

using namespace NaiveBayes;

// Do you wish that you had a bayesTable, but saddly the data shop is out of tables?
// Well, this function will give you one.
// Will it be right?
// Will it be left?
// It will be a table.  So at least you will know that.
bayesTable NaiveBayes::Setup(std::shared_ptr<Database> &db, int target) {
    bayesTable b;
    // For each target value
    for (int c = 0; c < db->getClassUniqueCount(target); ++c) {
        std::pair<std::vector<std::vector<double>>,double> classifierSet;
        // For each col in the data
        for (int i = 0; i < db->colCount; ++i) {
            std::vector<double> col(db->getClassUniqueCount(i));
            if (i != target) {
                // For each value
                for (int j = 0; j < db->getClassUniqueCount(i); ++j) {
                    FrequentSet f(target, c, i, j);
                    db->setCount(f);
                    // col[j] = static_cast<double>(f.getFrequency()) / db->getCount(target, c);
                    col[j] = log(
                            (f.getFrequency() + (M * (1.0 / db->getClassUniqueCount(i))))
                            /
                            (db->getCount(target, c) + M)
                    );

                }
            }
            classifierSet.first.push_back(col);
        }
        // WHy recompute this later?
        classifierSet.second = log((static_cast<double>(db->getCount(target, c)) + M) / (db->tuppleCount() + M));
        b.push_back(classifierSet);
    }
    return b;
}

// Predicting things tends to be dificult.
// Such functions are few and far bewteen, this happens to be one of them.
int NaiveBayes::predict(const bayesTable& b, tupple t, int target) {
    double max = -std::numeric_limits<double>::infinity();
    int maxIndex = -1;
    for(int index = 0; index < b.size(); index++) {
        double val = 1;
        for(int col = 0; col < t->size(); col++) {
            if(col != target)
            {
//                std::cout << val << "*" << b[index][col][(*t)[col]] << "(" <<  col << "," << (*t)[col] <<")";
                val += b[index].first[col][(*t)[col]];
            }
        }
        val += b[index].second;
        if(val > max){
            maxIndex = index;
            max = val;
        }
    }
    return maxIndex;
}

