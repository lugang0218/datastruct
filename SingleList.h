//
// Created by lugang on 2021/6/28.
//

#ifndef LIST_SINGLELIST_H
#define LIST_SINGLELIST_H


#include<iostream>
#include<ostream>
using namespace std;
template<typename T>
class SingleList {
public:
    class Node{
    public:
        T data;
        Node *next=nullptr;
        Node(T data,Node * next){
            this->data=data;
            this->next=next;
        }
        Node(T data){
            this->data=data;
            this->next=nullptr;
        }
        ~Node();
    };

    SingleList(const SingleList<T> & list);
    SingleList();
    ~SingleList();
    void add(const T &data);
    void show() const;
    T & operator[](const int &index) const;
    T & operator()(const int & index);
    SingleList<T> & operator +=(const SingleList<T> &list);
    SingleList<T> operator+(const SingleList<T> & list);
    void reverse();
    int getSize() const;
    bool isEmpty() const;
    T removeFromHead();
private:
    Node * head=nullptr;
    int size=0;
};
template<typename T>
void SingleList<T>::add(const T &data) {
    if(this->head==nullptr){
        this->head=new Node(data);
        this->size++;
        return ;
    }
    Node * newNode=new Node(data,head);
    head=newNode;
    this->size++;
}
template<typename T>
void SingleList<T>::show() const {
    if(this->head==nullptr){
        return ;
    }
    Node * current=head;
    while(current!=nullptr){
        cout<<current->data<<endl;
        current=current->next;
    }
}
template <typename T>
T &  SingleList<T>::operator[](const int &index) const{
    if(this->head==nullptr){
        throw 12;
    }
    Node *current=this->head;
    for(int i=0;i<index;i++){
        current=current->next;
    }
    return current->data;
}
template <typename T>
T &  SingleList<T>::operator()(const int &index){
    if(this->head==nullptr){
        throw 12;
    }
    Node *current=this->head;
    for(int i=0;i<index;i++){
        current=current->next;
    }
    return current->data;
}
template<typename T>
SingleList<T> & SingleList<T>::operator+=(const SingleList<T>& list) {
    Node *current=this->head;
    Node * listCurrent=list.head;
    Node * prevCurrent=nullptr;
    while(current!=nullptr&&listCurrent!=nullptr){
        current->data=current->data+listCurrent->data;
        prevCurrent=current;
        current=current->next;
        listCurrent=listCurrent->next;
    }
    while(listCurrent!= nullptr){
        Node * newNode=new Node(listCurrent->data);
        prevCurrent->next=newNode;
        prevCurrent=newNode;
        listCurrent=listCurrent->next;
    }
    return * this;
}

template<typename T>
SingleList<T>::SingleList(){
    cout<<"constructor with no args"<<endl;
}
template<typename T>
SingleList<T>::SingleList(const SingleList<T> &list) {
    cout<<"copy constructor"<<endl;
}
template<typename T>
SingleList<T> SingleList<T>::operator+(const SingleList<T> & list){
    Node *current=this->head;
    Node * listCurrent=list.head;
    Node * prevCurrent=nullptr;
    Node * newHead=nullptr;
    Node * temp=newHead;
    while(current!=nullptr&&listCurrent!=nullptr){
        Node * newNode=new Node(current->data=current->data+listCurrent->data);
        current=current->next;
        listCurrent=listCurrent->next;
    }
}
template<typename T>
void SingleList<T>::reverse() {
    if(this->head==nullptr||this->head->next== nullptr){
        return ;
    }
    Node *current=this->head;
    Node * prev=nullptr;
    Node *next=nullptr;
    while(current!=nullptr){
        next=current->next;
        current->next=prev;
        prev=current;
        current=next;
    }
    head->next=nullptr;
    head=prev;
}
template <typename T>
SingleList<T>::~SingleList(){
    if(this->head== nullptr){
        return ;
    }
    Node *current=head;
    Node * next;
    while(current!=nullptr){
        next=current->next;
        delete current;
        current=next;
    }
    this->head=nullptr;
}
template<typename T>
SingleList<T>::Node::~Node() {
    cout<<"Destroy Node"<<endl;
}

template<typename T>
int SingleList<T>::getSize() const{
    return this->size;
}
template<typename T>
bool SingleList<T>::isEmpty() const{
    return this->size==0;
}


#endif //LIST_SINGLELIST_H
