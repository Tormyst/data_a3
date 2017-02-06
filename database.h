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
    std::list<std::vector<int>> data;
    std::vector<std::vector<std::string>> decoder;

    database(std::vector<std::string> titles);
    std::string decode(int col, int value);
    int encode(int col, std::string value);
    void addData(std::string s);


};

std::ostream& operator<< (std::ostream & out, database const& data);

#endif //DATA_A3_DATABASE_H
