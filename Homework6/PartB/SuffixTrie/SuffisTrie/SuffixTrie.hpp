//
//  SuffixTrie.hpp
//  SuffisTrie
//
//  Created by jr2339 on 4/5/17.
//  Copyright © 2017 jr2339. All rights reserved.
//


#include "SuffixNode.h"
#include <queue>
#include <iostream>

#ifndef SuffixTrie_hpp
#define SuffixTrie_hpp

using namespace std;

#define SENTINEL "$"

class SuffixTrie
{
    private:
        SuffixNode *root;      //root of the trie
        SuffixNode *longest;   //point to the last character except SENTINEL
    
    public:
        SuffixTrie(){
            this->root = new SuffixNode();
            this->longest = new SuffixNode(this->root);
        }
    
        ~SuffixTrie(){
            delete this->root;
            delete this->longest;
        }
    
        SuffixNode* get_trie_root(){
            return this->root;
        }
    
        SuffixNode* get_deepest_leaf(){
            return this->longest;
        }
    
    
        /*
         *Ukkonen's Algorithm
         *build suffix trie of s
         *return root node, and
         *get deepest node
         */
    
        void build_suffix_trie(string s){
            int total_node =0;
            unsigned long len = s.length();
            if (len <= 1) {
                cout <<"DNA Sequence is Empty\n";
                return;
            }
            
            //add s[0] to root
            this->root->add_link(s.substr(0,1), this->longest);
            this->longest->set_path(s.substr(0,1));
            
            //append the rest of characters
            for (int i=1; i<len; i++) {
                SuffixNode *current = this->longest;
                SuffixNode *pre = NULL;
                string s_i = s.substr(i,1);
                
                //not root and s[i] not in node's children
                while (current && !current->has_string(s_i)) {
                    SuffixNode *new_node = new SuffixNode();
                    current->add_link(s_i, new_node);
                    new_node ->set_path(current->get_path() + s_i);
                    
                    if (pre != NULL) {
                        pre->set_suffix_link(new_node);
                    }
                    
                    pre = new_node;
                    ++total_node;
                    current = current->get_suffix_link();
                }
                
                //set the last suffic node link
                if (current == NULL) {
                    pre->set_suffix_link(this->root);
                }
                else{
                    pre->set_suffix_link(current->get_child(s_i));
                }
                
                if (s_i != SENTINEL) {
                    this->longest = this->longest->get_child(s_i);
                }
            }
            cout<<"The total node is: "<<total_node<<endl;
        }
    
    
    /*
     *Followings are basic applications of suffix trie
     */
    
    bool has_substring(string s){
        SuffixNode* head = this->root;
        
        for (int i=0; i<s.length(); i++) {
            SuffixNode* child = head->get_child(s.substr(i,1));
            
            if (child) {
                head = child;
            }
            else{
                return false;
            }
        }
        return true;
    }
    
    bool has_suffix(string s){
        SuffixNode *head = this->root;
        
        for (int i=0; i<s.length(); i++) {
            SuffixNode* child = head->get_child(s.substr(i,1));
            
            if (child) {
                head = child;
            }
            else{
                return false;
            }
        }
        if (head->get_child(SENTINEL)) {
            return true;
        }
        return false;
        
    }
    
    
    int numberOf(string s){
        SuffixNode* head = this->root;
        
        for (int i=0; i<s.length(); i++) {
            SuffixNode* child = head->get_child(s.substr(i,1));
            
            if (child) {
                head = child;
            }
            else{
                return 0;
            }
        }
        
        int count =0;
        //count number of leaves, use BFS algorithm
        //which is Breadth-first search
        
        queue<SuffixNode*> q;
        q.push(head);
        while (!q.empty()) {
            SuffixNode* node = q.front();
            q.pop();
            
            map<string, SuffixNode*> m = node->get_children();
            
            if (m.size() == 0) {
                count++;
                continue;
            }
            
            std::map<string,SuffixNode*>::iterator iter;
            for (iter = m.begin(); iter != m.end(); iter++) {
                q.push(iter->second);
            }
        }
        return count;
    }
    
    string longest_repeat(){
        SuffixNode* tail = this->longest;
        while (tail) {
            if (tail->get_children().size()>1) {
                return tail->get_path();
            }
            tail = tail->get_suffix_link();
        }
        
        return "";
    }
    
    string lexico_first_suffix(){
        SuffixNode* head = this->root;
        string lexico_1 = "";
        
        while (head) {
            //only find the prefix of the first suffix
            
            if (lexico_1 !="" && head->has_string(SENTINEL)) {
                break;
            }
            
            string min = "";
            
            std::map<string, SuffixNode*>::iterator iter;
            map<string,SuffixNode*> m = head->get_children();
            
            
            for (iter=m.begin(); iter != m.end(); iter++) {
                string child_edge = iter->first;
                if (child_edge != SENTINEL && (min == "" || child_edge.compare(min)<0)) {
                    min = child_edge;
                }
            }
            lexico_1 += min;
            head = head->get_child(min);
        }
        return lexico_1;
    }
    

    
};

void output(SuffixNode* node, string last ="");
void output_suffix(SuffixNode* longest);
void test_substring(SuffixTrie* trie, string s, string q);
void test_suffix(SuffixTrie* trie, string s, string q);
void test_occurrence(SuffixTrie* trie, string s, string q);
void test_longest_repeat(SuffixTrie* trie, string s);
void test_lexico_first_suffix(SuffixTrie* trie, string s);




#endif /* SuffixTrie_hpp */
