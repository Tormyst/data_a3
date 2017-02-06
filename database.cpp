//
// Created by Raphael Bronfman-Nadas on 2017-02-05.
//
#include <iostream>

#include "database.h"
using namespace std;

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

