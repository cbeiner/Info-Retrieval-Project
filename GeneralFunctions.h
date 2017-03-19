#include <iostream>
#include <string>
#include "StringFunctions.h"

#ifndef STEMMER_H
#define STEMMER_H

std::string porter_stemmer(std::string word){
    int size = word.length() - 1;
    std::string temp;
    
    // This unfortunately does not account for all of the endings and sometimes messes the words up

    // These are a few 'base cases'
    if (word[size] == 's')
        if (endIn(word, "sses"))
            return changeEnd(word, "sses", "ss");
        else if (endIn(word, "ies"))
            return changeEnd(word, "ies", "y");
        else if ( word[size-1] != 's')
            return removeSuffix(word, "s");
            
    if( endIn(word, "eed") )
        temp = removeSuffix(word, "eed");
        if( temp.length() > 1)
            return removeSuffix(word, "d");
    
    else if ( endIn(word, "lled") ) 
        return changeEnd(word, "lled", "l");
        
    // This doesn't hold if 'ed' is preceded by certain phonemes (alveolars)        
    else if ( endIn(word, "ed") && vowelInStem(word, "ed") ) 
        return changeEnd(word, "ed", "e");
    
    else if (endIn(word, "ing") && vowelInStem(word, "ing") )
        return removeSuffix(word, "ing");
    
    // After the most common suffixes, we check based on the second-to-last letter
    switch( word[size - 1] ){
        case 'a':
            if( endIn(word, "izational") ){ return changeEnd(word, "izational", "ize"); }
            if( endIn(word, "ational") ){ return changeEnd(word, "ational", "ate"); }
            if( endIn(word, "tional") ){ return changeEnd(word, "tional", "tion"); }
        case 'c':
            if( endIn(word, "ency") ){ return changeEnd(word, "ency", "ence"); }
            if( endIn(word, "ancy") && vowelInStem(word, "ancy") ){ return changeEnd(word, "ancy", "ance"); }
        case 'e':
            if( endIn(word, "izer") ){ return changeEnd(word, "izer", "ize"); }
        case 'l':
            if( endIn(word, "bly") ){ return changeEnd(word, "bly", "ble"); }
            if( endIn(word, "ally") ){ return changeEnd(word, "ally", "al"); }
            if( endIn(word, "ently") ){ return changeEnd(word, "ently", "ent"); }
            if( endIn(word, "ely") ){ return changeEnd(word, "ely", "e"); }
            if( endIn(word, "ously") ){ return changeEnd(word, "ously", "ous"); }
        case 'o':
            if( endIn(word, "ization") ){ return changeEnd(word, "ization", "ize"); }
            if( endIn(word, "ation") ){ return changeEnd(word, "ation", "ate"); }
            if( endIn(word, "ator") ){ return changeEnd(word, "ator", "ate"); }
        case 's':
            if( endIn(word, "alism") ){ return changeEnd(word, "alism", "al"); }
            if( endIn(word, "iveness") ){ return changeEnd(word, "iveness", "ive"); }
            if( endIn(word, "fulness") ){ return changeEnd(word, "fulness", "ful"); }
            if( endIn(word, "ousness") ){ return changeEnd(word, "ousness", "ous"); }
        case 't':
            if( endIn(word, "ality") ){ return changeEnd(word, "ality", "al"); }
            if( endIn(word, "ivity") ){ return changeEnd(word, "ivity", "ive"); }
            if( endIn(word, "bility") ){ return changeEnd(word, "bility", "ble"); }
        case 'g':
            if( endIn(word, "logy") ){ return changeEnd(word, "logy", "log"); }
    }
    
    // If we still haven't caught it, then we check based on the last letter
    switch ( word[size] ){
        case 'e':
            if( endIn(word, "icate") ){ return changeEnd(word, "icate", "ic"); }
            if( endIn(word, "ative") ){ return changeEnd(word, "ative", "e"); }
            if( endIn(word, "alize") ){ return changeEnd(word, "alize", "al"); }
        case 'y':
            if( endIn(word, "icity") ){ return changeEnd(word, "icity", "ic"); }
        case 'l':
            if( endIn(word, "ical") ){ return changeEnd(word, "ical", "ic"); }
            if( endIn(word, "ful") ){ return changeEnd(word, "ful", ""); }
        case 's':
            if( endIn(word, "ness") ){ return changeEnd(word, "ness", ""); }
    }
    // Return the original if it's not affected 
    return word;
    
}

#endif