//
// Created by Raphael Bronfman-Nadas on 2017-02-07.
//

#include "frequentSet.h"

#include <sstream>

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

unsigned long FrequentSet::size() const {
    return filters.size();
}

std::vector<int> FrequentSet::getFilter(int size){
    std::vector<int> retFilter(size, -1);
    for(auto f : filters){
        retFilter[f.first] = f.second;
    }
    return retFilter;
}

std::vector<intpair> FrequentSet::getRawFilters() const {
    return filters;
}

void FrequentSet::addFilter(intpair filter) {
    filters.push_back(filter);
    sort(filters.begin(), filters.end());
    frequency = 0;
}

FrequentSet FrequentSet::remaining(FrequentSet other) const{
    std::vector<intpair> f;
    for(auto myFilter : filters){
        if(std::find(other.filters.begin(), other.filters.end(), myFilter) == other.filters.end())
            f.push_back(myFilter);
    }
    return FrequentSet(f);
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

std::string FrequentSet::hashString() const {
    std::stringstream s;
    for(auto f: filters){
        s << f.first << "," << f.second << ";";
    }
    std::string outS;
    s >> outS;
    return outS;
}

FrequentSet::FrequentSet(std::vector<intpair> filters_in, intpair newFilter): frequency(0), filters(filters_in){
    filters.push_back(newFilter);
    sort(filters.begin(), filters.end());
}

FrequentSet::FrequentSet(std::vector<intpair> filters) :
        frequency(0),
        filters(filters) {}

bool FrequentSet::isNull(FrequentSet f){
    return f.getFrequency() < 0;
}