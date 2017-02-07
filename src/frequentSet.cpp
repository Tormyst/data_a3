//
// Created by Raphael Bronfman-Nadas on 2017-02-07.
//

#include "frequentSet.h"
using namespace std;

FrequentSet::FrequentSet(int col, int value, int frequency) :
        frequency(frequency) {
    filters.push_back(intpair(col, value));
}

vector<int> FrequentSet::getFilter(int size){
    vector<int> retFilter(size, -1);
    for(auto f : filters){
        retFilter[f.first] = f.second;
    }
    return retFilter;
}

bool FrequentSet::addFilter(int col, int value) {
    for(auto f : filters){
        if(f.first == col)
            return false;
    }
    filters.push_back(intpair(col, value));
    return true;
}

unique_ptr<FrequentSet> FrequentSet::combine(FrequentSet other) {
    if( this->filters.size() != other.filters.size() )
        return nullptr;
    int i;
    for(i = 0; i < this->filters.size() - 1; i++){
        if(this->filters[i] != other.filters[i])
            return nullptr;
    }
    if(this->filters[i] == other.filters[i])
        return nullptr;
    return unique_ptr<FrequentSet>(new FrequentSet(this->filters, other.filters[i]));
}

FrequentSet::FrequentSet(vector<intpair> filters_in, intpair newFilter): filters(filters_in){
    filters.push_back(newFilter);
    sort(filters.begin(), filters.end());
}