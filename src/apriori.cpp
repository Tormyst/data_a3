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

std::vector<std::vector<FrequentSet>> getFrequentSets(std::shared_ptr<Database> db, int min_sup){
    // Welcome to this mess of a function.
    // frequencies will be the output, an vector of vectors of the sets sorted by size for speed here and later.
    std::vector<std::vector<FrequentSet>> frequencies;
    frequencies.push_back(db->getFirstFrequentSets(min_sup));
    // Current is the index of the last completed set.
    int current = 0;
    while(current + 1 < db->colCount){
        frequencies.push_back(std::vector<FrequentSet>());
        // Itterator through every pair.  Only 1 pair will be able to join to produce a given set, all others will give the null set.
        for(auto first_f = frequencies[current].begin(); first_f != frequencies[current].end(); first_f++){
            auto second_f = first_f;// start at next
            for(second_f++; second_f != frequencies[current].end(); second_f++){
                FrequentSet combination = first_f->combine(*second_f);
                if(!FrequentSet::isNull(combination)) {
                    // Count parents to ensure database will not need to be polled.
                    // There should be as many parents, as elements in the set.
                    int parents = 0;
                    for(auto set:frequencies[current])
                        if(combination.isParent(set))
                            parents++;
                    if(parents < current + 2) // Why is this +2? Well, 1 for zero indexing frequencies, and 1 because current is one behind of the next generation.
                        continue;
                    // Finnally compute from database, and add to the set.
                    db->setCount(combination);
                    if(combination.getFrequency() >= min_sup) {
                        frequencies[current+1].push_back(combination);
                    }
                }
            }
        }
        // Logic for ending early in the case that not enough sets exist.
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
    // Rule generation follows a very similer process as above, however it is simpler.
    std::vector<Rule> retVal;
    std::vector<Rule> currentLevel = getFirstRules(db, root, min_con);
    std::vector<Rule> nextLevel;
    while(currentLevel.size() > 0) {
        // Double loop pair for the joins again.
        for (auto first_f = currentLevel.begin(); first_f != currentLevel.end(); first_f++) {
            auto second_f = first_f;// start at next
            for (second_f++; second_f != currentLevel.end(); second_f++) {
                // The join operation will join the tails of the rules leading.
                // Checking the confidence is faster then checking the parents, as we are sure to do no database checks.
                // The database object stores all the preformed checks, and we take advantage of this here.
                Rule combination = first_f->combine(db, *second_f);
                if (combination.getConfidence() > min_con) { // Null confidence will always be less.
                    nextLevel.push_back(combination);
                }
            }
        }
        // What is current goes to the past, what is future goes to the present, and the future is a clean slate.
        std::move(currentLevel.begin(), currentLevel.end(), std::back_inserter(retVal));
        currentLevel = nextLevel;
        nextLevel.clear();
    }
    return retVal;
}

std::vector<Rule> apriori(std::shared_ptr<Database> db, double min_sup_f, double min_con) {
    long min_sup = long(std::ceil(min_sup_f * db->tuppleCount()));

    std::vector<std::vector<FrequentSet>> sets = getFrequentSets(db, min_sup);
//    std::cout << "Sets: " << sets.size() << std::endl;
//    for(int i = 0; i < sets.size(); i++){
//        std::cout << "set " << i << ": " << sets[i].size() << std::endl;
//    }

    std::vector<Rule> rules;
    for(int i = 1; i < sets.size(); i++){
        for(auto frequentSet: sets[i]){
            std::vector<Rule> r = getRules(db, frequentSet, min_con);
            rules.insert(rules.end(), r.begin(), r.end());
        }
    }

//    std::cout << "Rules count: " << rules.size() << std::endl;
    return rules;
}

