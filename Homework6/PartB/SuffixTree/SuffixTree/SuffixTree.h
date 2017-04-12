//
//  SuffixTree.h
//  SuffixTree
//
//  Created by jr2339 on 4/7/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef SuffixTree_h
#define SuffixTree_h
#include "SuffixTreeNode.h"

class SuffixTree {
    SuffixTreeNode* root;
public:
    SuffixTree(string s) {
        int total_node = 0;
        root = new SuffixTreeNode;
        for (int i=0; i<s.length(); ++i) {
            string suffix = s.substr(i);
            root->insertString(suffix,i);
            
            if (root->insertString(suffix,i) != 0) {
                total_node = total_node + root->insertString(suffix,i);
            }
            
        }
        cout << "The total nodes are "<<total_node<<endl;
    }
    vector<int> getIndexes(string s) {
        return root->getIndexes(s);
    }
    
    ~SuffixTree() {}
};

#endif /* SuffixTree_h */
