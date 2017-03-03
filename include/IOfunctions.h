#ifndef LOAD_CSV_H
#define LOAD_CSV_H
#include <string>
#include <memory>
#include "database.h"
#include "rule.h"

std::unique_ptr<Database> readCSV(const std::string inputFile);

void prittyPrint(std::shared_ptr<Database> db, std::vector<Rule>& r, std::string filename,
                 double min_sup, double min_con);

#endif

