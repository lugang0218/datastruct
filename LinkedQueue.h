//
// Created by lugang on 2021/6/28.
//

#ifndef LIST_LINKEDQUEUE_H
#define LIST_LINKEDQUEUE_H

#include<iostream>
using namespace std;
template<typename T>
class LinkedQueue{
public:
    class Node{
    public:
        T data;
        Node * next;
        Node * prev;
        Node(T value,Node * prev,Node * next){
            this->data=value;
            this->next=next;
            this->prev=prev;
        }
    };
    ~LinkedQueue();
    void offer(const T & data);
    T  poller();
    T  peek();
    bool isEmpty() const;
    int getSize() const;
private:
    int size=0;
    Node * head=nullptr;
    Node * tail=nullptr;
};
template<typename T>
LinkedQueue<T>::~LinkedQueue() {
    cout<<"Destroy LinkedQueue"<<endl;
    if(this->head==nullptr){
        this->tail=nullptr;
        return ;
    }
    Node * next=this->tail;
    Node * tempHead=this->head;
    while(tempHead!=nullptr){
        next=tempHead->next;
        delete tempHead;
        tempHead=next;
    }
    this->head= nullptr;
    this->tail=nullptr;
    this->size=0;
}
template<typename T>
void LinkedQueue<T>::offer(const T &data) {
    if(this->tail==nullptr){
        this->head=this->tail=new Node(data,nullptr,nullptr);
        size++;
        return ;
    }
    Node * newNode=new Node(data,this->tail,nullptr);
    this->tail->next=newNode;
    this->tail=newNode;
    size++;
}
template<typename T>
T LinkedQueue<T>::poller() {

    if(this->head==nullptr){
        throw new string ("head == nullptr");
    }
    T data=this->head->data;
    Node * freeNode=this->head;
    this->head=this->head->next;
    if(this->head!=nullptr){
        this->head->prev=nullptr;
    }
    else{
        this->tail=nullptr;
    }
    //free old head
    delete freeNode;
    size--;
    return data;
}
template<typename T>
T  LinkedQueue<T>::peek(){
    if(this->head==nullptr){
        throw new string("head nullptr");
    }
    return this->head->data;
}

template<typename T>
bool LinkedQueue<T>::isEmpty() const {
    return size==0;
}


template<typename T>
int LinkedQueue<T>::getSize() const {
    return size;
}

#endif //LIST_LINKEDQUEUE_H
