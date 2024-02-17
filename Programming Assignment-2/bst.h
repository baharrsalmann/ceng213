#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class BST {
private:
    // Define TreeNode for the second phase (Binary Search Tree)
    /* DO NOT CHANGE */
    struct TreeNode {
        std::string key;
        T data;
        TreeNode* left;
        TreeNode* right;
        TreeNode(const std::string &k, const T& value) : key(k), data(value), left(NULL), right(NULL) {}
        
    };

    TreeNode* root;


public: // Do not change.

    BST();
    ~BST();
    TreeNode* getRoot() { return root; }
    bool isEmpty() { return root == NULL; }

    BST& insert(const std::string key, const T& value);
    bool search(std::string value) const;
    void remove(std::string value);
    BST<T>* merge(BST<T>* bst);
    BST<T>* intersection(BST<T>* bst);
    std::vector<TreeNode> tree2vector(TreeNode* root);
    void print();
    
private:// you may add your own utility member functions here.
    void insert_helper(TreeNode* &r,const string key, const T& value){
        if (!r){
            r = new TreeNode(key,value); 
        }
        else if (r->key > key){
            insert_helper(r->left, key, value);}
        else if (r->key < key){
            insert_helper(r->right,key, value);
        }
    }
    void clean(TreeNode*r){
        if(r==NULL) return;

        else{
            clean(r->right);
            clean(r->left);
            delete r;
        }
    }
    bool search_helper(const TreeNode* r, std::string value) const{
        if (!r) {
            return false;}
        else {
            if (r->key==value){
                return true;}
            else if (r->key > value){
                return search_helper(r->left,value);}
            else {
                return search_helper(r->right,value);}
        }
    }
    TreeNode* getMin(TreeNode* r) {
        if (!r->left) return r;
        else return getMin(r->left);
        }
TreeNode* remove_helper(TreeNode *root, string key) {
	if(root == NULL) return root; 
	else if(key < root->key) root->left = remove_helper(root->left,key);
	else if (key > root->key) root->right = remove_helper(root->right,key);

	else {
		if(root->left == NULL && root->right == NULL) { 
			delete root;
			root = NULL;
		}
		else if(root->left && root->right) { 
			TreeNode *temp = getMin(root->right);
			root->key = temp->key;
			root->data=temp->data;
			root->right = remove_helper(root->right,temp->key);
		}

        else{
                TreeNode* oldNode=root;
                root= (root->left!=NULL)? root->left : root->right ;
                delete oldNode;
            }


	}
	return root;
}

    void tree2vector(TreeNode* node, vector<TreeNode>& result){
        if(!node) return;

        tree2vector(node->left,result);
        result.push_back(TreeNode(node->key,node->data));
        tree2vector(node->right,result);

    }
    void print(TreeNode* node, std::string indent, bool last, bool isLeftChild); // Do not change.
    
};

    // Constructor
    template <class T>
    BST<T>::BST() : root(NULL) {}

    // Destructor
    template <class T>
    BST<T>::~BST() {
    /* IMPLEMENT THIS */
    clean(root);

    }

    // Insert function for BST.    
    template <class T>
    BST<T>& BST<T>::insert(const string key, const T& value) {
             /* IMPLEMENT THIS */
        insert_helper(root,key,value);
        return *this;
    }
    
    // Search function for BST.
    template <class T>
    bool BST<T>::search(std::string value) const {
     /* IMPLEMENT THIS */
    return search_helper(root,value);
    }
    
    // Remove a node from BST for given key. If key not found, do not change anything.
    template <class T>
    void BST<T>::remove(std::string key) {
        /* IMPLEMENT THIS */
        root=remove_helper(root,key);
        
    }
    
    // A helper function for converting a BST into vector.
    template <class T>
    vector<typename BST<T>::TreeNode> BST<T>::tree2vector(TreeNode* root) {
        vector<TreeNode> result;
        tree2vector(root,result);
        return result;
    }
    
    // Merge two BST's and return merged BST.
    template <class T>
    BST<T>* BST<T>::merge(BST<T>* bst) {
    /* IMPLEMENT THIS */
    vector<TreeNode> this_Vector = tree2vector(getRoot());
    vector<TreeNode> other_Vector = tree2vector(bst->getRoot());
    vector<TreeNode> merged_vector;
    while(!this_Vector.empty()&& !other_Vector.empty()){
        if(this_Vector.begin()->key < other_Vector.begin()->key){
            merged_vector.push_back(this_Vector.front());
            this_Vector.erase(this_Vector.begin());
        }
        else if(this_Vector.begin()->key==other_Vector.begin()->key){
            merged_vector.push_back(this_Vector.front());
            this_Vector.erase(this_Vector.begin());
            other_Vector.erase(other_Vector.begin());
        }
        else if(this_Vector.begin()->key > other_Vector.begin()->key){
            merged_vector.push_back(other_Vector.front());
            other_Vector.erase(other_Vector.begin());
        }
    }
    while(!this_Vector.empty()){
        merged_vector.push_back(this_Vector.front());
        this_Vector.erase(this_Vector.begin());

    }
    while(!other_Vector.empty()){
        merged_vector.push_back(other_Vector.front());
        other_Vector.erase(other_Vector.begin());
    }
    if(merged_vector.size()==0) return NULL;
    BST<T> *merged_BST= new BST<T>();
    for(int i=0;i<merged_vector.size();i++){
        merged_BST->insert(merged_vector[i].key,merged_vector[i].data);
    }

    return merged_BST;
    }
        
    // Intersect two BST's and return new BST.
    template <class T>
    BST<T>* BST<T>::intersection(BST<T>* bst) {
    /* IMPLEMENT THIS */
    vector<TreeNode> this_Vector = tree2vector(getRoot());
    vector<TreeNode> other_Vector = tree2vector(bst->getRoot());
    vector<TreeNode> merged_vector;
    while(!this_Vector.empty()&& !other_Vector.empty()){
        if(this_Vector.begin()->key == other_Vector.begin()->key){
            merged_vector.push_back(this_Vector.front());
            this_Vector.erase(this_Vector.begin());
            other_Vector.erase(other_Vector.begin());
        }
        else if(this_Vector.begin()->key > other_Vector.begin()->key){
            other_Vector.erase(other_Vector.begin()); }

        else if(this_Vector.begin()->key < other_Vector.begin()->key){
            this_Vector.erase(this_Vector.begin());  }      
    }
    if(merged_vector.size()==0) return NULL;
    
    BST<T> *merged_BST= new BST<T>();
    for(int i=0;i<merged_vector.size();i++){
        merged_BST->insert(merged_vector[i].key,merged_vector[i].data);
    }
    return merged_BST;
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print() {
        print(root, "", true, false);
    
    }
    
    /* DO NOT CHANGE */
    template <class T>
    void BST<T>::print(TreeNode* node, string indent, bool last, bool isLeftChild) {
        if (node != NULL) {
            cout << node->key << endl;
            print(node->left, indent, false, true);
            print(node->right, indent, true, false);
        }
    
    }


