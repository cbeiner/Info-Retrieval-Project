#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>

#ifndef KNOWLEDGEBASE_H
#define KNOWLEDGEBASE_H

class Node{

    
    public:
        std::string color;
        int depth;
        Node* parent;
        std::string data;
        std::vector <Node*> children;
        
        Node(std::string data){
            this->data=data;
            this->color = "white";
            this->depth = 0;
            this->parent = NULL;
        }
        
};



#endif