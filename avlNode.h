#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <cctype>
#include <cstring>
#include <cerrno>
#include <algorithm>
#include "KnowledgeBase.h"




#ifndef GENERALFUNCTIONS_H
#define GENERALFUNCTIONS_H

// This helps to format the string by getting rid
// of characters that we wont want to parse through
bool invalidChar(char c) {  
    return !(c>=0 && c <128);   
}; 

//useful function for getting rid of characaters with tildes ect.
void stripUnicode(std::string& str) { 
    str.erase(std::remove_if(str.begin(),str.end(), invalidChar), str.end());  
};
//this make helpful replace function
void replaceChar(std::string& str, const std::string& from,
                          const std::string& to) {
    size_t count = 0;
    while ((count = str.find(from, count)) != std::string::npos) {
         str.replace(count, from.length(), to);
         count+= to.length();
    }
};


// Key function run on each line to get rid of character that we dont
// want in our tree.
std::string formatLine(std::string str){
    stripUnicode(str);
    replaceChar(str, "\t", "");
    replaceChar(str, "\v", "");
    replaceChar(str, "\r", "");
    replaceChar(str, "\f", "");
    replaceChar(str, "-", "_");
    for(int i = 0; i<str.length();i++){
        if(str[i] == ' ' && isalpha(str[i-1]) && (isalpha(str[i+1]) || str[i+1]=='(')){
            str[i] = '_';
        }
        if(str[i] == ')' && (str[i+1] == ' ' && isalpha(str[i+2]))){
            str[i+1] = '_';
        }
        if (isalpha(str[i])){
            str[i] = toupper(str[i]);
        }
    }
    return str;
};


// need to see if other nodes are in the tree before adding as a 
// new child
Node* findNode(const std::string& data, Node* head){
    Node* temp;
    if (head == NULL){
        return NULL;
    }
    else if(head->data == data){
        return head;
    } else {
        if(head->children.empty() == false){
            if(head->children[0]!=NULL){
                for(int i = 0; i<head->children.size();i++){
                    if (findNode(data, head->children.at(i))!= NULL){
                        return findNode(data, head->children.at(i));
                    }
                }
            }
        } else {
        return NULL;
        }
    }
};    
        

//Builds the tree from teh text file
Node* BuildGraph(){
    //Get the input from the file
    std::ifstream input("kb.txt");
    std::string line;
    std::string str;
    std::string word;
    //starting NODE
    Node* head = new Node("ENTITY");
    Node* temp = head;
    
    //For each line in the text File
    for ( line ; getline( input, line );)
    {

        int count = 0;
        std::string formatted_line = formatLine(line);
        formatted_line = formatted_line.substr(0,formatted_line.find('\n'));
        formatted_line.push_back(',');
        for(int i = 0; i < formatted_line.length();i++){
            if(isalpha(formatted_line[i])  || formatted_line[i] == '(' || formatted_line[i] == ')' || formatted_line[i] == '_' || (!isalpha(formatted_line[i]) && (formatted_line[i]!=','&&formatted_line[i]!=':'&&formatted_line[i]!=' '))){
                count+=1;
                
            }
            //first word of line
            if(formatted_line[i]==':'){
                word = "";
                for (;count>0;count--){
                    word += formatted_line[i-count];
                }
                count = 0;
                if(findNode(word,head)!=NULL){
                    temp = findNode(word, head);
                } else {
                    temp->children.push_back(new Node(word));
                }
            }
            //subsequent words
            if(formatted_line[i]==','){
                word = "";
                for (;count>0;count--){
                    word += formatted_line[i-count];
                }
                count = 0;
                temp->children.push_back(new Node( word ));
            }
        }
        
    }
    return head;//should return first node.
};

#endif
