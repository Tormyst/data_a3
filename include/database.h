//
// Created by Raphael Bronfman-Nadas on 2017-02-05.
//

#ifndef DATA_A3_DATABASE_H
#define DATA_A3_DATABASE_H
#include <list>
#include <vector>
#include <array>
#include <string>

class Database {
public:
    const int colCount;
private:
    std::vector<std::string> _titles;
    std::list<std::vector<int>> _data;
    std::vector<std::vector<std::string>> _decoder;

public:
    Database(std::vector<std::string> titles);
    const std::string decode(int col, int value) const;
    void addData(std::string s);
    int setCount(std::vector<int>& searchPattern) const;
    const unsigned long tuppleCount() const;

    friend std::ostream& operator<< (std::ostream & out, const Database& data);

private:
    int encode(int col, std::string value);
};

std::ostream& operator<< (std::ostream & out, Database const& data);

#endif //DATA_A3_DATABASE_H
