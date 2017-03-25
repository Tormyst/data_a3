#ifndef LOAD_CSV_H
#define LOAD_CSV_H
#include <string>
#include <memory>
#include "database.h"
#include "rule.h"
#include "id3.h"
#include "NaiveBayes.h"

std::unique_ptr<Database> readCSV(const std::string inputFile, const std::string testFile, int& target);

int targetNameToInt(const std::string inputFile, const std::string target);

void prittyPrint(std::shared_ptr<Database> db, std::vector<Rule>& r, std::string filename,
                 double min_sup, double min_con);

void prittyPrintID3(std::shared_ptr<Database> db, id3::Node root, std::string filename, int target);

void prittyPrintNaiveBayes(std::shared_ptr<Database> db, const NaiveBayes::bayesTable &t, const std::string filename, const int target);

#endif

