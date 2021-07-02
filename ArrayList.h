#ifndef LIST_ARRAYLIST_H
#define LIST_ARRAYLIST_H
#include<iostream>
#include<ostream>
using namespace std;
template <typename T>
class ArrayList{
private:
    static const int DEFAULT_CAPACITY=10;
    int capacity=0;
    int size=0;
    T * array=nullptr;
public:
    //构造 析构 拷贝构造 拷贝赋值
    ArrayList(const int & capacity);
    ArrayList(const T * element,int elementLength,int capacity);
    ArrayList();
    ~ArrayList();
    ArrayList(const ArrayList<T> &list);
    //运算符重载函数
    T & operator[](const int &index) const;
    T & operator()(const int &index) const;
    ArrayList & operator= (const ArrayList<T> &arrayList);
    bool operator ==(const ArrayList<T> &list) const;
    bool operator !=(const ArrayList<T> &list) const;
    //普通成员函数
    void add(const int & index,const T & value);
    void add(const T & value);
    void show() const;
    int getSize() const;
    bool isEmpty() const;
    T set(const int &index,const T &value);
    T get(const int &index);
    T remove(const int &index);
    void copyToNewArray(const int &newLength);
    bool reSize(const int &minSize) const;
    int growCapacity(const int &minSize) const;
    bool contains(const T & data);
};
template<typename T>
ArrayList<T>::ArrayList(const T *element, int elementLength, int capacity) {
    this->capacity=capacity;
    this->array=new T[this->capacity];
    for(int i=0;i<elementLength;i++){
        this->array[size++]=element[i];
    }
}
template<typename T>
ArrayList<T>::ArrayList()  {
    this->capacity=DEFAULT_CAPACITY;
    this->array=nullptr;
}
template<typename T>
ArrayList<T>::ArrayList(const int &capacity) {
    this->capacity=capacity;
    this->array=nullptr;
}


//拷贝构造函数
template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &list) {
    cout<<"copy constructor"<<endl;
    //申请空间
    this->capacity=list.capacity;
    if(list.array!=nullptr){
        this->array=new T[this->capacity];
    }
    //copy data
    for(int i=0;i<list.size;i++){
        this->array[i]=list.array[i];
    }
    this->size=list.size;
}

//拷贝赋值函数
template<typename T>
ArrayList<T> & ArrayList<T>::operator=(const ArrayList<T>  &arrayList) {
    this->capacity=arrayList.capacity;
    this->size=arrayList.size;
    if(arrayList.array==nullptr){
        return * this;
    }
    this->array=new T[this->capacity];
    for(int i=0;i<this->size;i++){
        this->array[i]=arrayList[i];
    }
    return * this;
}
template<typename T>
void ArrayList<T>::show() const {
    for(int i=0;i<size;i++){
        cout<<array[i]<<endl;
    }
}
template<typename T>
ArrayList<T>::~ArrayList() {
    cout<<"destroy constructor"<<endl;
    if(this->array!=nullptr){
        delete []this->array;
        this->array=nullptr;
        this->size=0;
    }
}
template<typename T>
T & ArrayList<T>::operator[](const int &index) const {
    return array[index];
}

template<typename T>
T&  ArrayList<T>::operator()(const int &index) const{
    return array[index];
}
template<typename T>
ostream & operator <<(ostream &os, ArrayList<T> & list){
    for(int i=0;i<list.getSize();i++){
        os<<list[i]<<endl;
    }
    return os;
}

template<typename T>
bool ArrayList<T>::operator ==(const ArrayList<T> &list) const{
    if(this->size!=list.size){
        return false;
    }
    if(this->array!=nullptr&&list.array!=nullptr){
        for(int i=0;i<this->size;i++){
            if(this->array[i]==list.array[i]){
                continue;
            }
            return false;
        }
        return true;
    }
    else if(this->array==nullptr&&list.array==nullptr){
        return true;
    }
    else{
        return false;
    }
}
template<typename T>
bool ArrayList<T>::operator !=(const ArrayList<T> &list) const{
    if(this->size!=list.size){
        return true;
    }
    if(this->array!=nullptr&&list.array!=nullptr){
        for(int i=0;i<this->size;i++){
            if(this->array[i]!=list.array[i]){
                return true;
            }
        }
        return false;
    }
    else if(this->array==nullptr&&list.array==nullptr){
        return false;
    }
    else{
        return true;
    }
}

template<typename T>
int ArrayList<T>::getSize()  const{
    return size;
}
template<typename T>
bool ArrayList<T>::isEmpty() const {
    return size==0;
}

template<typename T>
void ArrayList<T>::add(const T &value) {
    add(size,value);
}

template <typename T>
void ArrayList<T>::add(const int &index, const T &value) {
    if(this->array==nullptr){
        this->array=new T[capacity];
    }
    if(reSize(this->size+1)){
        copyToNewArray(growCapacity(this->size+1));
    }
    //check index
    for (int i = size; i > index; i--) {
        array[i] = array[i - 1];
    }
    array[index] = value;
    this->size++;
}

template<typename T>
T ArrayList<T>::set(const int &index, const T &value) {
    //check index
    T oldData=this->array[index];
    this->array[index]=value;
    return oldData;
}

template<typename T>
T ArrayList<T>::get(const int &index) {
    //check index
    return this->array[index];
}
template<typename T>
T ArrayList<T>::remove(const int &index) {
    //check
    T oldData=this->array[index];
    for(int i=index+1;i<size;i++){
        this->array[i-1]=this->array[i];
    }
    this->size--;
    return oldData;
}


template<typename T>
bool ArrayList<T>::reSize(const int &minSize) const {
    return minSize>capacity;
}

template<typename T>
int  ArrayList<T>::growCapacity(const int &minSize) const {
    int newLength=this->capacity+this->capacity;
    return newLength;
}
template<typename T>
void ArrayList<T>::copyToNewArray(const int &newLength) {


    cout<<"grow capacity begin"<<endl;

    //申请一段新的存储空间
    T *newArray=new T[newLength];
    //拷贝旧的数组到新的数组
    for(int i=0;i<this->size;i++){
        newArray[i]=this->array[i];
    }
    //释放原有的内存空间
    delete []this->array;
    //让array指向新的空间
    this->array=newArray;
    this->capacity=newLength;
}
template <typename T>
bool ArrayList<T>::contains(const T &data) {
    if(this->array==nullptr){
        return false;
    }
    for(int i=0;i<size;i++){
        //Ｔ　需要重载＝＝比较符号
        if(array[i]==data){
            return true;
        }
    }
    return false;
}
#endif //LIST_ARRAYLIST_H
