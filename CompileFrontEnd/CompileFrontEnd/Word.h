//
//  Word.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Word__
#define __CompileFrontEnd__Word__

#include <iostream>
#include "Token.h"
#include "Tag.h"



using namespace std;

class Word : public Token {
    
public:
    string lexeme;
    Word( string s, int tag)
    :Token(tag), lexeme(s)
    {}
    
    Word(){lexeme = "";}
    string toString() { return lexeme; }
    
    static Word
    eq,  ne, le,  ge, andd,  orr, //双目运算
    minus, True, False, temp; //单目运算
    
    static Word Null;
    
    Word& operator=(const Word &rhs);
    bool operator!=(const Word &rhs);
    bool operator==(const Word &rhs);
    
};

#endif /* defined(__CompileFrontEnd__Word__) */
