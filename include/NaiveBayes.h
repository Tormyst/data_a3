//
// Created by Raphael Bronfman-Nadas on 2017-03-19.
//

#ifndef DATA_A5_NAIVEBAYES_H
#define DATA_A5_NAIVEBAYES_H

#include "database.h"

namespace NaiveBayes {
    typedef std::vector<std::pair<std::vector<std::vector<double>>,double>> bayesTable;

    bayesTable Setup(std::shared_ptr<Database> &db, int target);

    int predict(const bayesTable& b, tupple t, int target);

};


#endif //DATA_A5_NAIVEBAYES_H
