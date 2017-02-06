//
// Created by Raphael Bronfman-Nadas on 2017-02-05.
//
#include <iostream>
#include <sstream>

#include "database.h"
using namespace std;

database::database(vector<string> titles_set): titles(titles_set) {
    for(int i = 0; i < titles.size(); i++)
        decoder.push_back(*new vector<string>());
};

std::string database::decode(int col, int value){
    return decoder[col][value];
}

int database::encode(int col, std::string value){
    int count = decoder[col].size();
    for(int i = 0; i < count; i++)
        if(decoder[col][i] == value)
            return i;
    decoder[col].push_back(value);
    return count;
}

void database::addData(string s){
    stringstream ss(s);
//    istream_iterator<string> stream_iterator(ss);
    vector<int> vstrings;
    int col = 0;
    string v;
    while(ss >> v)
        vstrings.push_back(encode(col++, v));
    data.push_back(vstrings);
}

std::ostream& operator<< (std::ostream & out, database const& data){
    int i;

    for(i = 0; i < data.titles.size(); i++)
        out << data.titles[i] << " ";
    out << endl;

    for (auto& l: data.data) {
        for (i = 0; i < l.size(); i++)
            out << l[i] << " ";
        out << endl;
    }
    return out;
}

