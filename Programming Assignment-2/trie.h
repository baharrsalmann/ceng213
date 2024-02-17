#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;


template <class T>
class Trie {    
private:
    // Define TrieNode for the first phase (Trie)
    /* DO NOT CHANGE */
    struct TrieNode {
        static const int ALPHABET_SIZE = 128;
        TrieNode* children[ALPHABET_SIZE];
        char keyChar;
        bool isEndOfKey;
        T* data;

        TrieNode(char c) : keyChar(c), isEndOfKey(false), data(NULL) {

                for (int i = 0; i< ALPHABET_SIZE; i++) {
                children[i] = NULL;
                
            }
            
            }
    };

    TrieNode* root;

public: // Do not change.

    Trie(); 
    ~Trie();
    
    Trie& insert(const string& username); 
    void remove(std::string username);
    T* search(std::string username); 
    void findStartingWith(std::string prefix, std::vector<T*> &results); 
    void wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results); 
    void print(); 

private: // you may add your own utility member functions here.
    void print(const std::string& primaryKey); // Do not change this line.
    void printTrie(TrieNode* node, const std::string& currentKey); // Do not change this line.
    

    void deleteTrieNode(TrieNode* node) {
    if(!node) return;

        for (int i = 0; i < 128; i++) {
            deleteTrieNode(node->children[i]);
        }

        delete node->data;
        delete node;
}
    void prefix_helper(TrieNode*r,vector<T*> &results){
        for(int i=0;i<128;i++){
            if(r->children[i]!=NULL){
                if(r->children[i]->isEndOfKey==true) results.push_back(r->children[i]->data);
                else prefix_helper(r->children[i],results);
            }
        }
    }
bool is_Match(string username, string pattern)
{
    int n = username.length();
    int m = pattern.length();
    int i = 0, j = 0, star_begins = -1, match = 0;
 
    while (i<n) {

    if(j<m){
        if (pattern[j]=='?' || pattern[j]==username[i]){
            i++;
            j++;
        }
        else if (pattern[j]=='*'){
            star_begins= j;
            match= i;
            j++;
        }
        else if (star_begins != -1) {
            match++;
            j= star_begins+1;
            i = match;
        }
        else return false;
        
    }
    else if (star_begins != -1) {
            match++;
            j= star_begins+1;
            i = match;
        }
    else return false;

    }
    while (j<m && pattern[j]=='*') j++;
    bool flag= (j==m);
    return flag;
}





};
/* DO NOT CHANGE */
template <class T>
Trie<T>::Trie() : root(new TrieNode('\0')) {}

template <class T>
Trie<T>::~Trie() {
    /* IMPLEMENT THIS */
    deleteTrieNode(root);
}

template <class T>
Trie<T>& Trie<T>::insert(const string& key) {
    /* IMPLEMENT THIS */
        int i=0;
    TrieNode* curr=root;
    while(key[i]!='\0'){
        int index = key[i];
        if (!curr->children[index]) {
            TrieNode* new_comer=new TrieNode(key[i]);
            curr->children[index]=new_comer;
            T* my_data=new T(key);
            new_comer->data=my_data;
            
        }
            
        curr = curr->children[index];
        i++;
    }

    curr->isEndOfKey = true;
    delete curr->data;
    T* my_data=new T(key);
    curr->data=my_data;
    
    return *this;
}

template <class T>
T* Trie<T>::search(std::string username) {
    /* IMPLEMENT THIS */
    TrieNode* curr = root;
 
    for (int i = 0; i < username.length(); i++)
    {   
        int index = username[i];
        if ((curr->children[index])==NULL){

            return NULL; }
            
        curr = curr->children[index];
    }

    bool flag=(curr->isEndOfKey);
    if(flag&&curr->data) {    return curr->data;}
    else {     return NULL;}
}

template <class T>
void Trie<T>::remove(std::string username) {
    /* IMPLEMENT THIS */
    TrieNode* curr = root;
    for (int i = 0; i < username.length(); i++)
    {   
        int index = username[i];
        if ((curr->children[index])==NULL)
            return;
 
    curr = curr->children[index];
    }
    
    curr->isEndOfKey=false;

}

template <class T>
void Trie<T>::findStartingWith(string prefix,vector<T*> &results) {
/* IMPLEMENT THIS */
    TrieNode* curr = root;
    for (int i = 0; i < prefix.length(); i++)
    {   
        int index = prefix[i];
        if ((curr->children[index])==NULL){

            return; }
            
        curr = curr->children[index];
    }
    if(curr->isEndOfKey==true) results.push_back(curr->data);
    prefix_helper(curr,results);
    
}

template <class T>
void Trie<T>::wildcardSearch(const std::string &wildcardKey, std::vector<T*> &results) {
/* IMPLEMENT THIS */
    std::vector<T*> all_keys;
    prefix_helper(root,all_keys);
    while(!all_keys.empty()) {
        bool flag=is_Match(all_keys.front()->getUsername(),wildcardKey);
        if(flag) results.push_back(all_keys.front());
        all_keys.erase(all_keys.begin());
    }
}

/* DO NOT CHANGE */
template<class T>
void Trie<T>::print() {
    print("");
}
/* DO NOT CHANGE */
template <class T>
void Trie<T>::print(const std::string& primaryKey) {
    if (primaryKey.empty()) {
        // Print the entire tree.
        printTrie(root, "");
    } else {
        // Print specific keys.
        TrieNode* primaryNode = root;
        for (int i = 0; i < primaryKey.length(); i++) {
            
            int index = primaryKey[i];
            if (!primaryNode->children[index]) {
                std::cout << "{}" << std::endl; // Primary key not found, nothing to print.
                return ;
            }
            primaryNode = primaryNode->children[index];
        }

        }
    }
/* DO NOT CHANGE */
template <class T>
void Trie<T>::printTrie(TrieNode* node, const std::string& currentKey) {
    if (!node) {
        return;
    }
    if (node->isEndOfKey) {
        std::cout << currentKey <<std::endl;
        std::cout << "Watched Movies:" << std::endl;
        if(node->data) {
            node->data->printMovies();
        }
    }
    for (int i = 0; i < 128; ++i) {
        if (node->children[i]) {
            printTrie(node->children[i], currentKey + static_cast<char>(i));
        }
    }
}

