//
// Created by Raphael Bronfman-Nadas on 2017-02-05.
//
#include <iostream>
#include <sstream>

#include "../include/database.h"
using namespace std;

Database::Database(vector<string> titles_set): colCount(titles_set.size()), _titles(titles_set) {
    for(int i = 0; i < colCount; i++)
        _decoder.push_back(*new vector<pair<string,int>>());
};

const std::string Database::decode(int col, int value) const{
    return _decoder[col][value].first;
}

void Database::addData(string s){
    stringstream ss(s);
    vector<int> vstrings;
    int col = 0;
    string v;
    while(ss >> v)
        vstrings.push_back(encode(col++, v));
    _data.push_back(vstrings);
}

int Database::setCount(vector<int>& searchPattern) const{
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
    return count;
}

const unsigned long Database::tuppleCount() const{
    return _data.size();
}

vector<FrequentSet> Database::getFirstFrequentSets() const {
    vector<FrequentSet> retSet;
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
    out << endl;

    for (auto& l: data._data) {
        for (i = 0; i < data.colCount; i++)
            out << data.decode(i, l[i]) << " ";
        out << endl;
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
    _decoder[col].push_back(pair<string, int>(value, 1));
    return count;
}
