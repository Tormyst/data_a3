//
// Created by Raphael Bronfman-Nadas on 2017-02-08.
//

#ifndef DATA_A3_APRIORI_H
#define DATA_A3_APRIORI_H

#include <memory>

#include "database.h"
#include "rule.h"

std::vector<Rule> apriori(std::shared_ptr<Database> db, double min_sup, double min_con);

#endif //DATA_A3_APRIORI_H
