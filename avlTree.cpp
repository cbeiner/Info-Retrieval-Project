#include "avlNode.h"
#include <iostream>
#include <string>
#include<algorithm>
#include<fstream>
#include<ctime>
using namespace std;

// This is AVL tree that we wrote for our CISC220 class that will significantly help speed up lookup for stopwords 

avlNode::avlNode(string key){
    this->data = key;
}
avlNode::~avlNode(){
    if(left_child)
        delete left_child;
    if(right_child)
        delete right_child;
}

// Height of the tree
int avlNode::height(){
    if(this != NULL){
        int l_height = this->left_child->height();
        int r_height = this->right_child->height();
        return max(l_height, r_height) + 1;
    }
    return 0;
}

// difference in height of left and right children if the whole is unbalanced
int avlNode::diff(){
    return this->left_child->height() - this->right_child->height(); //height accounts for NULL
}

bool avlNode::isIn(string key){
    if(this == NULL)
        return false;
    
    if (this->data.compare(key) == 0)
        return true;
    else if (this->data.compare(key) < 0)
        return this->left_child->isIn(key);
    else if (this->data.compare(key) > 0)
        return this->right_child->isIn(key);
}


avlNode* avlNode::rrRotation(){
    avlNode* replacement = this->right_child;
    this->right_child = replacement->left_child;
    replacement->left_child = this;
    return replacement;
}

avlNode* avlNode::llRotation(){
    avlNode* replacement = this->left_child;
    this->left_child = replacement->right_child;
    replacement->right_child = this;
    return replacement;
}

avlNode* avlNode::lrRotation(){
    avlNode* replacement = this->left_child;
    this->left_child = replacement->rrRotation();
    return this->llRotation();
}

avlNode* avlNode::rlRotation(){
    avlNode* replacement = this->right_child;
    this->right_child = replacement->llRotation();
    return this->rrRotation();
}

avlNode* avlNode::balance(){
    avlNode* replacement = this;
    int bal_factor = replacement->diff();
    
    if(bal_factor > 1){
        if(replacement->left_child->diff() > 0)
            replacement = replacement->llRotation();
        else
            replacement = replacement->lrRotation();
    }
    else if(bal_factor < -1){
        if (replacement->right_child->diff() > 0)
            replacement = replacement->rlRotation();
        else
            replacement = replacement->rrRotation();
    }
    return replacement;
}

avlNode* avlNode::insert(string value){
    if(this == NULL || (this->data.compare("") == 0)){
        avlNode* root = new avlNode(value);
        root->left_child = NULL;
        root->right_child = NULL;
        return root;
    }
    
    if(this->data.compare(value) < 0){
        this->left_child = this->left_child->insert(value);
        return this->balance();
    }
    else{
        this->right_child = this->right_child->insert(value);
        return this->balance();
    }
}


void avlNode::display(int level, int leftOrRight){
    if(this->left_child)
        this->left_child->display(level + 1, -1);
    
    for(int i = 1; i < level; i++){
        // if(i == (level - 1))
        //     if(leftOrRight != 0){
        //         cout << (leftOrRight < 0 ? "   v" : "   ^");
        //         cout << "====";
        //     }
        // else
        cout << "\t";
    }
    cout << this->data << endl;
    if(this->right_child)
        this->right_child->display(level + 1, 1);
}

void avlNode::display(avlNode* root, avlNode* point, int level){
    if(point != NULL){
        display(root, point->right_child, level + 1);
        cout << endl << endl;
        if (point == root)
            cout << "Root -> ";
        for (int i = 0; i < level && point != root; i++)
            cout << "            ";
        cout << point->data;
        
        display(root, point->left_child, level + 1);
    }
}
