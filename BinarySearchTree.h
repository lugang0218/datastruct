//
// Created by lugang on 2021/6/28.
//
#include<iostream>
#include<queue>
#ifndef LIST_BINARYSEARCHTREE_H
#define LIST_BINARYSEARCHTREE_H
#include"LinkedQueue.h"
#include<cmath>
using namespace std;
template<typename E>
class BinarySearchTree{
public:
    class Node{
    public:
        E value;
        Node * left;
        Node * parent;
        Node * right;
        Node(E value,Node * parent,Node * left,Node * right);
        Node(E value,Node * parent);
        ~Node();
    };
    ~BinarySearchTree();
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree<E> &binarySearchTree);
    E & operator [](const int & index);
    bool operator ==(const BinarySearchTree<int> &tree);
    void add(const E & value);
    void preOrder() const ;
    void midOrder() const ;
    void postOrder() const;
    void levelOrder() const;
    int height();
    Node * parentNode(const Node *node);
    bool isEmpty() const;//是否空树
    bool contains(const E & value) const;

    void remove(const E & value);

    void test(){
        Node *result=this->findNode(150);
        Node *node=precursorNode(result);
        if(node==nullptr){
            cout<<"no precursorNode"<<endl;
        }
        else{
            cout<<node->value;
        }
    }
private:
    int size=0;
    Node * root=nullptr;
    void doPreOrder( const Node const * node) const ;
    void doMidOrder( const Node const  * node) const ;
    void doPostOrder( const Node const  * node) const ;
    int doHeight(const Node const * node) const;
    void doLevelOrder( Node  *node) const ;
    bool isRootNode(const Node & root) const;
    bool hasNoChildren(Node * node) const;
    bool hasTwoChildren(Node * node) const;
    bool hasOneChildren(Node * node) const;
    Node * precursorNode(Node * node) const;
    Node * findNode(const E & value) const;
    int getSize() const;
    void doCopyNode(Node * node,Node * parent,Node * newNode,Node * neParent);

    bool doCompare(Node * node1,Node * node2);

    void doRemove(Node * node);

    //获取单个子节点
    Node * getOneChild(Node * parent);
};
template<typename T>
BinarySearchTree<T>::BinarySearchTree() {
    cout<<"Empty Constructor"<<endl;
}
template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T> &binarySearchTree) {
    cout<<"Copy Constructor"<<endl;
    this->size=binarySearchTree.size;
    if(binarySearchTree.root==nullptr){
        this->root=nullptr;
        return ;
    }
    doCopyNode(binarySearchTree.root,nullptr,nullptr,nullptr);
}
template<typename T>
void BinarySearchTree<T>::doCopyNode(Node *node, Node *parent,Node * newNode,Node * newParent) {
    if(parent==nullptr){
        newNode =new Node(node->value,nullptr,nullptr,nullptr);
        this->root=newNode;
        newParent=newNode;
    }
    else{
        Node * currentNode=new Node(node->value,newParent,nullptr,nullptr);
        if(node==parent->left){
            newParent->left=currentNode;
            newParent=currentNode;
        }
        else if(node==parent->right){
            newParent->right=currentNode;
            newParent=currentNode;
        }
    }
    if(node->left!=nullptr){
        doCopyNode(node->left,node,newNode,newParent);
    }
    if(node->right!=nullptr){
        doCopyNode(node->right,node,newNode,newParent);
    }
}
template<typename T>
BinarySearchTree<T>::~BinarySearchTree(){


    cout<<"Destroy BinarySearchTree"<<endl;
    if(this->root==nullptr){
        return;
    }
    Node * current=this->root;
    queue<Node*> nodeQueue;
    nodeQueue.push(current);
    while(!nodeQueue.empty()){
        Node * node=nodeQueue.front();
        nodeQueue.pop();
        if(node->left!=nullptr){
            nodeQueue.push(node->left);
        }
        if(node->right!=nullptr){
            nodeQueue.push(node->right);
        }
        delete node;
    }
    this->root=nullptr;
}
template<typename E>
BinarySearchTree<E>::Node::Node(E value, Node *parent) {
    this->value=value;
    this->parent=parent;
    this->left=nullptr;
    this->right=nullptr;
}


template<typename E>
BinarySearchTree<E>::Node::Node(E value, Node *parent, Node *left, Node *right) {
    this->value=value;
    this->parent=parent;
    this->left=left;
    this->right=right;
}


template<typename E>
BinarySearchTree<E>::Node::~Node() {
    cout<<this->value<<endl;
    cout<<"Destroy Node"<<endl;
}


template<typename T>
T & BinarySearchTree<T>::operator[](const int &index) {
    //check index index from 1 to size
    if(this->root==nullptr){
        throw string("root==nullptr");
    }
    queue<Node*> nodeQueue;
    Node *current=this->root;
    nodeQueue.push(current);
    int count=1;
    while(!nodeQueue.empty()){
        Node * currentNode=nodeQueue.front();
        nodeQueue.pop();
        if(count==index){
            return currentNode->value;
        }
        if(currentNode->left!=nullptr){
            nodeQueue.push(currentNode->left);
        }
        if(currentNode->right!=nullptr){
            nodeQueue.push(currentNode->right);
        }
        count++;
    }
}

template<typename T>
bool BinarySearchTree<T>::operator==(const BinarySearchTree<int> &tree) {
    if(this->size!=tree.size){
        return false;
    }
    else if(this->root==nullptr&&tree.root==nullptr){
        return true;
    }
    else if(this->root!=nullptr&&tree.root!=nullptr){
        return doCompare(this->root,tree.root);
    }
    else{
        return false;
    }
}
template<typename T>
bool BinarySearchTree<T>::doCompare(Node *node1, Node *node2) {
    if(node1==nullptr&&node2==nullptr){
        return true;
    }
    else if(node1->left==nullptr&&node1->right==nullptr&&node2->left==nullptr&&node2->right==nullptr){
        if(node1->value==node2->value){
            return true;
        }
        return true;
    }
    else{
        return doCompare(node1->left,node2->left)&& doCompare(node1->right,node2->right);
    }
}
template<typename E>
void BinarySearchTree<E>::add(const E &value) {
    if(this->root==nullptr){
        this->root=new Node(value,nullptr,nullptr,nullptr);
        this->size++;
        return ;
    }
    Node *current=this->root;
    Node * parent=nullptr;
    int compareResult=0;
    do{
        parent=current;
        compareResult=value-current->value;
        if(compareResult>0){
            current=current->right;
        }
        else if(compareResult<0){
            current=current->left;
        }
        else{
            current->value=value;
            break;
        }
    }while(current!=nullptr);

    Node * newNode=new Node(value,parent,nullptr,nullptr);
    if(compareResult>0){
        parent->right=newNode;
    }
    else if(compareResult<0){
        parent->left=newNode;
    }
    this->size++;
}
template <typename E>
void BinarySearchTree<E>::preOrder() const  {
    if(this->root==nullptr){
        return ;
    }
    doPreOrder(this->root);
}
template <typename E>
void BinarySearchTree<E>::doPreOrder( const Node const  * node) const  {
    cout<<node->value<<endl;
    if(node->left!=nullptr){
        doPreOrder(node->left);
    }
    if(node->right!=nullptr){
        doPreOrder(node->right);
    }
}
template <typename E>
void BinarySearchTree<E>::midOrder() const {
    if(this->root==nullptr){
        return ;
    }
    doMidOrder(this->root);
}
template <typename E>
void BinarySearchTree<E>::doMidOrder(const Node const *node) const {
    if(node->left!=nullptr) {
        doMidOrder(node->left);
    }
    cout<<node->value<<endl;
    if(node->right!=nullptr){
        doMidOrder(node->right);
    }
}

template <typename E>
void BinarySearchTree<E>::postOrder() const  {
    if(this->root==nullptr){
        return ;
    }
    doPostOrder(this->root);
}
template <typename E>
void BinarySearchTree<E>::doPostOrder(const Node *node) const {
    cout<<node->value<<endl;
    if(node->left!=nullptr){
        doPostOrder(node->left);
    }
    if(node->right!=nullptr){
        doPostOrder(node->right);
    }
}

template<typename E>
void BinarySearchTree<E>::levelOrder() const  {
    if(this->root==nullptr){
        return ;
    }
    doLevelOrder(this->root);
}
template<typename E>
void BinarySearchTree<E>::doLevelOrder( Node *  node) const {
    LinkedQueue<Node *> linkedQueue;
    linkedQueue.offer(node);
    while(!linkedQueue.isEmpty()){
        Node * node=linkedQueue.poller();
        cout<<node->value<<endl;
        if(node->left!=nullptr){
            linkedQueue.offer(node->left);
        }
        if(node->right!=nullptr){
            linkedQueue.offer(node->right);
        }
    }
}
template<typename E>
int BinarySearchTree<E>::height() {
    if(this->root==nullptr) {
        return 0;
    }
    return doHeight(this->root);
}
template<typename E>
int BinarySearchTree<E>::doHeight(const Node const  *node) const  {
    if(node==nullptr){
        return 0;
    }
    else if(node->left==nullptr&&node->right==nullptr){
        return 1;
    }
    else{
        return max(doHeight(node->left), doHeight(node->right))+1;
    }
}
template <typename E>
bool BinarySearchTree<E>::isEmpty() const {
    return this->size==0;
}
template <typename E>
int BinarySearchTree<E>::getSize() const{
    return this->size;
}
template<typename E>
bool BinarySearchTree<E>::hasNoChildren(Node * node) const {
    return node->left==nullptr&&node->right==nullptr;
}
template<typename E>
bool BinarySearchTree<E>::hasTwoChildren(Node * node) const {
    return node->left!=nullptr&&node->right!=nullptr;
}
template<typename E>
bool BinarySearchTree<E>::hasOneChildren( Node *node) const {
    return (node->left!=nullptr&&node->right==nullptr)||(node->left==nullptr&&node->right!=nullptr);
}
//前驱节点
template<typename E>
typename BinarySearchTree<E>::Node* BinarySearchTree<E>::precursorNode(Node * node) const{
    if(node==nullptr){
        return nullptr;
    }
    Node *current=node->left;
    if(current == nullptr){
        //重新查找前驱节点
        current=node;
        Node * parent=current->parent;
        while(parent!= nullptr&&current==parent->left){
            current=parent;
            parent=parent->parent;
        }
        if(parent==nullptr){
            return nullptr;
        }
        return parent;
    }
    else{
        Node *temp=nullptr;
        do {
            temp=current;
            current = current->right;

        }while(current != nullptr);
        return temp;
    }
}

template <typename E>
bool BinarySearchTree<E>::contains(const E &value) const {
    return findNode(value)!=nullptr?true:false;
}
template <typename E>
typename BinarySearchTree<E>::Node * BinarySearchTree<E>::findNode(const E & value) const{
    if(this->root==nullptr){
        return nullptr;
    }
    Node * current=this->root;
    do{
        if(current->value==value){
            return current;
        }
        else if(value>current->value){
            current=current->right;
        }
        else{
            current=current->left;
        }
    }while(current!= nullptr);
    return nullptr;
}
template<typename T>
typename BinarySearchTree<T>::Node * BinarySearchTree<T>::parentNode(const Node *node) {
    return node== nullptr?nullptr:node->parent;
}

template<typename T>

typename BinarySearchTree<T>::Node * BinarySearchTree<T>::getOneChild(Node *parent) {
    if(parent==nullptr){
        return nullptr;
    }
    else if(parent->left!=nullptr){
        return parent->left;
    }
    else if(parent->right!=nullptr){
        return parent->right;
    }
    else{
        return nullptr;
    }
}
template<typename T>
void BinarySearchTree<T>::remove(const T &value) {
    Node * node= findNode(value);
    if(node==nullptr){
        return ;
    }
    else if(hasTwoChildren(node)){
        //找到前驱节点
        Node *prevNode=precursorNode(node);
        node->value=prevNode->value;
        doRemove(prevNode);
    }
    else{
        doRemove(node);
    }
}
template<typename T>
void BinarySearchTree<T>::doRemove(Node *node) {
    if(hasNoChildren(node)){
        if(node==this->root){
            delete node;
            this->root=nullptr;
        }
        else{
            Node * parent=node->parent;
            if(node==parent->left){
                parent->left=nullptr;
            }
            else if(node==parent->right){
                parent->right=nullptr;
            }
            delete node;
        }
    }
        //删除只有一个节点的子节点
    else if(hasOneChildren(node)){
        //拿到待删除节点的父节点
        Node * parent=parentNode(node);
        //拿到待删除节点的子节点
        Node * child= getOneChild(node);

        // first check child
        if(child==nullptr){
            return ;
        }
        //删除的是根节点
        Node * toFreeNode=nullptr;
        if(parent==nullptr){
            toFreeNode=this->root;
            if(child==node->left){

                this->root=node->left;
                this->root->parent=nullptr;
            }
            else if(child==node->right){
                this->root->parent=nullptr;
                this->root=node->right;
            }
        }
        else{
            toFreeNode=node;
            if(node==parent->left){
                child->parent=parent;
                parent->left=child;
            }
            else if(node==parent->right){
                child->parent=parent;
                parent->right=child;
            }
        }
        if(toFreeNode!=nullptr){
            delete toFreeNode;
        }
    }
}
#endif //LIST_BINARYSEARCHTREE_H
