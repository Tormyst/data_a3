//
// Created by Raphael Bronfman-Nadas on 2017-03-05.
//

#include "id3.h"
#include <iostream>
#include <iterator>
#include <algorithm>

namespace id3 {

    std::shared_ptr<Database> db;
    int target;
    std::vector<int> used;

    dataSet subset(dataSet &set, int col, int val){
        dataSet d;
        for(auto v : set)
            if((*v)[col] == val)
                d.push_back(v);
        return d;
    }

    Node::Node(int value){
        _v = value;
        _leaf = true;
    }

    int magority(dataSet& set){
        std::vector<int> counts(db->getClassUniqueCount(target), 0);
        for(auto a : set){counts[(*a)[target]]++;}
        return (int) std::distance(counts.begin(), std::max_element(counts.begin(), counts.end()));
    }

    Node::Node(dataSet& set) : _leaf(false) {
        double e = entropy(set);
        if (e < 0.0005) {
            _v = (*set[0])[target];
            _leaf = true;
        } else if (used.size() == db->colCount) {
            _v = magority(set);
            _leaf = true;
        }
        else {
            _splitTarget = bestGain(set, e);
            if(_splitTarget == -1){ // Nothing improves at this point.
                _v = magority(set);
                _leaf = true;
            }
            else {
                used.push_back(_splitTarget);
                for (int i = 0; i < db->getClassUniqueCount(_splitTarget); i++) {
                    dataSet d = subset(set, _splitTarget, i);
                    if (d.size()) {
                        _children.push_back(Node(d));
                    } else {
                        _children.push_back(Node(magority(set)));
                    }
                }
                used.pop_back();
            }
        }
    }

    int Node::bestGain(dataSet &set, double myEntropy) {
        int best = -1;
        double bestVal = 0.0; // Something large and negative.

        for(int i=0; i < db->colCount; i++){
            if(std::find(used.begin(), used.end(), i) != used.end()) continue;
            double pg = potentialGain(set, i, myEntropy);
            if(pg > bestVal) {
                best = i;
                bestVal = pg;
            }
        }
        return best;
    }

    std::ostream& tabs(std::ostream& out, int indent) { out << std::endl; for(int i=0;i < indent; i++){out << "\t";} return out;}

    std::ostream& Node::toStream(std::ostream& out, int indent) {
        if(_leaf) {
            out << db->getHeader(target) << " is " << db->decode(target, _v);
        }
        else {
            for(int c = 0; c < _children.size(); c++){
                tabs(out, indent);
                out << "If "<< db->getHeader(_splitTarget) << " is " << db->decode(_splitTarget, c) << " then ";
                _children[c].toStream(out, indent + 1);
            }
        }
        return out;
    }

    Node createTree(std::shared_ptr<Database> indb, int intarget) {
        db = indb;
        target = intarget;
        used.clear();
        used.push_back(target);

        dataSet d = db->createDataset();

        return Node(d);
    }

    double potentialGain(dataSet &set, int split, double myEntropy) {
        std::vector<dataSet> d(db->getClassUniqueCount(split));
        for (auto a : set) {
            d[(*a)[split]].push_back(a);
        }
        for(auto v: d){
            double otherE = entropy(v);
            myEntropy -= (((double) v.size()) / set.size()) * otherE;
        }
        return myEntropy;
    }

    double entropy(dataSet &set) {
        if(!set.size()) return 0.0;
        std::vector<int> count(db->getClassUniqueCount(target), 0);
        for (auto a : set) {
            count[(*a)[target]]++;
        }
        double sum = 0.0;
        for (int i : count) {
            double percentage = ((double) i) / set.size();
            if (percentage != 0.0)
                sum += percentage * (log2(1.0 / percentage));
        }
        return sum;
    }
}