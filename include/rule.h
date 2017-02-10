//
// Created by Raphael Bronfman-Nadas on 2017-02-09.
//

#ifndef DATA_A3_RULE_H
#define DATA_A3_RULE_H

#include "frequentSet.h"
#include "database.h"

class Rule {
private:
    FrequentSet head;
    FrequentSet tail;
    FrequentSet combined;
    double confidence;
public:
    Rule();
    Rule(std::shared_ptr<Database> db, FrequentSet tail, FrequentSet combined);
    double getConfidence() const;
    double getFrequencyCount() const;

    Rule combine(Rule other) const;

};

std::vector<Rule> getFirstRules();


#endif //DATA_A3_RULE_H
