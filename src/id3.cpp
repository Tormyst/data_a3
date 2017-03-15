//
// Created by Raphael Bronfman-Nadas on 2017-03-05.
//

#include "id3.h"
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>

namespace id3 {

    std::shared_ptr<Database> db;
    int target;
    std::vector<int> used;

    // Utility function to split a list in parts.
    std::vector<dataSet> subset(dataSet &set, int col){
        std::vector<dataSet> d(db->getClassUniqueCount(col));
        for (auto a : set) {
            d[(*a)[col]].push_back(a);
        }
        return d;
    }

    // Basic constructor used to create leaf nodes when there is no data to suport a conclusion.
    Node::Node(int value){
        _v = value;
        _leaf = true;
    }

    // majority finds the most common value in the list, if it is a tie, it tries to use the passed in value to break the tie.
    // The tie is only broken with that value if it is one of the values tied with.
    // Otherwise the picked value happens to be the first that appered in the data set.
    std::pair<int, std::vector<int>> majority(dataSet &set, int tieBreak){
        std::vector<int> counts(db->getClassUniqueCount(target), 0);
        for(auto a : set){counts[(*a)[target]]++;}

        double max = counts[0];
        std::vector<int> maxIndex;
        maxIndex.push_back(0);

        for(int i=1; i<counts.size();i++) {
            if(counts[i] > max) {
                max = counts[i];
                maxIndex.clear();
                maxIndex.push_back(i);
            }
            else if(counts[i] == max){
                maxIndex.push_back(i);
            }
        }

        std::pair<int, std::vector<int>> ret;

        // If there is a tie, and the tie value is one of the parent values that could contain that tie, then return the index.
        if(maxIndex.size() > 1 && std::find(maxIndex.begin(), maxIndex.end(), tieBreak) != maxIndex.end() )
            ret.first = tieBreak;
        else
            ret.first =  (int) std::distance(counts.begin(), std::max_element(counts.begin(), counts.end()));
        ret.second = counts;
        return ret;
    }

    // The main part of the function.  This is a recursive constructor.
    // May morph into a leaf, if there is nothing else that can be done, the entropy is to low, or if nothing improves on the entropy of the data set.
    Node::Node(dataSet& set, int tieBreak=-1) : _leaf(false) {
        std::pair<int, std::vector<int>> major = majority(set, tieBreak);

        _v = major.first;
        _counts = major.second;

        double e = entropy(set);
        if (e < 0.0000005 || used.size() == db->colCount) {
            _leaf = true;
        }
        else {
            _splitTarget = bestGain(set, e);
            if(_splitTarget == -1){ // Nothing improves at this point.
                _leaf = true;
            }
            else {
                // Set this value as off limits
                used.push_back(_splitTarget);
                for (auto d : subset(set,_splitTarget)) {
                    if (d.size()) {
                        // Recurse and create the next node.
                        _children.push_back(Node(d,_v));
                    } else {
                        // There is no suport for this data set, but we still need to create it
                        _children.push_back(Node(_v));
                    }
                }
                // Ok future calls can use this value again.
                used.pop_back();
            }
        }
    }


    // Picks the best split value.
    // Tries all, then picks the best to return.
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

    // Utility for printing
    std::ostream& tabs(std::ostream& out, int indent) { out << std::endl; for(int i=0;i < indent; i++){out << "\t";} return out;}

    // Nicely print the tree.
    std::ostream& Node::toStream(std::ostream& out, int indent) {
        if(_leaf) {
            out << db->getHeader(target) << " is " << db->decode(target, _v);

            if(_counts.size()) {
                int total = std::accumulate(_counts.begin(), _counts.end(), 0, std::plus<int>());
                out << "\t Count=" << total;
                for (int i = 0; i < _counts.size(); i++) {
                    double val = (static_cast<double>(_counts[i]) / total) * 100;
                    out << "\t" << db->decode(target, i) << "=" << val << "%";
                }
            }
            else
                out << "\t No support for conclusion.";
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

    // This function runs the tree.
    int Node::test(tupple t){
        if(_leaf)
            return _v;
        else
            return _children[(*t)[_splitTarget]].test(t);
    }

    // Called by main to run the tree.
    Node createTree(std::shared_ptr<Database> indb, int intarget) {
        db = indb;
        target = intarget;
        used.clear();
        used.push_back(target);

        dataSet d = db->createDataset();

        return Node(d);
    }

    // Calculates the potential gain based on the global value of target.
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

    // Calculates the entropy based on the global value of target.
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