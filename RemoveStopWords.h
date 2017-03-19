//My Assumption
//1.Comma use for seperation of string
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include "avlNode.h"

#ifndef REMOVESTOPWORDS_H
#define REMOVESTOPWORDS_H

avlNode* makeStopWordsArray(){
    
    
    std::string line;
    // Open stopwords file
    std::ifstream fileName("stopwords.txt");
    //Create new AVL tree
    avlNode *stopWords = new avlNode("");
    
    if ( fileName.is_open() ){
        
        // For each stop word in the file, add it to the AVL tree
        while ( getline(fileName, line) ){
            stopWords = stopWords->insert(line);
        }
        fileName.close();
    }
    
    return stopWords;
    // The AVL is nice because it significantly decreases the time it takes to look up stop words
    // since complexity changes from O(n) to O(logn)
    
}

#endif