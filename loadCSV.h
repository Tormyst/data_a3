#ifndef LOAD_CSV_H
#define LOAD_CSV_H
#include <string>
#include <memory>
#include "database.h"

std::unique_ptr<Database> readCSV(const std::string inputFile);
#endif

