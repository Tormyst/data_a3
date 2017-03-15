//
// Created by Raphael Bronfman-Nadas on 2017-03-05.
//

#ifndef DATA_A3_ID3_H
#define DATA_A3_ID3_H

#include <ostream>
#include "database.h"

namespace id3 {

    class Node{
    private:
        int _splitTarget;
        std::vector<Node> _children;
        bool _leaf;
        std::vector<int> _counts;
        int _v; // Value associated with the leaf node of a tree.
    public:
        Node(dataSet& set, int tieBreak);
        Node(int val);
        std::ostream& toStream(std::ostream& out, int indent=0);
        int test(tupple t);

    private:
        static int bestGain(dataSet& set, double myEntropy);
    };

    Node createTree(std::shared_ptr<Database> db, int target);
    double potentialGain(dataSet &set, int split, double myEntropy);
    double entropy(dataSet& set);
}
#endif //DATA_A3_ID3_H
