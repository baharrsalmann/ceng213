#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &rhs);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);
    void mergeNodes(int sourceIndex, int destIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    /* TODO */
    T data;
    this->head=new Node<T>(data);
    this->size=0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs)
{   
    /* TODO */
    T data;
    this->head=new Node<T>(data);
    Node<T> *temp;
    Node<T> *current_1;
    Node<T> *current_2;
    temp=(rhs.head)->next;
    current_1=head;

    while (temp)
    {
        current_2=new Node<T>(temp->data);
        current_1->next=current_2;
        current_2->prev=current_1;
        current_1=current_2;
        temp=temp->next;
    }
    size=rhs.size;
}

template<class T>
LinkedList<T>::~LinkedList()
{   
    /* TODO */
    this->removeAllNodes();
    delete head;
    size=0;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) //iiyi calısıyor
{
    /* TODO */
    removeAllNodes();
    Node<T> *temp=rhs.head->next;
    Node<T> *curr=head;
    while(temp){
        curr->next=new Node<T>(temp->data);
        curr->next->prev=curr;
        curr=curr->next;
        temp=temp->next;
    }
    size=rhs.size;
    return *this;   //return type is linkedlist itself
}

template<class T>
int LinkedList<T>::getSize() const
{
    /* TODO */
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    /* TODO */
    if(size==0 && head->next==NULL) return true;
    else return false;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    /* TODO */
    Node<T> *temp;
    temp=head;
    while (temp)
    {
        if(temp==node) return true; //node->datayı bi variableda tutabilir misin her seferinde hesaplanmasın diye?
        else temp=temp->next;
    }
    return false;    
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
    if(size==0) return NULL;
    return head->next;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
    if(size==0) return NULL;
    Node<T> *temp;
    temp=head;
    while(temp->next) {temp=temp->next;}
    return temp;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
    Node<T> *temp;
    temp=head->next;
    while (temp) {
        if(temp->data==data) return temp;
        temp=temp->next;
    }
    return NULL;

}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */
    Node<T> *temp;
    temp=head->next; //0. nodea işaret eder
    if(index<0 || index>size-1) return NULL;
    for (int i=0; i<index; i++) {temp=temp->next;}  
    return temp;
}

template<class T>
void LinkedList<T>::append(const T &data)
{   
    /* TODO */ //acaba tempsiz yapabilir miydin?
    Node<T> *new_node,*temp;
    temp=head;
    new_node=new Node<T>(data);
    new_node->next=NULL;
    while(temp->next) {temp=temp->next;}
    temp->next=new_node;
    new_node->prev=temp;
    size++;
    return;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    /* TODO */
    if(isEmpty()) {
        append(data);
        return;}
    Node<T> *new_node,*temp;
    temp=head;
    new_node=new Node<T>(data);
    new_node->next=head->next;
    head->next->prev=new_node;
    head->next=new_node;
    new_node->prev=head;
    size++;
    return;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) //node dummy head olabilir mi??
{
    /* TODO */
    if(!containsNode(node)) return;
    if(node==head) {
    prepend(data); 
    size++;
    return;
    }
    Node<T> *new_node=new Node<T>(data);  
    if(node==getLastNode()){
        node->next=new_node;
        new_node->prev=node;
        size++;
        return;
    }
    //imlement it with the other constructor, just try.
    new_node->prev=node;
    new_node->next=node->next;
    node->next->prev=new_node;
    node->next=new_node;
    size++;
    return;
}


template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index) //örn son index 5, 6 verdiğimizde sona eklemeli mi?
{
    /* TODO */
    if( 0>index || size<index+1) return;
    Node<T> *temp=head;
    for(int i=0;i<index;i++) {temp=temp->next;}
    insertAfterNode(data,temp);
    return;
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    /* TODO */
    Node<T> *temp;
    int index=0;
    temp=head->next;
    while (temp) {
        if(temp->data==node->data) return index;
        index++;
        temp=temp->next;
    }
    return -1;
}

/*
template<class T>
void LinkedList<T>::swapWithLeft(Node<T> *node)
{
     TODO 
}

template<class T>
void LinkedList<T>::swapWithRight(Node<T> *node)
{
    /* TODO 
}*/

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    if (currentIndex < 0 || newIndex < 0 || currentIndex == newIndex) { return; }

    else if(newIndex>currentIndex) {
        if(newIndex>size-1) {moveToIndex(currentIndex,size-1);} //sona ekleniyor
        else {
            Node<T> *curr=getNodeAtIndex(currentIndex);
            Node<T> *temp=getNodeAtIndex(newIndex);    
            curr->prev->next=curr->next;
            curr->next->prev=curr->prev;
            curr->next=temp->next;
            curr->prev=temp;
            temp->next=curr;
            if(temp->next) temp->next->prev=curr; 
        }//sağa taşınıyor
    }
    else if(currentIndex>newIndex){
        if(currentIndex>size-1) {return;}
        else{
            Node<T> *curr=getNodeAtIndex(currentIndex);
            Node<T> *temp=getNodeAtIndex(newIndex); 
            curr->prev->next=curr->next;
            if(curr->next) curr->next->prev=curr->prev;
            curr->next=temp;
            curr->prev=temp->prev;
            temp->prev=curr;
            temp->prev->next=curr;
        } //sola taşınıyor
    }


}




template<class T>
void LinkedList<T>::mergeNodes(int sourceIndex, int destIndex)
{
    /* TODO */
    if( 0>sourceIndex || 0>destIndex || size<sourceIndex+1 || size<destIndex+1) return;

    Node<T> *ptr_1,*ptr_2;
    ptr_2=getNodeAtIndex(destIndex);
    ptr_1=getNodeAtIndex(sourceIndex);
    ptr_2->data+=ptr_1->data;
    removeNode(ptr_1);
    return;
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{   
    /* TODO */
    if(node==getLastNode()) removeNodeAtIndex(size-1);
    else{
    node->prev->next=node->next;
    node->next->prev=node->prev;
    delete node; }
    size--;
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{   
    /* TODO */
    Node<T> *temp;
    while(temp=getNode(data)){
    removeNode(temp);
    }
    return;
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    /* TODO */
    if( 0>index || size<index+1) return;
    Node<T> *ptr=getNodeAtIndex(index);
    
    if(index==size-1){
        ptr->prev->next=NULL;
        delete ptr;
    }
    else{
        ptr->prev->next=ptr->next;
        ptr->next->prev=ptr->prev;
        delete ptr; }
    size--;
}

template<class T>
void LinkedList<T>::removeAllNodes()
{   
    /* TODO */
    if(size==0) return;
    Node<T> *ptr_1;
    ptr_1=head->next;
    while(ptr_1){
        Node<T> *near= ptr_1->next;
        delete ptr_1;
        ptr_1=near;
    }
    head->next=NULL;
    size=0;
}


template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    while(node)
    {
        std::cout << *node << std::endl;
        node = node->next;
    }

}

#endif //LINKEDLIST_H