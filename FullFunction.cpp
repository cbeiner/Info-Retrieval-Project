#include <iostream>
#include <fstream> 
#include <string>
#include <queue>
#include <cctype>
#include <map>
#include <math.h>
#include <algorithm>    // std::sort
#include <vector>
#include "avlNode.h"
#include "Stemmer.h"
#include "RemoveStopWords.h"
#include "KnowledgeBase.h"
#include "GeneralFunctions.h"
#include "BFSstuff.h"





std::map<std::string, double> firstPass(int num){
    std::string file_ext_0 = "texts/txt0";
    std::string file_ext = "texts/txt";
    std::string filename;
    int filenum = num;
    
    if(filenum < 10){
        filename = file_ext_0 + std::to_string(filenum) + ".txt";  
    } else {
        filename = file_ext + std::to_string(filenum) + ".txt";
    }
    
    
    // Store the array of words/freuqency as a map
    std::map<std::string, double> tfArray;
    
    
    // Keep track of total words for relative frequency
    int totalWords = 0;
    
    
    
    std::ifstream inFile(filename.c_str());
     
    avlNode* vec = makeStopWordsArray();
    
    std::string temp;
    std::string line;
    std::queue<std::string> concat;
    int j = 0;
    

    if (inFile.is_open()){

    while (getline(inFile, line)){
        for (int i = 0; i < line.length(); i++){
        
            // This will grab individual words from the file and throw away numbers and punctuation
            if (line[i] != ',' && line[i] != ' ' && line[i] != '.' && line[i] != ';' && line[i] != '(' && line[i] != ')' && line[i] != '[' && line[i] != ']' && line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != '3' && line[i] != '4' && line[i] != '5' && line[i] != '6' && line[i] != '7' && line[i] != '8' && line[i] != '9' && line[i] != '\n'){ 
                line[i] = tolower(line[i]);
                // adds words letter by letter into the 'temp' buffer
                temp.push_back(line[i]);
            }
            
            // exits when we hit punctuation, e.o.w, or numbers
            else{ 
                
                // we only do something if the word is not a stop word (this effectively removes stop words by not copying them)

                if( vec->isIn(temp) != 1 ) 
                
                    // add word to queue which stores the entire line
                    concat.push(temp); 
                    temp.clear();
            }
        }

    }
    
    inFile.close();
    
    
    }
     // Now we consider the buffer
    while ( !concat.empty() ){
        std::map<std::string, double>::iterator it;
        temp = concat.front();
        concat.pop();
        //std::cout << temp << std::endl;
        // Stem the word
        if (temp != " "){
            temp = porter_stemmer(temp);
        // See if we can find the key already in the map
            it = tfArray.find(temp);
        
            if (it == tfArray.end()){ // If the key isn't in the map
                tfArray.insert( std::pair<std::string, double>(temp, 1) ); // Insert the word with a count of 1
                totalWords += 1; 
            }
            else{  
                tfArray[it->first] += 1;
                totalWords += 1;
            }
            temp.clear();
            it = tfArray.begin();
            }
        }
        
        // Iterate through the map and replace the number of occurences with global frequency
        for (std::map<std::string,double>::iterator iter=tfArray.begin(); iter!=tfArray.end(); ++iter){
            //std::cout<<iter->second / totalWords<<std::endl;
            //std::cout<<iter->second <<std::endl;
            iter->second = iter->second / totalWords;
            //std::cout<<iter->second <<std::endl;
        }

        
        // Thus removing all stop words and stemming all words
        return tfArray;
}

double D(std::map<std::string,double> p, std::string q){
    std::map<std::string, double>::iterator it;
    double distance;
    bool flag = false;
        // If the key isn't in the map
        for(std::map<std::string, double >::const_iterator it = p.begin(); it != p.end(); ++it){
            if(it->first.compare(q)==0){
                //std::cout<<it->first<<std::endl;
                distance += ((it->second - 1)*(it->second - 1));
                flag = true;
            } else {
                distance += (it->second * it->second);
            }
        }
        if(flag){
            return sqrt(distance);
        }
        
        if(!flag){
            //std::cout<<"not found sorry" <<std::endl;
            return sqrt(distance+1);
            
        }
}
bool isinfiles(std::map<std::string,double> p, std::string q){
    std::map<std::string, double>::iterator it;
    double distance;
    bool flag = false;
        // If the key isn't in the map
        for(std::map<std::string, double >::const_iterator it = p.begin(); it != p.end(); ++it){
            if(it->first.compare(q)==0){
                //std::cout<<it->first<<std::endl;
                distance += ((it->second - 1)*(it->second - 1));
                flag = true;
            } else {
                distance += (it->second * it->second);
            }
        }
        if(flag){
            return true;
        }
        
        if(!flag){
            //std::cout<<"not found sorry" <<std::endl;
            return false;
            
        }
}

    // it = p.find(q)
    // if (it == p.end()){ // If the key isn't in the map
    //     for(std::map<std::string, double >::const_iterator it = myMap.begin(); it != myMap.end(); ++it){
    //         distance += it->second * it->second;
    //     }
    //     return sqrt(distance+1);
    // } else {
    //     for(std::map<std::string, double >::const_iterator it = myMap.begin(); it != myMap.end(); ++it){
    //         if()
    //         distance += it->second * it->second;
    //     }
    // }
class NodeSort{
    int index;
    double val;
    public:
        NodeSort(int index,double val){
            this->index = index;
            this->val = val;
        }
        double getV(){
            return this->val;
        }
        double getI(){
            return this->index;
        }
};

void runBFS(Node* head, std::string str){
 std::cout << "-----------------------------------------------------" << std::endl;
 
 std::transform(str.begin(), str.end(),str.begin(), ::toupper);
 std::cout << "**IF PROGRAM EXITS WORDS NOT FOUND IN KnowledgeBase**" << std::endl;
 
 Node* Bfs = BFS(head, str);
 
 if(Bfs == NULL){
     
 }
 
 std::cout << Bfs->data << " is " << Bfs->children.at(0)->data << std::endl;
 
 std::cout << "**Consider retrying with the subspecies**" << std::endl;
 
}



bool pairCompare(NodeSort* fir, NodeSort* sec) {
  return fir->getV() < sec->getV();
}


int main(){
    bool flag = true;
    bool check = false;

    Node* head = new Node("ENTITY");
    head = BuildGraph();
    
    while(flag){
        std::string choice;
        std::cout << "---------------------------------------------------------------------------" << std::endl;
        std::cout << "Welcome! Enter a word as a query to get the best 6 files" << std::endl;
        std::cout << "or press cntrl c to exit                       " << std::endl;
        std::cout << "---------------------------------------------------------------------------" << std::endl;
        std::cout << "Enter: ";
        std::cin >> choice;
        std::vector<NodeSort*> topFiles;
        std::map<std::string, double> myMap;
        
        
        for(int i = 1; i<41;i++){
            myMap = firstPass(i);
            //std::cout<< D(myMap, choice)<<std::endl;
            if(isinfiles(myMap,choice)){
                check = true;
            }
            //double d = D(myMap, "shark");
        }
        
        
        if(check){
            
            for(int i = 1; i<41;i++){
                myMap = firstPass(i);
                //std::cout<< D(myMap, choice)<<std::endl;
                topFiles.push_back(new NodeSort(i,D(myMap, choice)));
                //double d = D(myMap, "shark");
            }
            std::sort(topFiles.begin(), topFiles.end(), pairCompare);
            std::cout<<"top 6 files are: "<<std::endl;
            for(int z = 0; z < 6; z++){
                std::cout<< "txt" << topFiles.at(z)->getI()<<".txt     " << "Distance: " << topFiles.at(z)->getV()<<std::endl;
            }
        } else {
            std::cout<<"Im sorry, Your Query wasnt found, lets check the Knowlege Base"<<std::endl;
            std::cout<<"for some subspecies and try again!"<<std::endl;
            runBFS(head, choice);
            std::cout << "-----------------------------------------------------" << std::endl;
        }
    }
        
        
        //TEST STEM/FREQUENCY FUNCITONS
        // for(std::map<std::string, double >::const_iterator it = myMap.begin(); it != myMap.end(); ++it)
        // {
        // std::cout << it->first << " " << it->second << " " <<"\n";
        // }
        //TEST DISTANCE FUNCTION
        //std::cout<< D(myMap,"") <<std::endl;
        return 0;
}
