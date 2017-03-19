#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cctype>
#include <queue>
#include "KnowledgeBase.h"

void initializeBFS(Node* head){
    // this initializes all of the nodes so they can store parents and be undiscovered
    int i = 0;
    head->color = "white";
    head->depth = 0;
    head->parent = NULL;
    
    if ( head->children.empty() != true ){
        while ( i < head->children.size() ){
            initializeBFS(head->children[i]);
            i += 1;
        }
    }
};

Node* BFS (Node* head, std::string word){
    // this is a standard BFS algorithm implemented into C++ as an auxiliary function to help with 
    // the other BFS algorithms in finding specific nodes and sotring them.
    initializeBFS(head);
    std::queue<Node*> Q;
    head->color = "grey";
    Node* node;
    Q.push(head);
    
    while(Q.empty() != true){
        node = Q.front();
        Q.pop();
        
        if( node->data == word){
            return node;
        }
        
        for (int i = 0; i < node->children.size(); i++ ){
            if ( node->children[i]->color == "white" ){
                node->children[i]->color = "grey";
                node->children[i]->depth = node->depth + 1;
                node->children[i]->parent = node;
                Q.push(node->children[i]);
            }
        }
    }
    Node* me = new Node("Does not exist");
    return me;
};


void subtypes(Node* head, int quantity, int order, std::string type){
    
    std::queue<Node*> set;
    Node* headNode = BFS(head, type); //headNode is the node containing the string we're looking for
    Node* node;
    std::queue<Node*> Q;
    initializeBFS(headNode); // prime the BFS
    headNode->color = "grey";
    Q.push(headNode);
    
    while(Q.empty() != true){
        node = Q.front();
        Q.pop();
        
        // filter for nodes that are of proper depth from the head
        if( node->depth == order){
            // only inserts "quantity" number of nodes, as desired
            if ( set.size() < quantity ){
                set.push(node);
            }
        }
        
        // ensures that no nodes beyond the desired depth are considered
        else if( node->depth < order ){
            // standard BFS internals
            for (int i = 0; i < node->children.size(); i++ ){
                if ( node->children[i]->color == "white" ){
                    node->children[i]->color = "grey";
                    node->children[i]->depth = node->depth + 1;
                    node->children[i]->parent = node;
                    Q.push(node->children[i]);
                }
            }
        }
    }
    // Prints out results
    std::cout << "The " << quantity << " subtypes of order " << order << " of " << type << " are:" << std::endl;
    while ( set.empty() != true){
        std::cout << set.front()->data << std::endl;
        set.pop();
     }
};


void subspecies(Node* head, std::string species){
    
    std::cout<<"1"<<std::endl;
    Node* firstNode = BFS(head, species); //find the constructed node from the graph
    initializeBFS(head); //reinitialize a BFS from the new head
    std::queue<Node*> Q;
    firstNode->color = "grey";
    firstNode->depth = 0;
    Node* node;
    Q.push(firstNode);
    int count = 0; // node counter
    
    while(Q.empty() != true){ // Normal BFS will just find every node dominated by the head
        node = Q.front();
        

        for (int i = 0; i < node->children.size(); i++ ){
            if ( node->children[i]->color == "white" ){
                node->children[i]->color = "grey";
                node->children[i]->depth = node->depth + 1;
                node->children[i]->parent = node;
                Q.push(node->children[i]);
            }
        }
        
        Q.pop();
        count++; // increase count for each element removed from the queue
    }
    
     std::cout << "The number of subspecies of " << species << " is " << (count-1) << std::endl;
};


std::string lowestCommonAncestor(Node* head, std::string sp1, std::string sp2){
    
    // finds the first two heads in the constructed graph
    // this allows us to access parents
    Node* one = BFS(head, sp1); 
    Node* two = BFS(head, sp2); 
    
    // two sets to store the paths to the root
    std::vector<std::string> set1; 
    std::vector<std::string> set2;
    
    std::queue<Node*> Q;
    head->color = "grey";
    head->depth = 0;
    Node* node;
    Q.push(head);
    
    while (one != NULL || two != NULL){
        
        if (one != NULL){ // follows the path from node SP1 to the root
            // places the path into set1
            set1.push_back(one->data); 
            one = one->parent;
        }
        
        if (two!= NULL){ //follows path from SP2 to the root
            // places the path into set2
            set2.push_back(two->data);
            two = two->parent;
        }
    } 
    
    // simple iterator to search for the matching nodes on the path closest to the SP1 and SP2
    for (int i = 0; i < set1.size(); i++){ 
        for(int j = 0; j < set2.size(); j++){
            if( set1[i] == set2[j]){
                return set1[i];
            }
        }
    }
    
    return "No lowest common ancestor exists.";
    
    
};

