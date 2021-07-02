//
// Created by lugang on 2021/6/28.
//
#include<iostream>
using namespace std;
#ifndef LIST_LINKEDLIST_H
#define LIST_LINKEDLIST_H
template<typename T>
class LinkedList{
public:
    class Node{
    public:
        T data;
        Node * next;
        Node * prev;
        Node(T data,Node * prev,Node * next){
            this->data=data;
            this->next=next;
            this->prev=prev;
        }
        ~Node(){
            cout<<"Destroy Node"<<endl;
        }
    };

    void add(const T & data);
    void show();
private:
    Node * head=nullptr;
    Node * tail=nullptr;
};
template<typename T>
void LinkedList<T>::add(const T &data) {
    if(this->tail==nullptr){
        this->head=this->tail=new Node(data,nullptr,nullptr);
        return ;
    }
    Node * newNode=new Node(data,nullptr,nullptr);
    this->tail->next=newNode;
    newNode->prev=this->tail;
    this->tail=newNode;
}
template<typename T>
void LinkedList<T>::show() {
    if(this->head==nullptr){
        return;
    }
    Node * current=head;
    do{
        cout<<current->data<<endl;
        current=current->next;
    }while(current!= nullptr);
}
#endif //LIST_LINKEDLIST_H
