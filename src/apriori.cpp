#include <iostream>
#include <cmath>

#include "apriori.h"

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

void apriori(std::shared_ptr<Database> db, double min_sup_f, double min_con_f) {
    long min_sup = long(std::ceil(min_sup_f * db->tuppleCount()));
    long min_con = long(std::ceil(min_con_f * db->tuppleCount()));

    std::vector<FrequentSet> frequencies_current = db->getFirstFrequentSets();
    std::vector<FrequentSet> frequencies_next;
    int i = 1;
    while(i < db->colCount){
        for(auto first_f = frequencies_current.begin(); first_f != frequencies_current.end(); first_f++){
            for(auto second_f = first_f; second_f != frequencies_current.end(); second_f++){
                FrequentSet combination = first_f->combine(*second_f);
                if(!FrequentSet::isNull(combination)) {
                    combination = db->setCount(combination);
                    if(combination.getFrequency() >= min_sup) {
                        frequencies_next.push_back(combination);
                        std::cout << "Combining sets with a value of "
                                  << double(combination.getFrequency()) / db->tuppleCount()
                                  << ", and a filter of "
                                  << combination.getFilter(db->colCount) << std::endl;
                    }
                }
            }
        }
        if(frequencies_current.size() > 1){
            frequencies_current = frequencies_next;
            frequencies_next.clear();
        }
        else break;
        i++;
    }
}
