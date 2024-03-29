//
// Created by Raphael Bronfman-Nadas on 2017-02-05.
//

#ifndef DATA_A3_DATABASE_H
#define DATA_A3_DATABASE_H
#include <list>
#include <vector>
#include <array>
#include <string>
#include <memory>
#include <unordered_map>

#include "frequentSet.h"

class Database {
public:
    const int colCount;
private:
    std::vector<std::string> _titles;
    std::vector<std::vector<int>> _data;
    std::vector<std::vector<std::pair<std::string, int>>> _decoder;
    std::unordered_map<std::string, int> setFinder;

public:
    Database(std::vector<std::string> titles);
    const std::string decode(int col, int value) const;
    void addData(std::string s);
    void setCount(FrequentSet& set);
    const unsigned long tuppleCount() const;
    std::vector<FrequentSet> getFirstFrequentSets(int min_sup);
    void printIntPair(std::ostream &out, intpair filter);

    friend std::ostream& operator<< (std::ostream & out, const Database& data);

private:
    int encode(int col, std::string value);
};

std::ostream& operator<< (std::ostream & out, Database const& data);

#endif //DATA_A3_DATABASE_H
