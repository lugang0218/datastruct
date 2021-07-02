#include<iostream>
#include"RedBlackTree.h"
using namespace std;
int main(){
    RedBlackTree<int,int> redBlackTree;
    redBlackTree.put(1,1);
    redBlackTree.put(2,2);
    redBlackTree.put(3,3);
    redBlackTree.put(4,4);
    redBlackTree.put(5,5);
    redBlackTree.put(6,5);
    redBlackTree.put(7,7);
    redBlackTree.put(8,8);
    redBlackTree.levelOrder();
}