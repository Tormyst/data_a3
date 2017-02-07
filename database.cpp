//
// Created by Raphael Bronfman-Nadas on 2017-02-05.
//
#include <iostream>
#include <sstream>

#include "database.h"
using namespace std;

Database::Database(vector<string> titles_set): _titles(titles_set), colCount(titles_set.size()) {
    for(int i = 0; i < colCount; i++)
        _decoder.push_back(*new vector<string>());
};

const std::string Database::decode(int col, int value) const{
    return _decoder[col][value];
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

int Database::tuppleCount(){
    return _data.size();
}

std::ostream& operator<< (std::ostream & out, const Database& data){
    int i;

    for(i = 0; i < data.colCount; i++)
        out << data._titles[i] << " ";
    out << endl;

    for (auto& l: data._data) {
        for (i = 0; i < l.size(); i++)
            out << data.decode(i, l[i]) << " ";
        out << endl;
    }
    return out;
}

int Database::encode(int col, std::string value){
    int count = _decoder[col].size();
    for(int i = 0; i < count; i++)
        if(_decoder[col][i] == value)
            return i;
    _decoder[col].push_back(value);
    return count;
}
