//
// Created by Raphael Bronfman-Nadas on 2017-02-05.
//
#include <iostream>
#include <sstream>

#include "database.h"

Database::Database(std::vector<std::string> titles_set): colCount(titles_set.size()), _titles(titles_set) {
    for(int i = 0; i < colCount; i++)
        _decoder.push_back(*new std::vector<std::pair<std::string,int>>());
};

// Data in the database is encoded for faster use.  This function reverse the process.
const std::string Database::decode(int col, int value) const{
    return _decoder[col][value].first;
}

// Encodes and stores the data from a single line of the database.
// Expects space seporated data.
void Database::addData(std::string s){
    std::stringstream ss(s);
    tupple vstrings(new std::vector<int>);
    int col = 0;
    std::string v;
    while(ss >> v)
        vstrings->push_back(encode(col++, v));
    _data.push_back(vstrings);
}

// Checks the database for the occurence of a paterm.
// The pattern is set by the frequent set, but is a vector containing -1 where the filter is not important, and any other valeu if specified.
void Database::setCount(FrequentSet& set) {
    std::vector<int> searchPattern = set.getFilter(colCount);
    int count = 0;
    auto s = setFinder.find(set.hashString());
    if(s != setFinder.end()) {
        count = s->second;
    }
    else {
        for (auto row : _data) {
            bool valid = true;
            for (int col = 0; col < colCount; col++) {
                if (searchPattern[col] >= 0 && searchPattern[col] != (*row)[col]) {
                    valid = false;
                    break;
                }
            }
            if (valid) count++;
        }
    }
    set.setFrequency(count);
    setFinder[set.hashString()] = count;
}

const unsigned long Database::tuppleCount() const{
    return _data.size();
}

// Starts off the frequent sets by giving sets of all unique values.
// Has the advantage that all these sets were counted in the encoding process.
// Calling this function copies the data into the setFinder for use with setCount.
std::vector<FrequentSet> Database::getFirstFrequentSets(int min_sup) {
    std::vector<FrequentSet> retSet;
    for (int i = 0; i < colCount; ++i) {
        for (int j = 0; j < _decoder[i].size(); ++j) {
            if(_decoder[i][j].second >= min_sup) {
                FrequentSet f = FrequentSet(i, j, _decoder[i][j].second);
                setFinder[f.hashString()] = f.getFrequency();
                retSet.push_back(f);
            }
        }
    }
    return retSet;
}

dataSet Database::createDataset(){return _data;};

std::string Database::getHeader(int col) {return _titles[col];}

int Database::getClassUniqueCount(int col){return _decoder[col].size();}

void Database::printIntPair(std::ostream &out, intpair filter) {
    out << _titles[filter.first] << "=" << decode(filter.first, filter.second);
}

std::ostream& operator<< (std::ostream & out, const Database& data){
    int i;

    for(i = 0; i < data.colCount; i++)
        out << data._titles[i] << " ";
    out << std::endl;

    for (auto& l: data._data) {
        for (i = 0; i < data.colCount; i++)
            out << data.decode(i, (*l)[i]) << " ";
        out << std::endl;
    }
    return out;
}
// The encode used after reading in data.
// A pair of ints represent the row and index in the decoder.
// Can be considered set and subset as well.
int Database::encode(int col, std::string value){
    int count = static_cast<int>(_decoder[col].size());
    for(int i = 0; i < count; i++)
        if(_decoder[col][i].first == value){
            _decoder[col][i].second++;
            return i;
        }
    _decoder[col].push_back(std::pair<std::string, int>(value, 1));
    return count;
}
