//
// Created by Raphael Bronfman-Nadas on 2017-02-09.
//

#include "rule.h"
// Null constructor
Rule::Rule() : confidence(-1) {}

Rule::Rule(std::shared_ptr<Database> db, FrequentSet tail, FrequentSet combined): tail(tail), combined(combined) {
    head = combined.remaining(tail);
    db->setCount(head);
    confidence = double(combined.getFrequency()) / head.getFrequency();
}

double Rule::getConfidence() const {return confidence;}
double  Rule::getFrequencyCount() const {return combined.getFrequency();}
// Checks if there are enough filters to move one to the tail. Checks if the tails combine.
// We are good.  Valid rule then.
Rule Rule::combine(std::shared_ptr<Database> db, Rule other) const {
    FrequentSet f;
    if( head.size() < 2)
        return Rule(); // Null value
    f = tail.combine(other.tail);
    if(FrequentSet::isNull(f))
        return Rule(); // Null value
    return Rule(db, tail.combine(other.tail), combined);
}

void Rule::prittyPrint(std::ostream &fileOut, std::shared_ptr<Database> db) {
    fileOut << " { ";
    bool notFirst = false;
    for(auto f : head.getRawFilters()){
        if(notFirst) fileOut << ", ";
        else notFirst = true;
        db->printIntPair(fileOut, f);
    }
    fileOut << " } " << std::endl << "----> { ";
    notFirst = false;
    for(auto f : tail.getRawFilters()){
        if(notFirst) fileOut << ", ";
        else notFirst = true;
        db->printIntPair(fileOut, f);
    }
    fileOut << " } " << std::endl;
}
// All rules need to start somewhere, and that start is a root node.
std::vector<Rule> getFirstRules(std::shared_ptr<Database> db, FrequentSet& root, double min_con) {
    std::vector<Rule> retVal;
    std::vector<intpair> rootFilters = root.getRawFilters();
    for(auto filter : rootFilters) {
        Rule r = Rule(db, FrequentSet(filter.first,filter.second, 0), root);
        if(r.getConfidence() >= min_con)
            retVal.push_back(r);
    }
    return retVal;
}