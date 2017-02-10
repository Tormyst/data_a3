//
// Created by Raphael Bronfman-Nadas on 2017-02-09.
//

#include "rule.h"

Rule::Rule() : confidence(-1) {}

Rule::Rule(std::shared_ptr<Database> db, FrequentSet tail, FrequentSet combined): tail(tail), combined(combined){
    head = combined.remaining(tail);
    db->setCount(head);
    confidence = double(combined.getFrequency()) / head.getFrequency();
}

double Rule::getConfidence() const {return confidence;}
double  Rule::getFrequencyCount() const {return combined.getFrequency();}

std::vector<Rule> getFirstRules(std::shared_ptr<Database> db, FrequentSet root) {
    std::vector<Rule> retVal;
    std::vector<intpair> rootFilters = root.getRawFilters();
    for(auto filter : rootFilters) {
        retVal.push_back(Rule(db, FrequentSet(filter.first,filter.second, 0), root));
    }
    return retVal;
}