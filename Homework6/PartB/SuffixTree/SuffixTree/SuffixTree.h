//
//  SuffixTree.h
//  SuffixTree
//
//  Created by jr2339 on 4/6/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef SuffixTree_h
#define SuffixTree_h

#include "SuffixTreeNode.h"

class SuffixTree{
    SuffixTreeNode* root;
    
public:
    
    SuffixTree(string s){
        root = new SuffixTreeNode;
        for (int i = 0; i<s.length(); ++i) {
            string suffix = s.substr(i);
            root->insertString(suffix, i);
        }
        
    }
    
    vector<int> getIndexes(string s){
        return root->getIndexes(s);
    }
    
    ~SuffixTree() {}
    
};

#endif /* SuffixTree_h */
