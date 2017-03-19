#include <iostream>
#include <string>

#ifndef STRINGFUNCTIONS_H
#define STRINGFUNCTIONS_H

bool endIn(std::string word, std::string end){
    
    int wordL = word.length() - 1;
    int endL = end.length() - 1;
    
    // Works backward through word to make sure the suffixes match
    while (endL >= 0){  
        if (word[wordL] == end[endL]){
            wordL--;
            endL--;
        }
        else
            return false; // As soon as they don't match, false
    }
    return true;
    
}

std::string removeSuffix(std::string word, std::string suff){
    std::string stemmed;
    int wordL = word.length() - 1;
    int endL = suff.length() - 1;
    
    // This gives us the index of where the stem ends and the suffix begins
    int editlen = wordL - endL; 
    // Takes the substring that is the stem
    stemmed = word.substr(0, editlen); 
    return stemmed;
}

std::string changeEnd(std::string word, std::string end, std::string next){
    std::string stemmed;
    int wordL = word.length() - 1;
    int endL = end.length() - 1;
    
    // This gives us the index of where the stem ends and the suffix begins
    int editlen = wordL - endL;
    // Concatenates the stem with the new ending
    stemmed = word.substr(0, editlen) + next; 
    return stemmed;
}



bool vowelInStem(std::string word, std::string stem){
    
    int wordL = word.length() - 1;
    int stemL = stem.length() - 1;
    int editlen = wordL - stemL - 1; // captures stem
    
    while (editlen >= 0){
        // Simply if there is a vowel before the suffix
        if(word[editlen] == 'a' || word[editlen] == 'e' || word[editlen] == 'i' || word[editlen] == 'o' || word[editlen] == 'u' || word[editlen] == 'y')
            return true;
        
        else
            editlen--;
    }
    
    return false;
}


#endif
