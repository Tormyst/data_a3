//
// Created by Raphael Bronfman-Nadas on 2017-02-07.
//

#ifndef DATA_A3_FREQUENTSET_H
#define DATA_A3_FREQUENTSET_H

#include <vector>
#include <memory>

typedef std::pair<int,int> intpair;

class FrequentSet {
// Variables
private:
    int frequency;
    std::vector<intpair> filters;
// Functions
public:
    FrequentSet(); // Null constructor
    FrequentSet(int col, int value, int frequency);
    int getFrequency() const;
    void setFrequency(int set);
    unsigned long size() const;
    std::vector<int> getFilter(int size); // The size of the array to make.
    std::vector<intpair> getRawFilters() const;
    void addFilter(intpair filter);
    FrequentSet remaining(FrequentSet toRemove) const;
    FrequentSet combine(FrequentSet& other) const;
    std::string hashString() const;
    bool operator ==(const FrequentSet &other) const;
    bool isParent(const FrequentSet &other) const;

private:
    FrequentSet(std::vector<intpair> filters, intpair newFilter);
    FrequentSet(std::vector<intpair> filters);
// Static
public:
    static bool isNull(FrequentSet f);

};

#endif //DATA_A3_FREQUENTSET_H
