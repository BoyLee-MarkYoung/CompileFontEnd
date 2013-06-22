//
//  Token.h
//  CompileFrontEnd
//
//  Created by Mark Young on 13-6-19.
//  Copyright (c) 2013年 Boy-Mark. All rights reserved.
//

#ifndef __CompileFrontEnd__Token__
#define __CompileFrontEnd__Token__

#include <iostream>
#include "Tag.h"
//#include "Type.h"
//#include "Word.h"

using namespace std;
class Token {
public:
    int tag;
    Token(int t)
        :tag(t)
    {}
    
    
    virtual void foo(){}
    Token(){ tag = Tag::Null;}
    virtual string toString();
    
    
    static Token Null;
    bool operator==(const Token &rhs);
//    operator Word();
    Token& operator=(const Token &rhs);
    
//    operator Type();
};
#endif /* defined(__CompileFrontEnd__Token__) */
