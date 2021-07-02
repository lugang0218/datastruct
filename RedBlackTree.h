//
// Created by lugang on 2021/7/2.
//


//如果没有定义它
#ifndef LIST_REDBLACKTREE_H

//就定义一个
#define LIST_REDBLACKTREE_H
#include<queue>
#include<iostream>
#include<cmath>
#include"LinkedQueue.h"
using namespace std;
template<typename K,typename V>
class RedBlackTree{
public:
    static const bool RED= false;
    const static bool BLACK=true;
    class Node{
    public:
        K key;
        V value;
        Node * left;
        Node * parent;
        Node * right;
        bool color=BLACK;
        Node(K key,V value,Node * parent,Node * left,Node * right,bool color){
            this->key=key;
            this->value=value;
            this->parent=parent;
            this->left=left;
            this->right=right;
            this->color=color;
        }

        Node(K key,V value,Node * parent){
            this->key=key;
            this->value=value;
            this->parent=parent;
            this->left=nullptr;
            this->right=nullptr;
            this->color=BLACK;
        }
        ~Node();
    };
    RedBlackTree();
    ~RedBlackTree();
    RedBlackTree(const RedBlackTree& redBlackTree);
    void doCopyNode(Node *node, Node *parent,Node * newNode,Node * newParent);
    void preOrder();
    void doProOrder(Node * node);
    void leftRotate(Node * node);
    void rightRotate(Node * node);
    bool colorOf(Node * node);
    Node * parentOf(Node * node);
    Node * leftOf(Node * node);
    Node * rightOf(Node * node);
    //查找node的节点的前驱节点
    Node * predecessor(Node * node);
    //查找node节点的后继节点
    Node * successor(Node * node);
    K & findMaxKey() const;
    K & findMinKey() const;
    K & getRootKey() const;
    bool containsKey(const K & key) const;
    bool containsValue(const V & value) const;
    void setColor(Node * node,bool color);
    int height();

    void put(const K & key,const V & value);
    void removeKey(const K & key);
    V set(const K & key,const V & newValue);
    void levelOrder();
    const V& get(const K & key);
private:
    Node * root=nullptr;
    int size=0;
    void doPreOrder(Node * node);

    int doHeight(Node * node);

    Node * findNode(const K & key) const;

    void removeNode(Node * node);


    //添加节点之后调整
    void afterPut(Node *node);

    //删除节点之后调整
    void afterRemove(Node *node);


    void doLevelOrder(Node * node);


};
template<typename K,typename V>
RedBlackTree<K,V>::Node::~Node() {
    cout<<"Delete Node"<<endl;
}
template<typename K,typename V>
RedBlackTree<K,V>::RedBlackTree() {
    cout<<"Empty Constructor"<<endl;
}
template<typename K,typename V>
RedBlackTree<K,V>::RedBlackTree(const RedBlackTree<K,V> &redBlackTree) {
    cout<<"Copy Constructor"<<endl;
    this->size=redBlackTree.size;
    if(redBlackTree.root == nullptr){
        this->root=nullptr;
        return ;
    }
    doCopyNode(redBlackTree.root, nullptr, nullptr, nullptr);
}
template<typename K, typename V>
void RedBlackTree<K,V>::doCopyNode(Node *node, Node *parent,Node * newNode,Node * newParent) {
    if(parent==nullptr){
        newNode =new Node(node->key,node->value,nullptr,nullptr,nullptr,node->color);
        this->root=newNode;
        newParent=newNode;
    }
    else{
        Node * currentNode=new Node(node->key,node->value,newParent,nullptr,nullptr,node->color);
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
template<typename K,typename V>
RedBlackTree<K,V>::~RedBlackTree(){
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

template<typename K,typename V>
int RedBlackTree<K,V>::height() {
    if(root==nullptr){
        return 0;
    }

    return doHeight(root);

}


template<typename K,typename V>
int RedBlackTree<K,V>::doHeight(Node * node) {
    if(node== nullptr){
        return 0;
    }
    if(node->left==nullptr&&node->right==nullptr){
        return 1;
    }
    return max(doHeight(node->left), doHeight(node->right))+1;
}


template<typename K,typename V>
void RedBlackTree<K,V>::preOrder() {
    if(root!=nullptr){
        doPreOrder(root);
    }
}
template<typename K,typename V>
void RedBlackTree<K,V>::levelOrder() {
    if(root!=nullptr){
        doLevelOrder(root);
    }
}

template<typename K,typename V>
void RedBlackTree<K,V>::doLevelOrder(Node * node) {
    LinkedQueue<Node *> nodeQueue;
    //记录放入的次数，每放入一个节点，count就+1

    //求解树的高度
    int height=0;
    nodeQueue.offer(node);
    while(!nodeQueue.isEmpty()){
        height++;
        int nodeSize=nodeQueue.getSize();
        for(int i=0; i < nodeSize; i++){
            Node * current=nodeQueue.poller();
            string  color=current->color==BLACK?"black":"red";
            cout<<current->key<<"===>"<<color<<" ";
            if(current->left!= nullptr){
                nodeQueue.offer(current->left);
            }
            if(current->right!=nullptr){
                nodeQueue.offer(current->right);
            }
        }
        cout<<endl;
    }
    cout<<"height="<<height<<endl;
}


template<typename K,typename V>
void RedBlackTree<K,V>::doPreOrder(Node *node) {
    if(node->color==RED){
        cout<<"node-"<<node->value<<"red"<<endl;
    }
    else{
        cout<<"node-"<<node->value<<"black"<<endl;
    }
    if(node->left!= nullptr){
        doPreOrder(node->left);
    }
    if(node->right!=nullptr){
        doPreOrder(node->right);
    }
}
template<typename K,typename V>
void RedBlackTree<K,V>::leftRotate(Node *node) {
    if (node == nullptr) {
        return;
    }
    Node * rightNode=node->right;
    node->right=rightNode->left;

    if(rightNode->left != nullptr) {
        rightNode->left->parent=node;
    }
    rightNode->parent=node->parent;
    if(node->parent== nullptr) {
        rightNode->parent == nullptr;
        this->root = rightNode;
    }

    else if(node==node->parent->left) {
        node->parent->left=rightNode;
    }
    else if(node==node->parent->right) {
        node->parent->right=rightNode;
    }
    node->parent=rightNode;
    rightNode->left=node;
}
template<typename K,typename V>
void RedBlackTree<K,V>::rightRotate(Node *node) {
    if (node == nullptr) {
        return;
    }
    Node * leftNode=node->left;
    node->left=leftNode->right;

    if(leftNode->right!= nullptr) {
        leftNode->right->parent=node;
    }
    leftNode->parent=node->parent;
    if(node->parent== nullptr) {
        this->root = leftNode;
    }

    else if(node==node->parent->left) {
        node->parent->left=leftNode;
    }
    else if(node==node->parent->right) {
        node->parent->right=leftNode;
    }
    node->parent=leftNode;
    leftNode->right=node;
}

template <typename K,typename V>
typename RedBlackTree<K,V>::Node * RedBlackTree<K,V>::parentOf(Node *node) {
    return node!= nullptr?node->parent:nullptr;
}




template<typename K,typename V>
typename RedBlackTree<K,V>::Node* RedBlackTree<K,V>::leftOf(Node *node) {
    return node!=nullptr?node->left:nullptr;
}
template<typename K,typename V>
typename RedBlackTree<K,V>::Node* RedBlackTree<K,V>::rightOf(Node *node) {
    return node!=nullptr?node->right:nullptr;
}



//空节点颜色为黑色
template<typename K,typename V>
bool RedBlackTree<K,V>::colorOf(Node *node) {
    return node==nullptr?BLACK:node->color;
}

template<typename K,typename V>
bool RedBlackTree<K,V>::containsKey(const K &key) const {
    return findNode(key)!=nullptr;
}


template<typename K,typename V>
bool RedBlackTree<K,V>::containsValue(const V & value) const {
    if(root==nullptr){
        return false;
    }

    queue<Node*> nodeQueue;
    nodeQueue.push(root);
    while(!nodeQueue.empty()){
        Node * node=nodeQueue.front();
        if(node->value==value){
            return true;
        }
        if(node->left!= nullptr){
            nodeQueue.push(node->left);
        }
        if(node->right!=nullptr){
            nodeQueue.push(node->right);
        }
    }
    return false;

}

template<typename K,typename V>
K & RedBlackTree<K,V>::findMaxKey() const {
    if(root!= nullptr){
        Node * current=root;
        while(current->right!=nullptr){
            current=current->right;
        }
        return current->value;
    }
}

template<typename K,typename V>
K & RedBlackTree<K,V>::findMinKey() const {
    if(root!= nullptr){
        Node * current=root;
        while(current->left!=nullptr){
            current=current->left;
        }
        return current->value;
    }
}




template<typename K,typename V>
typename RedBlackTree<K,V>::Node * RedBlackTree<K,V>::findNode(const K &key) const {
    if(this->root==nullptr){
        return nullptr;
    }
    Node * current=this->root;
    do{
        if(current->key==key){
            return current;
        }
        else if(key>current->key){
            current=current->right;
        }
        else{
            current=current->left;
        }
    }while(current!= nullptr);
    return current;
}



template<typename K,typename V>
void RedBlackTree<K,V>::put(const K &key, const V &value) {
    if (this->root == nullptr) {
        this->root = new Node(key, value, nullptr);
        size++;
        return;
    }
    Node *current = this->root;
    Node *parent = nullptr;
    int compareResult = 0;
    while (current != nullptr) {
        parent = current;
        compareResult=key-current->key;
        if (compareResult>0) {
            current = current->right;
        } else if (compareResult==0) {
            current->value = value;
            return;
        } else {
            current = current->left;
        }
    }
    Node *newNode = new Node(key, value, parent);
    if (compareResult > 0) {
        parent->right = newNode;
    } else {
        parent->left = newNode;
    }
    size++;
    //添加之后做出调整
    afterPut(newNode);

}
template<typename K,typename V>
void RedBlackTree<K,V>::setColor(Node *node, bool color) {
    if(node!=nullptr){
        node->color=color;
    }
}


//寻找前驱节点
template<typename K,typename V>
typename RedBlackTree<K,V>::Node * RedBlackTree<K,V>::predecessor(Node *node) {
    Node * leftNode= leftOf(node);
    //如果左子节点不为空 往左子节点向右一直遍历
    if(leftNode!=nullptr){
        while(leftNode->right!= nullptr){
            leftNode=leftNode->right;
        }
        return leftNode;
    }
    //如果左子节点为空 向上一直找到第一个拐点
    Node * current=node;
    Node * parent= parentOf(current);
    while(parent!=nullptr&&current== leftOf(parent)){
        current=parent;
        parent=parent->parent;
    }
    return parent;
}
//寻找后继节点
template<typename K,typename V>
typename RedBlackTree<K,V>::Node * RedBlackTree<K,V>::successor(Node *node) {
    Node * rightNode= rightOf(node);
    if(rightNode!=nullptr){
        while(rightNode!=nullptr) {
            rightNode = rightNode->left;
        }
        return rightNode;
    }
    Node * current=node;
    Node * parent=parentOf(current);
    while(parent!=nullptr&&current== rightOf(parent)){
        current=parent;
        parent=parent->parent;
    }
    return parent;
}
//添加做出调整
template<typename K,typename V>
void RedBlackTree<K,V>::afterPut(Node *node) {
    //检查node是否为空
    if(node==nullptr){
        return ;
    }
    //添加节点都是红色的
    node->color=RED;
    //当node!=root时候 第一表示还需要调整 第二表示node的parent一定不为空
    //如果添加node的父节点是红色,那么就需要调整
    while(node!=nullptr&&node!=root&&node->parent->color==RED){
        //如果父亲是爷爷的左孩子
        Node * parent= parentOf(node);
        Node * grand= parentOf(parent);
        if(leftOf(grand)==parent){
            //获取叔叔节点
            Node * uncle= rightOf(grand);
            //如果叔叔节点存在
            if(colorOf(uncle) == RED){
                //将父亲节点染黑
                setColor(parent,BLACK);
                //将叔叔节点染黑
                setColor(uncle, BLACK);
                //将爷爷节点染红
                setColor(grand,RED);
                node=grand;
            }
            else{
                //如果不是标准左三 先旋转一下
                if(node== rightOf(parent)){
                    //先围绕父亲进行右旋

                    leftRotate(parent);
                }
                setColor(parent,BLACK);
                setColor(grand,RED);
                rightRotate(grand);
            }
        }
        else if(rightOf(grand)==parent){
            //获取叔叔节点
            Node * uncle= leftOf(grand);
            //如果叔叔节点存在
            if(colorOf(uncle) == RED){
                //将父亲节点染黑
                setColor(parent,BLACK);
                //将叔叔节点染黑
                setColor(uncle, BLACK);
                //将爷爷节点染红
                setColor(grand,RED);
                node=grand;
            }
            else{
                //如果不是标准左三 先旋转一下
                if(node== leftOf(parent)){
                    //先围绕父亲进行右旋

                    rightRotate(parent);
                }
                setColor(parent,BLACK);
                setColor(grand,RED);
                leftRotate(grand);
            }
        }
    }
    setColor(root,BLACK);
}
template<typename K,typename V>

void RedBlackTree<K,V>::removeKey(const K &key) {
    Node * node=findNode(key);
    if(node==nullptr){
        return ;
    }
    removeNode(node);
}
//删除node节点
template<typename K,typename V>
void RedBlackTree<K,V>::removeNode(Node *node) {
    if (node == nullptr) {
        return;
    }
    //如果删除节点有两个子节
    if (leftOf(node) != nullptr && rightOf(node) != nullptr) {
        //拿到后继节点
        Node *s = successor(node);
        node->key = s->key;
        node->value = s->value;
        //让node指向前驱节点 统一删除
        node = s;
    }
    //删除一个节点的情况
    //查找待删除节点node的孩子
    Node *replacement = node->left != nullptr ? node->left : node->right;
    Node *freeNode = nullptr;
    //待删除节点node的孩子不为空
    if (replacement != nullptr) {
        replacement->parent = node->parent;
        if (node->parent == nullptr) {
            freeNode = root;
            root = replacement;
        } else if (node == node->parent->left) {
            freeNode = node;
            node->parent->left = replacement;
        } else {
            freeNode = node;
            node->parent->right = replacement;
        }
        node->left = node->right = node->parent = nullptr;
        //此时node节点已经被删除了 但是node节点没有置空
        //node 真正要删除的节点
        //如果node的颜色是黑色，需要调整它的子节点，并且它的子节点的颜色一定是红色，这点由红黑色的性质可以知道
        if(node->color==BLACK){
            afterRemove(replacement);
        }
    } else if (node->parent == nullptr) {
        freeNode = root;
        root = nullptr;
    }
        //能来到这儿，说明删除节点node的左右孩子都为空，此时如果node的颜色是红色，不用进行调整，如果node节点的颜色是黑色，就要进行调整
        //在删除之前进行调整
    else {
        freeNode = node;

        //如果node节点的颜色是黑色，先进行调整
        if(node->color==BLACK){
            //对node进行调整
            afterRemove(node);
        }
        if (node->parent != nullptr) {
            if (node == node->parent->left) {
                node->parent->left = nullptr;
            } else {
                node->parent->right = nullptr;
            }
        }
    }
    if (freeNode != nullptr) {
        delete freeNode;
    }
}
//删除节点之后做出调整
template<typename K,typename V>
void RedBlackTree<K,V>::afterRemove(Node *node){
    //如果node还没有到达root并且node的颜色是黑色,就需要进行调整
    //如果删除节点是父节点的左孩子
    while(node!=root&&node->color==BLACK){
        if(node== leftOf(parentOf(node))){
            //寻找兄弟节点
            Node * slider=  rightOf(parentOf(node));
            //如果兄弟节点的颜色是红色，如果这棵树转换成为234树红色节点将会向上移动一层与黑色节点合并，所以需要进行旋转找到真正的兄弟节点
            if(colorOf(slider)==RED){
                //假的兄弟节点染成黑色，父节点染成红色，然后沿着父节点进行左旋
                setColor(slider,BLACK);
                setColor(parentOf(node),RED);
                leftRotate(parentOf(node));
                //重新找到兄弟节点
                slider= rightOf(parentOf(node));
            }
            //如果兄弟节点没有,如果兄弟节点的左右节点都为黑色或者兄弟节点是一个黑色子节点（不可能出现兄弟节点只有一个黑色字节这种情况，这样就不平衡）
            if(colorOf(leftOf(slider))==BLACK&& colorOf(rightOf(slider))==BLACK){
                //牺牲兄弟节点以达到平衡
                setColor(slider,RED);
                //递归向上处理
                node= parentOf(node);
            }
            else{
                //如果兄的节点是3节点，并且兄弟节点的孩子在左边，需要旋转一次
                if(colorOf(rightOf(slider))==BLACK){
                    setColor(slider,RED);
                    setColor(rightOf(slider),BLACK);
                    rightRotate(slider);
                    //重新赋值兄弟节点
                    slider= rightOf(parentOf(node));
                }
                setColor(slider, colorOf(parentOf(node)));
                setColor(parentOf(node),BLACK);
                setColor(rightOf(slider),BLACK);
                //沿着父亲左旋
                leftRotate(parentOf(node));
                node=root;
            }
        }

        else{
            //寻找兄弟节点
            Node *slider= leftOf(parentOf(node));
            //如果兄弟节点的颜色是红色，如果这棵树转换成为234树红色节点将会向上移动一层与黑色节点合并，所以需要进行旋转找到真正的兄弟节点
            if(colorOf(slider)==RED){
                //假的兄弟节点染成黑色，父节点染成红色，然后沿着父节点进行右旋
                setColor(slider,BLACK);
                setColor(parentOf(node),RED);
                rightRotate(parentOf(node));
                //重新找到兄弟节点
                slider= leftOf(parentOf(node));
            }
            //如果兄弟节点没有,如果兄弟节点的左右节点都为黑色或者兄弟节点是一个黑色子节点（不可能出现兄弟节点只有一个黑色字节这种情况，这样就不平衡）
            if(colorOf(leftOf(slider))==BLACK&& colorOf(rightOf(slider))==BLACK){
                //牺牲兄弟节点以达到平衡
                setColor(slider,RED);
                //递归向上处理
                node= parentOf(node);
            }
            else{
                //如果兄的节点是3节点，并且兄弟节点的孩子在左边，需要旋转一次
                if(colorOf(leftOf(slider))==BLACK){
                    setColor(slider,RED);
                    setColor(rightOf(slider),BLACK);
                    leftRotate(slider);
                    //重新赋值兄弟节点
                    slider= leftOf(parentOf(node));
                }
                setColor(slider, colorOf(parentOf(node)));
                setColor(parentOf(node),BLACK);
                setColor(leftOf(slider),BLACK);
                //沿着父亲左旋
                leftRotate(parentOf(node));
                node=root;
            }
        }
    }
    //简单情况的删除，直接将替代节点染成黑色，当真正的黑色节点被删除的时候，这个替代节点变成黑色，就能够保证平衡
    setColor(node,BLACK);
}

template<typename K,typename V>
V RedBlackTree<K,V>::set(const K &key, const V &newValue) {
    Node * node= findNode(key);
    if(node==nullptr){
        throw 123;
    }
    V oldValue=node->value;
    node->value=newValue;
    return oldValue;
}
template<typename K,typename V>
const V& RedBlackTree<K,V>::get(const K &key) {
    Node *node = findNode(key);
    return node->value;
}
#endif //LIST_REDBLACKTREE_H
