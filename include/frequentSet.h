//
// Created by Raphael Bronfman-Nadas on 2017-02-07.
//

#ifndef DATA_A3_FREQUENTSET_H
#define DATA_A3_FREQUENTSET_H

#include <vector>
#include <memory>

typedef std::pair<int,int> intpair;

class FrequentSet {
public:
    int frequency;
private:
    std::vector<intpair> filters;

public:
    FrequentSet(int col, int value, int frequency);
    std::vector<int> getFilter(int size); // The size of the array to make.
    bool addFilter(int col, int value);
    std::unique_ptr<FrequentSet> combine(FrequentSet other);

private:
    FrequentSet(std::vector<intpair> filters, intpair newFilter);
};


#endif //DATA_A3_FREQUENTSET_H
