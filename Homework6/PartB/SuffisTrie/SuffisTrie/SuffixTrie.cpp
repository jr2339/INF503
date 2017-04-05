//
//  SuffixTrie.cpp
//  SuffisTrie
//
//  Created by jr2339 on 4/5/17.
//  Copyright © 2017 jr2339. All rights reserved.
//


#include "SuffixTrie.hpp"

/*
* output each node info to check correctness
*/

void output(SuffixNode* node, string last =""){
    map<string, SuffixNode*> m = node->get_children();
    string children = "";
    
    for (std::map<string, SuffixNode*>::iterator iter = m.begin(); iter != m.end(); ++iter) {
        string s = iter->first;
        children += s+" ";
    }
    
    string parent = node->get_suffix_link() ? last: "root";
    
    cout << parent <<"in" << node->get_path() <<"\thas child:" <<children<<"tsuffix link: ";
    if (parent != "root") {
        cout << node->get_suffix_link()->get_path()<<endl;
    }
    else{
        cout <<"NONE\n";
    }
    
    for (std::map<string, SuffixNode*>::iterator iter = m.begin(); iter != m.end(); ++iter) {
        string s = iter->first;
        SuffixNode * s_node = iter->second;
        output(s_node,s);
    }
    
}



/*
 *output all the suffix via
 *the deepest node
 */
void output_suffix(SuffixNode* longest){
    while (longest) {
        cout <<longest->get_path()<<endl;
        longest = longest->get_suffix_link();
    }
}


/*
 *test basic applications
 */

void test_substring(SuffixTrie* trie, string s, string q){
    if (trie->has_substring(q)) {
        cout << q << " is a substring of " << s << endl;
    }
    else{
        cout << q << "is not a substring of " << s << endl;
    }
}


void test_suffix(SuffixTrie* trie, string s, string q){
    if (trie->has_suffix(q)) {
        cout << q << "is a suffix of " << s << endl;
    }
    else{
        cout <<q << "is not a suffix of " << s << endl;
    }
    
}

void test_occurrence(SuffixTrie* trie, string s, string q)
{
    cout << q << " occurs " << trie->numberOf(q) << " time(s) in " << s << endl;
}

void test_longest_repeat(SuffixTrie* trie, string s){
    string repeat = trie -> longest_repeat();
    
    if (repeat == "") {
        cout << "There is no repeat substring in " << s << endl;
    }
    else{
        cout << repeat << "is the longest repeat substring in " << s << endl;
    }
}

void test_lexico_first_suffix(SuffixTrie* trie, string s)
{
    string lexico_1 = trie->lexico_first_suffix();
    cout << lexico_1 << " is the first suffix of " << s << " by alphabetical order\n";
}



int main(int argc, char *argv[])
{
    string s = argv[1];
    string q = argv[2];
    
    SuffixTrie* trie = new SuffixTrie();
    trie->build_suffix_trie(s+SENTINEL);
    
    SuffixNode* root = trie->get_trie_root();
    SuffixNode* longest = trie->get_deepest_leaf();
    
    cout << "print trie stucture\n";
    output(root);
    cout << "print suffix link\n";
    output_suffix(longest);
    
    // test basic applications
    test_substring(trie, s, q);
    test_suffix(trie, s, q);
    test_occurrence(trie, s, q);
    test_longest_repeat(trie, s);
    test_lexico_first_suffix(trie, s);
}




















