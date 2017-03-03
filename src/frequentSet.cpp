//
// Created by Raphael Bronfman-Nadas on 2017-02-07.
//
#include <algorithm>

#include "frequentSet.h"

#include <sstream>
// Null constructor.
FrequentSet::FrequentSet() : frequency(-1){}
// Used to create frequent sets of one value.  The frequency is expected here.
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
// Creates a vector that is all -1 except for the values specified by the filters.
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
// Given a frequent set, return a frequent set consisting of all values not given.
FrequentSet FrequentSet::remaining(FrequentSet& other) const{
    std::vector<intpair> f;
    for(auto myFilter : filters){
        if(std::find(other.filters.begin(), other.filters.end(), myFilter) == other.filters.end())
            f.push_back(myFilter);
    }
    return FrequentSet(f);
}
// Combines two sets given they can combine.
// They can combine if they only differ by the last value, and if the first value of said differing values is different.
FrequentSet FrequentSet::combine(FrequentSet& other) const {
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
// For use with retreving the count from the database.
std::string FrequentSet::hashString() const {
    std::stringstream s;
    for(auto f: filters){
        s << f.first << "," << f.second << ";";
    }
    std::string outS;
    s >> outS;
    return outS;
}

bool FrequentSet::operator ==(const FrequentSet &other) const{
    if(filters.size() != other.filters.size()) return false;
    for(int i = 0; i < filters.size();i++)
        if(filters[i] != other.filters[i])
            return false;
    return true;
}
// Checks if a given set is a parent of the current set.
bool FrequentSet::isParent(const FrequentSet &other) const {
    if(other.filters.size() != filters.size() - 1) return false;
    int differing = 0;
    int first = 0;
    int second = 0;
    while(first < filters.size() && second < other.filters.size()) {
        if (filters[first] == other.filters[second]) {
            first++;
            second++;
        }
        else if(filters[first] <= other.filters[second]) {
            first++;
            differing++;
        }
        else{
            second++;
            differing++;
        }
    }
    differing += filters.size() - first;
    differing += other.filters.size() - second;

    return differing == 1;
}
// Constructor for adding a single filter to a set.
// For use with combine.
FrequentSet::FrequentSet(std::vector<intpair> filters_in, intpair newFilter): frequency(0), filters(filters_in){
    filters.push_back(newFilter);
    sort(filters.begin(), filters.end());
}
// Creates a set from filters.
FrequentSet::FrequentSet(std::vector<intpair> filters) :
        frequency(0),
        filters(filters) {}

bool FrequentSet::isNull(FrequentSet f){
    return f.getFrequency() < 0;
}
