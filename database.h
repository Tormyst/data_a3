//
// Created by Raphael Bronfman-Nadas on 2017-02-05.
//

#ifndef DATA_A3_DATABASE_H
#define DATA_A3_DATABASE_H
#include <list>
#include <vector>
#include <array>
#include <string>

class database {
public:
    std::vector<std::string> titles;
    std::list<std::vector<std::string>> data;

    database(){};

};

std::ostream& operator<< (std::ostream & out, database const& data);

#endif //DATA_A3_DATABASE_H
