//
// Created by Raphael Bronfman-Nadas on 2017-02-05.
//
#include <iostream>
#include <sstream>

#include "database.h"
#include "frequentSet.h"

Database::Database(std::vector<std::string> titles_set): colCount(titles_set.size()), _titles(titles_set) {
    for(int i = 0; i < colCount; i++)
        _decoder.push_back(*new std::vector<std::pair<std::string,int>>());
};

const std::string Database::decode(int col, int value) const{
    return _decoder[col][value].first;
}

void Database::addData(std::string s){
    std::stringstream ss(s);
    std::vector<int> vstrings;
    int col = 0;
    std::string v;
    while(ss >> v)
        vstrings.push_back(encode(col++, v));
    _data.push_back(vstrings);
}

FrequentSet Database::setCount(FrequentSet set) const{
    std::vector<int> searchPattern = set.getFilter(colCount);
    int count = 0;
    for(auto row : _data){
        bool valid = true;
        for(int col = 0; col < colCount; col++){
            if(searchPattern[col] >= 0 && searchPattern[col] != row[col]){
                valid = false;
                break;
            }
        }
        if(valid) count++;
    }
    set.setFrequency(count);
    return set;
}

const unsigned long Database::tuppleCount() const{
    return _data.size();
}

std::vector<FrequentSet> Database::getFirstFrequentSets() const {
    std::vector<FrequentSet> retSet;
    for (int i = 0; i < colCount; ++i) {
        for (int j = 0; j < _decoder[i].size(); ++j) {
            retSet.push_back(FrequentSet(i,j,_decoder[i][j].second));
        }
    }
    return retSet;
}

std::ostream& operator<< (std::ostream & out, const Database& data){
    int i;

    for(i = 0; i < data.colCount; i++)
        out << data._titles[i] << " ";
    out << std::endl;

    for (auto& l: data._data) {
        for (i = 0; i < data.colCount; i++)
            out << data.decode(i, l[i]) << " ";
        out << std::endl;
    }
    return out;
}

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
