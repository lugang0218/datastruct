#ifndef LIST_SINGLELISTSTACK_H
#define LIST_SINGLELISTSTACK_H
#include"SingleList.h"
template<typename T>
class SingleListStack{
public:
    void push(const T &value);
    T pop();
private:
    SingleList<T> *singleList=nullptr;
};
template<typename T>
void SingleListStack<T>::push(const T &value) {
    if(singleList==nullptr){
        singleList=new SingleList<T>();
    }
    singleList->add(value);
}


template<typename T>
T SingleListStack<T>::pop() {
    if(singleList->isEmpty()){
        throw string("stack is empty");
    }
    return singleList->removeFromHead();
}

#endif //LIST_SINGLELISTSTACK_H
