//
// Created by Raphael Bronfman-Nadas on 2017-02-07.
//

#include "frequentSet.h"

FrequentSet::FrequentSet() : frequency(-1){}

FrequentSet::FrequentSet(int col, int value, int frequency) :
        frequency(frequency) {
    filters.push_back(intpair(col, value));
}

int FrequentSet::getFrequency() const{
    return frequency;
}

void FrequentSet::setFrequency(int set) {
    frequency = set;
}

std::vector<int> FrequentSet::getFilter(int size){
    std::vector<int> retFilter(size, -1);
    for(auto f : filters){
        retFilter[f.first] = f.second;
    }
    return retFilter;
}

FrequentSet FrequentSet::combine(FrequentSet other) const {
    if( this->filters.size() != other.filters.size() )
        return FrequentSet(); // Null value
    int i;
    for(i = 0; i < this->filters.size() - 1; i++){
        if(this->filters[i] != other.filters[i])
            return FrequentSet(); // Null value
    }
    if(this->filters[i] == other.filters[i] || this->filters[i].first == other.filters[i].first)
        return FrequentSet(); // Null value
    return FrequentSet(this->filters, other.filters[i]);
}

FrequentSet::FrequentSet(std::vector<intpair> filters_in, intpair newFilter): frequency(0), filters(filters_in){
    filters.push_back(newFilter);
    sort(filters.begin(), filters.end());
}

bool FrequentSet::isNull(FrequentSet f){
    return f.getFrequency() < 0;
}