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
// Very similer to the frequency set combine, this join acts on the tail lists, and tries to combine them.
// TODO check if I can just remove the bulk of this.
Rule Rule::combine(std::shared_ptr<Database> db, Rule other) const {
    std::vector<intpair> tailList = this->tail.getRawFilters();
    std::vector<intpair>  otherTailList = other.tail.getRawFilters();
    if( tailList.size() != otherTailList.size() || head.size() < 2)
        return Rule(); // Null value
    int i;
    for(i = 0; i < tailList.size() - 1; i++){
        if(tailList[i] != otherTailList[i])
            return Rule(); // Null value
    }
    if(tailList[i] == otherTailList[i] || tailList[i].first == otherTailList[i].first)
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