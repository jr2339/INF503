//
//  SuffixTreeNode.h
//  SuffixTree
//
//  Created by jr2339 on 4/6/17.
//  Copyright © 2017 jr2339. All rights reserved.
//

#ifndef SuffixTreeNode_h
#define SuffixTreeNode_h

#include <iostream>
#include <vector>
#include <map>
#include <ctime>


using namespace std;

class SuffixTreeNode{
    map<char, SuffixTreeNode*> children;
    char value;
    vector<int> indexes;
    
public:
    SuffixTreeNode(){}
    
    int insertString(string s, int index){
        int number_node = 0;
        indexes.push_back(index);
        if (s.length() > 0) {
            value = s[0];
            SuffixTreeNode* child = NULL;
            if (children.find(value) != children.end()) {
                child = children[value];
            }
            else{
                child = new SuffixTreeNode();
                children[value] = child;
                number_node = number_node + 1;
            }
            string remainder = s.substr(1);
            child -> insertString(remainder, index);
            
        }
        cout <<" The node is " << number_node << endl;
        return number_node;
    }
    
    // this is a search function which means if find it we return the index
    //else we will printf some messages
    
    vector<int> getIndexes(string s){
        if (s.length() == 0) {
            return indexes;
        }
        else{
            char first = s[0];
            if (children.find(first) != children.end()) {
                string remainder = s.substr(1);
                return children[first] -> getIndexes(remainder);
            }
            else{
                vector<int> empty;
                return empty;
            }
            
        }
    }
    
    ~SuffixTreeNode(){
        map<char, SuffixTreeNode*>::iterator it;
        for (it = children.begin(); it != children.end(); ++it) {
            delete it->second;
        }
    }
};


#endif /* SuffixTreeNode_h */
