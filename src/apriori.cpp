#include <iostream>
#include <cmath>

#include "apriori.h"
#include "rule.h"

std::ostream& operator<< (std::ostream &out, const std::vector<int> v){
    out << "[ ";
    bool comma = false;
    for (auto i : v){
        if(comma) out << ", ";
        else comma = true;
        out << i;
    }
    out << " ]";
    return out;
}

std::vector<std::vector<FrequentSet>> getFrequentSets(std::shared_ptr<Database> db, long min_sup){
    std::vector<std::vector<FrequentSet>> frequencies;
    frequencies.push_back(db->getFirstFrequentSets(min_sup));
    int current = 0;
    while(current + 1 < db->colCount){
        frequencies.push_back(std::vector<FrequentSet>());
        for(auto first_f = frequencies[current].begin(); first_f != frequencies[current].end(); first_f++){
            for(auto second_f = first_f; second_f != frequencies[current].end(); second_f++){
                FrequentSet combination = first_f->combine(*second_f);
                if(!FrequentSet::isNull(combination)) {
                    combination = db->setCount(combination);
                    if(combination.getFrequency() >= min_sup) {
                        frequencies[current+1].push_back(combination);
                        std::cout << "Combining sets with a value of "
                                  << double(combination.getFrequency()) / db->tuppleCount()
                                  << ", and a filter of "
                                  << combination.getFilter(db->colCount) << std::endl;
                    }
                }
            }
        }
        if(frequencies[current + 1].size() > 1){
            current++;
        }
        else {
            break;
        }
    }
    return frequencies;
}

std::vector<Rule> getRules(std::shared_ptr<Database> db, FrequentSet root, double min_con) {
    std::vector<Rule> retVal;


    return retVal;
}

void apriori(std::shared_ptr<Database> db, double min_sup_f, double min_con) {
    long min_sup = long(std::ceil(min_sup_f * db->tuppleCount()));

    std::vector<std::vector<FrequentSet>> sets = getFrequentSets(db, min_sup);
    std::cout << "Sets: " << sets.size() << std::endl;
    for(int i = 0; i < sets.size(); i++){
        std::cout << "set " << i << ": " << sets[i].size() << std::endl;
    }

    std::vector<Rule> rules;
    for(int i = 1; i < sets.size(); i++){
        for(auto frequentSet: sets[i]){
            std::vector<Rule> r = getRules(db, frequentSet, min_con);
            rules.insert(rules.end(), r.begin(), r.end());
        }
    }

    std::cout << "Rules count: " << rules.size() << std::endl;
}
